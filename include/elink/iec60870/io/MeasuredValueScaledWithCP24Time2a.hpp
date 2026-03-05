/***********************************************************************************
 * \file MeasuredValueScaledWithCP24Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-01 22:51:42
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

#include "elink/iec60870/details/io/MeasuredValueScaledImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class MeasuredValueScaledWithCP24Time2a final
    : public details::MeasuredValueScaledImp<MeasuredValueScaledWithCP24Time2a, TypeID::M_ME_TB_1>,
      public details::CPxxTime2aUtil<CP24Time2a>
{
public:
    MeasuredValueScaledWithCP24Time2a() = default;

    MeasuredValueScaledWithCP24Time2a(const IOA ioa,
                                      const ScaledValue value,
                                      const Quality quality = Quality::GOOD,
                                      const CP24Time2a cp24time2a = CP24Time2a::now())
    : MeasuredValueScaledImp{ioa, value, quality}, CPxxTime2aUtil{cp24time2a}
    {
    }

    ~MeasuredValueScaledWithCP24Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM << qualityM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM >> qualityM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + sizeof(qualityM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
