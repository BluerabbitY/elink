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
    : parametersM{parameters},
      asduHeaderLengthM{static_cast<uint8_t>(LENGTH_OF_TTPEID + LENGTH_OF_VSQ + static_cast<uint8_t>(parameters.getLengthOfCOT()) + static_cast<uint8_t>(parameters.getLengthOfCA()))},
      bufferM{},
      asduM{bufferM},
      payloadM{bufferM.data() + asduHeaderLengthM, MaxLengthOfASDU - asduHeaderLengthM}
    {
    }

    ApplicationServiceDataUnitImp(const AppLayerParameters& parameters, const bool isSequence, const COT cot, const int oa, const int ca, const bool isTest = false, const bool isNegative = false)
        : parametersM{parameters},
          asduHeaderLengthM{static_cast<uint8_t>(LENGTH_OF_TTPEID + LENGTH_OF_VSQ + static_cast<uint8_t>(parameters.getLengthOfCOT()) + static_cast<uint8_t>(parameters.getLengthOfCA()))},
          bufferM{},
          asduM{bufferM},
          payloadM{bufferM.data() + asduHeaderLengthM, MaxLengthOfASDU - asduHeaderLengthM}
    {
        setSequence(isSequence);
        setCOT(cot);
        setOA(oa);
        setCA(ca);
        setTest(isTest);
        setNegative(isNegative);
    }

    explicit ApplicationServiceDataUnitImp(const AppLayerParameters& parameters, const LiteBufferView buffer)
    : parametersM{parameters},
      asduHeaderLengthM{static_cast<uint8_t>(LENGTH_OF_TTPEID + LENGTH_OF_VSQ + static_cast<uint8_t>(parameters.getLengthOfCOT()) + static_cast<uint8_t>(parameters.getLengthOfCA()))},
      bufferM{},
      asduM{const_cast<uint8_t*>(buffer.data()), buffer.size()},
      payloadM{bufferM.data() + asduHeaderLengthM, MaxLengthOfASDU - asduHeaderLengthM}
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
        const int caIndex = LENGTH_OF_TTPEID + LENGTH_OF_VSQ + static_cast<int>(parametersM.getLengthOfCOT());

        int ca = asduM[caIndex];

        if (parametersM.getLengthOfCA() == CAByteLength::Two)
            ca += asduM[caIndex + 1] * 0x100;

        return ca;
    }

    void setCA(uint16_t ca)
    {
        const int caIndex = LENGTH_OF_TTPEID + LENGTH_OF_VSQ + static_cast<int>(parametersM.getLengthOfCOT());

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

        if (const int numberOfElements = getNumberOfElements(); numberOfElements == 0)
        {
            setTypeID(io.getTypeID());
            io.serialize(payloadM, false);
            encoded = payloadM.hasError();
        }
        else if (numberOfElements <= 0x7f)
        {
            /* Check if type of information object is matching ASDU type */
            if (getTypeID() == io.getTypeID())
            {
                if (isSequence())
                {
                    /* check that new information object has correct IOA */
                    if (getObjectAddress(io) == (getFirstIOA() + numberOfElements))
                    {
                        io.serialize(payloadM, true);
                        encoded = payloadM.hasError();
                    }
                    else
                        encoded = false;
                }
                else
                {
                    io.serialize(payloadM, false);
                    encoded = payloadM.hasError();
                }
            }
        }

        /* increase number of elements in VSQ */
        if (encoded)
            asduM[1]++;

        payloadM.acknowledgeError();

        return encoded;
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
        const bool encoded = payloadM.hasError();
        payloadM.acknowledgeError();
        return encoded;
    }

private:
    [[nodiscard]] int getFirstIOA() const
    {
        const IOA ioa{LiteBufferView{asduM.data(), static_cast<int>(parametersM.getLengthOfIOA())}};
        return ioa.getLengthOfInformationObjectAddress();
    }

    static constexpr uint16_t MAX_LENGTH_OF_ASDU = 256;
    static constexpr uint8_t LENGTH_OF_TTPEID = 1;
    static constexpr uint8_t LENGTH_OF_VSQ = 1;

    const AppLayerParameters& parametersM;
    const uint8_t asduHeaderLengthM;

    Buffer<MAX_LENGTH_OF_ASDU> bufferM;

    LiteBuffer asduM;

    OStream payloadM;
};

constexpr uint8_t CS101_MAXUMUM_LENGTH_OF_ASDU = 254;
constexpr uint8_t CS104_MAXUMUM_LENGTH_OF_ASDU = 249;

}
