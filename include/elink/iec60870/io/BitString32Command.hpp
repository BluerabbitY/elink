/***********************************************************************************
 * \file Bitstring32Command.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 21:26:44
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

#include "elink/iec60870/details/io/BitString32WithoutQualityImp.hpp"

namespace elink::iec60870
{

class BitString32Command : public details::BitString32WithoutQualityImp<BitString32Command, TypeID::C_BO_NA_1>
{
public:
    BitString32Command() = default;

    BitString32Command(const IOA ioa, const uint32_t value)
    : BitString32WithoutQualityImp{ioa, value}
    {
    }

    ~BitString32Command() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return valueM.size() / 8;
    }
};

}
