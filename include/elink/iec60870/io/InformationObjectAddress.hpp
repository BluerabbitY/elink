/***********************************************************************************
 * \file InformationObjectAddress.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief information object address (IOA)
 * \date 2025-12-12 22:10:19
 * 
 * \copyright Copyright (C) 2025-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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

    bool operator==(const int addr) const
    {
        return address() == addr;
    }

    bool operator!=(const int addr) const
    {
        return address() != addr;
    }

    InformationObjectAddress operator+(const int offset) const
    {
        return InformationObjectAddress{address() + offset, getIOAByteLength()};
    }

    InformationObjectAddress operator-(const int offset) const
    {
        return InformationObjectAddress{address() - offset, getIOAByteLength()};
    }

    InformationObjectAddress& operator=(const int address)
    {
        setAddress(address);
        return *this;
    }

    InformationObjectAddress& operator+=(const int offset)
    {
        setAddress(address() + offset);
        return *this;
    }

    InformationObjectAddress& operator-=(const int offset)
    {
        setAddress(address() - offset);
        return *this;
    }

    bool setAddress(const int ioa)
    {
        addressM = (addressM & 0xff000000) | (std::clamp<int>(ioa, 0, (1 << 8 * length()) - 1) & 0x00ffffff);
        return address() == ioa;
    }

    [[nodiscard]] int address() const
    {
        return static_cast<int>(addressM & 0x00ffffff);
    }

    [[nodiscard]] int length() const
    {
        return static_cast<int>(getIOAByteLength());
    }

    [[nodiscard]] IOAByteLength getLengthStrategy() const
    {
        return getIOAByteLength();
    }

    void resize(const IOAByteLength byteOfIOA)
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
