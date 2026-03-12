/***********************************************************************************
 * \file MeasuredValueNormalizedWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-12 23:51:54
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

class MeasuredValueNormalizedWithCP56Time2a final
: public details::MeasuredValueNormalizedImp<MeasuredValueNormalizedWithCP56Time2a, TypeID::M_ME_TD_1>,
  public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    MeasuredValueNormalizedWithCP56Time2a() = default;

    MeasuredValueNormalizedWithCP56Time2a(const IOA ioa,
                                          const float value,
                                          const Quality quality = Quality::GOOD,
                                          const CP56Time2a cp56time2a = CP56Time2a::now())
    : MeasuredValueNormalizedImp{ioa, value, quality}, CPxxTime2aUtil{cp56time2a}
    {
    }

    MeasuredValueNormalizedWithCP56Time2a(const IOA ioa,
                                          const OriginalPhyValue value,
                                          const NormalizationFactor factor,
                                          const float offset = 0.f,
                                          const Quality quality = Quality::GOOD,
                                          const CP56Time2a cp56time2a = CP56Time2a::now())
    : MeasuredValueNormalizedImp{ioa, value, factor, offset, quality}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~MeasuredValueNormalizedWithCP56Time2a() = default;

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
