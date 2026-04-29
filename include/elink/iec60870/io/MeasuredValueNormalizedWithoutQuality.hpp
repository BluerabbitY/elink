/***********************************************************************************
 * \file MeasuredValueNormalizedWithoutQuality.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-11 23:43:18
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

#include "elink/iec60870/details/io/MeasuredValueNormalizedWithoutQualityImp.hpp"

namespace elink::iec60870
{

class MeasuredValueNormalizedWithoutQuality final : public details::MeasuredValueNormalizedWithoutQualityImp<MeasuredValueNormalizedWithoutQuality, TypeID::M_ME_ND_1>
{
public:
    MeasuredValueNormalizedWithoutQuality() = default;

    MeasuredValueNormalizedWithoutQuality(const IOA ioa, const float value)
    : MeasuredValueNormalizedWithoutQualityImp{ioa, value}
    {
    }

    MeasuredValueNormalizedWithoutQuality(const IOA ioa, const OriginalPhyValue value, const NormalizationFactor factor, const float offset = 0.f)
    : MeasuredValueNormalizedWithoutQualityImp{ioa, value, factor, offset}
    {
    }

    ~MeasuredValueNormalizedWithoutQuality() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const MeasuredValueNormalizedWithoutQuality& io)
    {
        return stream << io.valueM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, MeasuredValueNormalizedWithoutQuality& io)
    {
        return stream >> io.valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM);
    }
};

}
