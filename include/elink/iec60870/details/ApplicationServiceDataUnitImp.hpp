/***********************************************************************************
 * \file ApplicationServiceDataUnitImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-06 19:13:27
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
#include "elink/iec60870/CauseOfTransmission.hpp"
#include "elink/iec60870/io/InformationObjectTypeID.h"
#include "elink/iec60870/AppLayerParameters.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

namespace elink::iec60870::details
{

template <std::size_t MaxLengthOfASDU>
class ApplicationServiceDataUnitImp
{
public:
    explicit ApplicationServiceDataUnitImp(const AppLayerParameters& parameters)
    : typeM{ASDUType::CONSTRUCT},
      parametersM{parameters},
      bufferM{},
      asduM{bufferM},
      payloadM{bufferM.data() + parameters.getHeaderLength(), MaxLengthOfASDU - parameters.getHeaderLength()}
    {
    }

    ApplicationServiceDataUnitImp(const AppLayerParameters& parameters, const bool isSequence, const COT cot, const int oa, const int ca, const bool isTest = false, const bool isNegative = false)
    : typeM{ASDUType::CONSTRUCT},
      parametersM{parameters},
      bufferM{},
      asduM{bufferM},
      payloadM{bufferM.data() + parameters.getHeaderLength(), MaxLengthOfASDU - parameters.getHeaderLength()}
    {
        setSequence(isSequence);
        setCOT(cot);
        setOA(oa);
        setCA(ca);
        setTest(isTest);
        setNegative(isNegative);
    }

    explicit ApplicationServiceDataUnitImp(const AppLayerParameters& parameters, const LiteBufferView buffer)
    : typeM{ASDUType::TEMPLATE},
      parametersM{parameters},
      bufferM{},
      asduM{const_cast<uint8_t*>(buffer.data()), buffer.size_bytes()},
      payloadM{bufferM.data() + parameters.getHeaderLength(), MaxLengthOfASDU - parameters.getHeaderLength()}
    {
    }

    ~ApplicationServiceDataUnitImp() = default;

    [[nodiscard]] TypeID getTypeID() const
    {
        return static_cast<TypeID>(asduM[0]);
    }

    void setTypeID(TypeID typeId)
    {
        asduM[0] = static_cast<uint8_t>(typeId);
    }

    [[nodiscard]] bool isSequence() const
    {
        return (asduM[1] & 0x80) != 0;
    }

    void setSequence(const bool isSequence)
    {
        if (isSequence)
            asduM[1] |= 0x80;
        else
            asduM[1] &= 0x7f;
    }

    [[nodiscard]] uint8_t getNumberOfElements() const
    {
        return asduM[1] & 0x7f;
    }

    void setNumberOfElements(const uint8_t numberOfElements)
    {
        asduM[1] &= 0x80;
        asduM[1] |= numberOfElements & 0x7f;
    }

    [[nodiscard]] COT getCOT() const
    {
        return static_cast<COT>(asduM[2] & 0x3f);
    }

    void setCOT(COT value)
    {
        uint8_t cot = asduM[2] & 0xc0;
        cot += static_cast<uint8_t>(value) & 0x3f;

        asduM[2] = cot;
    }

    [[nodiscard]] bool isTest() const
    {
        return (asduM[2] & 0x80) == 0x80;
    }

    void setTest(const bool value)
    {
        if (value)
            asduM[2] |= 0x80;
        else
            asduM[2] &= ~0x80;
    }

    [[nodiscard]] bool isNegative() const
    {
         return (asduM[2] & 0x40) == 0x40;
    }

    void setNegative(const bool value)
    {
        if (value)
            asduM[2] |= 0x40;
        else
            asduM[2] &= ~0x40;
    }

    [[nodiscard]] uint8_t getOA() const
    {
        return parametersM.getLengthOfCOT() == COTByteLength::One ? 0 : asduM[3];
    }

    void setOA(const uint8_t oa)
    {
        if (parametersM.getLengthOfCOT() == COTByteLength::Two)
        {
            asduM[3] = oa;
        }
    }

    [[nodiscard]] uint16_t getCA() const
    {
        const int caIndex = static_cast<int>(parametersM.getLengthOfTypeId()) +
                            static_cast<int>(parametersM.getLengthOfVSQ()) +
                            static_cast<int>(parametersM.getLengthOfCOT());

        int ca = asduM[caIndex];

        if (parametersM.getLengthOfCA() == CAByteLength::Two)
            ca += asduM[caIndex + 1] * 0x100;

        return ca;
    }

    void setCA(uint16_t ca)
    {
        const int caIndex = static_cast<int>(parametersM.getLengthOfTypeId()) +
                            static_cast<int>(parametersM.getLengthOfVSQ()) +
                            static_cast<int>(parametersM.getLengthOfCOT());

        if (parametersM.getLengthOfCA() == CAByteLength::One)
        {
            ca = std::clamp<uint8_t>(ca, 0, 255);
        }
        else if (parametersM.getLengthOfCA() == CAByteLength::Two)
        {
            ca = std::clamp<uint16_t>(ca, 0, 65535);
        }

        if (parametersM.getLengthOfCA() == CAByteLength::One)
        {
            asduM[caIndex] = static_cast<uint8_t>(ca);
        }
        else
        {
            asduM[caIndex] = static_cast<uint8_t>(ca % 0x100);
            asduM[caIndex + 1] = static_cast<uint8_t>(ca / 0x100);
        }
    }

    template <typename InformationObjectSerializable>
    bool addInformationObject(const InformationObjectSerializable& io)
    {
        bool encoded = false;

        const auto& ioserialze = static_cast<const InformationObjectSerializable::SerializeType&>(io);

        if (const int numberOfElements = getNumberOfElements(); numberOfElements == 0)
        {
            setTypeID(io.getTypeID());
            ioserialze.serialize(payloadM, false);
            encoded = !payloadM.hasError();
        }
        else if (numberOfElements <= 0x7f)
        {
            /* Check if type of information object is matching ASDU type */
            if (getTypeID() == io.getTypeID())
            {
                if (isSequence())
                {
                    const IOA firstIOA{LiteBufferView{asduM.data() + parametersM.getHeaderLength(), static_cast<std::size_t>(parametersM.getLengthOfIOA())}};
                    /* check that new information object has correct IOA */
                    if (io.getInformationObjectAddress().address() == (firstIOA.address() + numberOfElements))
                    {
                        ioserialze.serialize(payloadM, true);
                        encoded = !payloadM.hasError();
                    }
                    else
                        encoded = false;
                }
                else
                {
                    ioserialze.serialize(payloadM, false);
                    encoded = !payloadM.hasError();
                }
            }
        }

        /* increase number of elements in VSQ */
        if (encoded)
            asduM[1]++;

        payloadM.acknowledgeError();

        return encoded;
    }

    template <typename IOType>
    std::optional<IOType> getElement(const int index) const
    {
        if (getTypeID() == IOType::IDENT_T)
        {
            std::optional<IOType> io{std::in_place};
            const bool isSeq = isSequence();
            const int elementLength = io->length(isSeq);

            int startIndex = parametersM.getHeaderLength();

            if (isSeq)
            {
                startIndex += static_cast<uint8_t>(parametersM.getLengthOfIOA()) + elementLength * index;
                const IOA firstIOA{LiteBufferView{asduM.data() + parametersM.getHeaderLength(), static_cast<std::size_t>(parametersM.getLengthOfIOA())}};
                io->setInformationObjectAddress(IOA{firstIOA.address() + index, parametersM.getLengthOfIOA()});
            }
            else
            {
                startIndex += (static_cast<uint8_t>(parametersM.getLengthOfIOA()) + elementLength) * index;
            }

            switch (typeM)
            {
                case ASDUType::CONSTRUCT: {
                    if (startIndex + elementLength > payloadM.writenBytes() + parametersM.getHeaderLength())
                        return std::nullopt;
                    break;
                }
                case ASDUType::TEMPLATE: {
                    if (index >= getNumberOfElements())
                        return std::nullopt;
                    break;
                }
            }

            IStream istream{asduM.data() + startIndex, asduM.size_bytes()};

            static_cast<IOType::SerializeType&>(*io).deserialize(istream, isSeq);

            if (istream.hasError())
            {
                return std::nullopt;
            }

            return io;
        }

        return std::nullopt;
    }

    void removeAllElements()
    {
        asduM[1] = asduM[1] & 0x80;
        payloadM.erase();
    }

    [[nodiscard]] LiteBufferView getPayload() const
    {
        return {payloadM.data(), payloadM.writenBytes()};
    }

    bool addPayload(const LiteBufferView buffer)
    {
        payloadM << buffer;
        const bool encoded = !payloadM.hasError();
        payloadM.acknowledgeError();
        return encoded;
    }

private:
    enum class ASDUType : uint8_t {
        CONSTRUCT,
        TEMPLATE,
    };

    const ASDUType typeM;
    const AppLayerParameters& parametersM;
    Buffer<MaxLengthOfASDU> bufferM;
    LiteBuffer asduM;
    OStream payloadM;
};

constexpr uint8_t CS101_MAXUMUM_LENGTH_OF_ASDU = 254;
constexpr uint8_t CS104_MAXUMUM_LENGTH_OF_ASDU = 249;

}
