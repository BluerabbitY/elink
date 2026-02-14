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
    InformationObjectAddress() : addressM{0}
    {
        setIOAByteLength(IOAByteLength::Three);
    }

    explicit InformationObjectAddress(const int ioa, const IOAByteLength byteOfIOA = IOAByteLength::Three)
    : addressM{0}
    {
        setIOAByteLength(byteOfIOA);
        setAddress(ioa);
    }

    InformationObjectAddress(const int ioa, const AppLayerParameters& parameters)
    : addressM{0}
    {
        setIOAByteLength(parameters.getLengthOfIOA());
        setAddress(ioa);
    }

    explicit InformationObjectAddress(const LiteBufferView buffer)
    : addressM{0}
    {
        if (buffer.size_bytes() >= 1)
        {
            setIOAByteLength(IOAByteLength::One);
            setAddress(buffer[0]);
        }

        if (buffer.size_bytes() >= 2)
        {
            setIOAByteLength(IOAByteLength::Two);
            setAddress(address() + buffer[1] * 0x100);
        }

        if (buffer.size_bytes() >= 3)
        {
            setIOAByteLength(IOAByteLength::Three);
            setAddress(address() + buffer[2] * 0x10000);
        }
    }

    ~InformationObjectAddress() = default;

    bool operator==(const InformationObjectAddress& other) const
    {
        return addressM == other.addressM && getIOAByteLength() == other.getIOAByteLength();
    }

    bool operator!=(const InformationObjectAddress& other) const
    {
        return addressM != other.address() || getIOAByteLength() != other.getIOAByteLength();
    }

    InformationObjectAddress& operator=(const int address)
    {
        setAddress(address);
        return *this;
    }

    bool setAddress(const int ioa)
    {
        addressM = (addressM & 0xff000000) | (std::clamp<int>(ioa, 0, (1 << 8 * static_cast<int>(getIOAByteLength())) - 1) & 0x00ffffff);
        return address() == ioa;
    }

    [[nodiscard]] int address() const
    {
        return static_cast<int>(addressM & 0x00ffffff);
    }

    [[nodiscard]] int getLengthOfInformationObjectAddress() const
    {
        return static_cast<int>(getIOAByteLength());
    }

    [[nodiscard]] IOAByteLength getLengthOfInformationObjectAddressStrategy() const
    {
        return getIOAByteLength();
    }

    void resetLengthOfInformationObjectAddress(const IOAByteLength byteOfIOA)
    {
        setIOAByteLength(byteOfIOA);
        setAddress(address());
    }

private:
    void setIOAByteLength(const IOAByteLength byteOfIOA)
    {
        addressM = (addressM & ~0xff000000) | ((static_cast<int>(byteOfIOA) << 24) & 0xff000000);
    }

    [[nodiscard]] IOAByteLength getIOAByteLength() const
    {
        return static_cast<IOAByteLength>((addressM & 0xff000000) >> 24);
    }

    // 1 byte length + 3 byte address
    uint32_t addressM;
};

using IOA = InformationObjectAddress;

}
