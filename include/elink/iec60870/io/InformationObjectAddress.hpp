/***********************************************************************************
 * \file InformationObjectAddress.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief information object address (IOA)
 * \date 2025-12-12 22:10:19
 * 
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#include "elink/iec60870/AppLayerParameters.hpp"
#include "elink/common/Type.hpp"

#include <algorithm>

namespace elink::iec60870 {

class InformationObjectAddress final {
public:
    InformationObjectAddress() : addressM{0}, byteOfIOAM{IOAByteLength::Three}
    {
    }

    explicit InformationObjectAddress(const int ioa, const IOAByteLength byteOfIOA = IOAByteLength::Three)
    : addressM{ioa}, byteOfIOAM{byteOfIOA}
    {
    }

    InformationObjectAddress(const int ioa, const AppLayerParameters& parameters)
    : addressM{ioa}, byteOfIOAM{parameters.getLengthOfIOA()}
    {
    }

    explicit InformationObjectAddress(const LiteBufferView buffer)
    {
        addressM = buffer[0];
        byteOfIOAM = IOAByteLength::One;

        if (buffer.size_bytes() >= 2)
        {
            byteOfIOAM = IOAByteLength::Two;
            addressM += buffer[1] * 0x100;
        }

        if (buffer.size_bytes() >= 3)
        {
            byteOfIOAM = IOAByteLength::Three;
            addressM += buffer[2] * 0x10000;
        }
    }

    ~InformationObjectAddress() = default;

    bool operator==(const InformationObjectAddress& other) const
    {
        return addressM == other.addressM && byteOfIOAM == other.byteOfIOAM;
    }

    bool operator!=(const InformationObjectAddress& other) const
    {
        return addressM != other.address() || byteOfIOAM != other.byteOfIOAM;
    }

    InformationObjectAddress& operator=(const int address)
    {
        setAddress(address);
        return *this;
    }

    bool setAddress(const int ioa)
    {
        addressM = std::clamp<int>(ioa, 0, (1 << 8 * static_cast<int>(byteOfIOAM)) - 1);
        return addressM == ioa;
    }

    [[nodiscard]] int address() const
    {
        return addressM;
    }

    [[nodiscard]] int getLengthOfInformationObjectAddress() const
    {
        return static_cast<int>(byteOfIOAM);
    }

    [[nodiscard]] IOAByteLength getLengthOfInformationObjectAddressStrategy() const
    {
        return byteOfIOAM;
    }

    void resetLengthOfInformationObjectAddress(const IOAByteLength byteOfIOA)
    {
        byteOfIOAM = byteOfIOA;
        setAddress(addressM);
    }

private:
    int addressM;
    IOAByteLength byteOfIOAM;
};

using IOA = InformationObjectAddress;

}
