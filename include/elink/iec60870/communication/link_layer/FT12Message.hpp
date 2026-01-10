/***********************************************************************************
 * \file FT12Message.hpp
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

namespace elink::iec60870::comm::LinkLayer::internal
{

template <typename Stream, RawMessageHandlerConcept RawMessageHandler>
class FT12Message {
public:
    FT12Message(Stream& transmiter, const int& addressLength, const int messageTimeout = 10, const int characterTimeout = 300)
        : transmiterM{transmiter}, addressLengthM{addressLength}, messageTimeoutM{messageTimeout}, characterTimeoutM{characterTimeout}
    {
    }

    ~FT12Message() = default;

    void setRawMessageHandler(RawMessageHandler hanlder)
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

    void sendMessage(MessageBufferView msg)
    {
        if (rawMessageHandlerM)
            rawMessageHandlerM(msg, MessageDir::MSG_SEND);

        // SerialPort_write(self->serialPort, msg, 0, msgSize);
        // transmiterM.read();
    }

    template <elink::internal::TXMessageHandlerConcept TXMessageHandler>
    void readNextMessage(MessageBufferView buffer, TXMessageHandler hanlder)
    {

    }

    // (Variable Length Frame)
    // (Fixed Length Frame)
    // (Single Character Frame)

private:
    Stream& transmiterM;
    const int& addressLengthM;
    RawMessageHandler rawMessageHandlerM;
    int messageTimeoutM;
    int characterTimeoutM;
};

} // namespace 
