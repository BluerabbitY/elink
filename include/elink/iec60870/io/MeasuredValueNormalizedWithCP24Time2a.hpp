/***********************************************************************************
 * \file MeasuredValueNormalizedWithCP24Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-01 00:36:43
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

#include "elink/iec60870/details/io/MeasuredValueNormalizedImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class MeasuredValueNormalizedWithCP24Time2a final
: public details::MeasuredValueNormalizedImp<MeasuredValueNormalizedWithCP24Time2a, TypeID::M_ME_TA_1>,
  public details::CPxxTime2aUtil<CP24Time2a>
{
public:
    MeasuredValueNormalizedWithCP24Time2a() = default;

    MeasuredValueNormalizedWithCP24Time2a(const IOA ioa,
                                          const float value,
                                          const Quality quality = Quality::GOOD,
                                          const CP24Time2a cp24time2a = CP24Time2a::now())
    : MeasuredValueNormalizedImp{ioa, value, quality}, CPxxTime2aUtil{cp24time2a}
    {
    }

    MeasuredValueNormalizedWithCP24Time2a(const IOA ioa,
                                          const OriginalPhyValue value,
                                          const NormalizationFactor factor,
                                          const float offset = 0.f,
                                          const Quality quality = Quality::GOOD,
                                          const CP24Time2a cp24time2a = CP24Time2a::now())
    : MeasuredValueNormalizedImp{ioa, value, factor, offset, quality}, CPxxTime2aUtil{cp24time2a}
    {
    }

    ~MeasuredValueNormalizedWithCP24Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const MeasuredValueNormalizedWithCP24Time2a& io)
    {
        return stream << io.valueM << io.qualityM << io.cpxxtime2aM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, MeasuredValueNormalizedWithCP24Time2a& io)
    {
        return stream >> io.valueM >> io.qualityM >> io.cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + sizeof(qualityM) + sizeof(cpxxtime2aM);
    }
};

}
