/***********************************************************************************
 * \file LengthInt.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-28 20:54:47
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "elink/common/Type.hpp"

namespace elink::iec60870::details
{

class LengthInt
{
public:
    LengthInt()
    : valueM{}
    {
    }

    explicit LengthInt(const uint32_t value)
    : valueM{}
    {
        setValue(value);
    }

    ~LengthInt() = default;

    void setValue(const uint32_t value)
    {
        valueM[0] = (value % 0x100);
        valueM[1] = (value / 0x100) % 0x100;
        valueM[2] = (value / 0x10000) % 0x100;
    }

    [[nodiscard]] uint32_t getValue() const
    {
        return valueM[0] + (valueM[1] * 0x100) + (valueM[2] * 0x10000);
    }

    template <typename OStream>
    friend OStream& operator<<(OStream& stream, const LengthInt& lengthInt)
    {
        stream << lengthInt.valueM;
        return stream;
    }

    template <typename IStream>
    friend IStream& operator>>(IStream& stream, LengthInt& lengthInt)
    {
        stream >> lengthInt.valueM;
        return stream;
    }

private:
    Buffer<3> valueM;
};

}
