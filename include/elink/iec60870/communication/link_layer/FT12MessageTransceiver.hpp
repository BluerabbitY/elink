/***********************************************************************************
 * \file FT12MessageTransceiver.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief Frame format FT1.2 message
 * \date 2026-01-07 00:08:43
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#include "elink/common/Type.hpp"
#include "elink/common/communication/Type.hpp"
#include "elink/common/communication/Component.hpp"
#include "elink/common/logging/logger.hpp"

namespace elink::iec60870::ft12
{

namespace details {
// maximum FT1.2 frame length
constexpr uint8_t MaxFT12FrameLength = 261;
}

template<SerialPortLike TransceiverImp, std::size_t N = details::MaxFT12FrameLength>
class Transceiver {
public:
    Transceiver(Component& component, const int& addressLength, const int messageTimeout = 10, const int characterTimeout = 300)
        : transceiverM{component}, addressLengthM{addressLength}, messageTimeoutM{messageTimeout}, characterTimeoutM{characterTimeout}
    {
    }

    ~Transceiver() = default;

    bool open(const SerialPortCFG& cfg)
    {
        return transceiverM.open(cfg);
    }

    void close()
    {
        transceiverM.close();
    }

    void setRawMessageHandler(const RawMessageHandler& hanlder)
    {
        rawMessageHandlerM = hanlder;
    }

    void setMessageFrameTimeouts(const int messageTimeout)
    {
        messageTimeoutM = messageTimeout;
    }

    void setCharacterFrameTimeouts(const int characterTimeout)
    {
        characterTimeoutM = characterTimeout;
    }

    void sendMessage(const MessageBufferView msg)
    {
        if (rawMessageHandlerM)
            rawMessageHandlerM(msg, MessageDir::MSG_DIR_SEND);

        transceiverM.send(msg, std::chrono::milliseconds{});
    }

    LiteBuffer readNextMessage()
    {
        const auto read = readByte(bufferM, std::chrono::milliseconds{messageTimeoutM});

        E_INTERRUPTABLE_BEGIN;

        if (read != InvalidFrameHeader)
        {
            E_INTERRUPT;
        }

        if (read == VariableLengthFrameHeader)
        {
            int msgSize = readByte(bufferM, std::chrono::milliseconds(characterTimeoutM));

            if (msgSize == -1)
            {
                DLOG("RECV: SYNC ERROR");
                transceiverM.discardInBuffer();
                E_INTERRUPT;
            }

            bufferM[0] = VariableLengthFrameHeader;
            bufferM[1] = static_cast<uint8_t>(msgSize);

            msgSize += 4;

            int readBytes = transceiverM.recv({bufferM.data() + 2, msgSize}, std::chrono::milliseconds{characterTimeoutM});

            if (readBytes == msgSize)
            {
                msgSize += 2;

                if (rawMessageHandlerM)
                {
                    rawMessageHandlerM(LiteBuffer{bufferM, msgSize}, MessageDir::MSG_DIR_RECV);
                }

                return LiteBuffer{bufferM, msgSize};
            }
            else
            {
                DLOG("RECV: Timeout reading variable length frame size = {} (expected = {})", readBytes, msgSize);
            }
        }
        else if (read == FixedLengthFrameHeader)
        {
            bufferM[0] = FixedLengthFrameHeader;

            int msgSize = 3 + addressLengthM;

            int readBytes = transceiverM.recv({bufferM.data() + 1, msgSize}, std::chrono::milliseconds{characterTimeoutM});

            if (readBytes == msgSize)
            {
                msgSize += 1;

                if (rawMessageHandlerM)
                {
                    rawMessageHandlerM(LiteBuffer{bufferM, msgSize}, MessageDir::MSG_DIR_RECV);
                }

                return LiteBuffer{bufferM, msgSize};
            }
            else
            {
                DLOG("RECV: Timeout reading fixed length frame size = {} (expected = {})", readBytes, msgSize);
            }
        }
        else if (read == SingleCharacterFrameHeader)
        {
            int msgSize = 1;

            bufferM[0] = SingleCharacterFrameHeader;

            if (rawMessageHandlerM)
            {
                rawMessageHandlerM(LiteBuffer{bufferM, 1}, MessageDir::MSG_DIR_RECV);
            }

            return LiteBuffer{bufferM, msgSize};
        }
        else
        {
            DLOG("RECV: SYNC ERROR");
            transceiverM.discardInBuffer();
            E_INTERRUPT;
        }

        E_INTERRUPTABLE_END;

        return LiteBuffer{};
    }

private:
    using Byte = std::uint8_t;

    Byte readByte(const LiteBuffer buffer, const int timeout)
    {
        auto readByte = transceiverM.recv({bufferM.data(), 1}, std::chrono::milliseconds{timeout});

        if (readByte > 0)
        {
            return buffer[0];
        }

        return InvalidFrameHeader;
    }

    static constexpr uint8_t FixedLengthFrameHeader = 0x10;
    static constexpr uint8_t VariableLengthFrameHeader = 0x68;
    static constexpr uint8_t SingleCharacterFrameHeader = 0xe5;
    static constexpr uint8_t InvalidFrameHeader = -1;

    TransceiverImp transceiverM;
    const int& addressLengthM;
    RawMessageHandler rawMessageHandlerM;
    std::array<uint8_t, N> bufferM;
    int messageTimeoutM;
    int characterTimeoutM;
};

} // namespace 
