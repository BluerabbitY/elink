/***********************************************************************************
 * \file MeasuredValueShortWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 09:30:06
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

#include "elink/iec60870/details/io/MeasuredValueShortImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class MeasuredValueShortWithCP56Time2a final
: public details::MeasuredValueShortImp<MeasuredValueShortWithCP56Time2a, TypeID::M_ME_TF_1>,
  public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    MeasuredValueShortWithCP56Time2a() = default;

    MeasuredValueShortWithCP56Time2a(const IOA ioa,
                                     const float value,
                                     const Quality quality = Quality::GOOD,
                                     const CP56Time2a cp56time2a = CP56Time2a::now())
    : MeasuredValueShortImp{ioa, value, quality}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~MeasuredValueShortWithCP56Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const MeasuredValueShortWithCP56Time2a& io)
    {
        return stream << io.valueM << io.qualityM << io.cpxxtime2aM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, MeasuredValueShortWithCP56Time2a& io)
    {
        return stream >> io.valueM >> io.qualityM >> io.cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + sizeof(qualityM) + sizeof(cpxxtime2aM);
    }
};

}
