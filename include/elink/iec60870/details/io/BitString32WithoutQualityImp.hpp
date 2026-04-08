/***********************************************************************************
 * \file BitString32WithoutQualityImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 21:18:56
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

#include "elink/iec60870/details/io/InformationObjectSerializable.hpp"

#include <bitset>

namespace elink::iec60870
{

using BitString32Value = std::bitset<32>;

namespace details
{

template <typename inherit, TypeID typeID>
class BitString32WithoutQualityImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    BitString32WithoutQualityImp() : valueM{0x00000000}
    {
    }

    BitString32WithoutQualityImp(const IOA ioa, const uint32_t value)
     : InformationObjectSerializable<inherit, typeID>{ioa}, valueM{value}
    {
    }

    ~BitString32WithoutQualityImp() = default;

    [[nodiscard]] const BitString32Value &getValue() const
    {
        return valueM;
    }

    void setValue(const BitString32Value& value)
    {
        valueM = value;
    }

    [[nodiscard]] bool getValue(const std::size_t pos) const
    {
        return valueM.test(std::clamp<size_t>(pos, 0, 31));
    }

    void setValue(const std::size_t pos, const bool value)
    {
        valueM.set(std::clamp<size_t>(pos, 0, 31), value);
    }

protected:
    BitString32Value valueM;
};

}
}
