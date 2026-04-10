/***********************************************************************************
 * \file Bitstring32CommandWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 01:00:03
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
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class BitString32CommandWithCP56Time2a final
: public details::BitString32WithoutQualityImp<BitString32CommandWithCP56Time2a, TypeID::C_BO_TA_1>
, public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    BitString32CommandWithCP56Time2a() = default;

    BitString32CommandWithCP56Time2a(const IOA ioa, const uint32_t value, const CP56Time2a cp56time2a = CP56Time2a::now())
    : BitString32WithoutQualityImp{ioa, value}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~BitString32CommandWithCP56Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return valueM.size() / 8 + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
