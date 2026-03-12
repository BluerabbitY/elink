/***********************************************************************************
 * \file MeasuredValueNormalizedImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-01 00:19:02
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
#include "elink/iec60870/io/QualityDescriptor.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class MeasuredValueNormalizedImp : public MeasuredValueNormalizedWithoutQualityImp<inherit, typeID>
{
public:
    MeasuredValueNormalizedImp()
    : MeasuredValueNormalizedWithoutQualityImp<inherit, typeID>{}, qualityM{Quality::GOOD}
    {
    }

    MeasuredValueNormalizedImp(const IOA ioa, const NormalizedValue value, const Quality quality)
    : MeasuredValueNormalizedWithoutQualityImp<inherit, typeID>{ioa, value},
      qualityM{quality}
    {
    }

    MeasuredValueNormalizedImp(const IOA ioa, const OriginalPhyValue value, const NormalizationFactor factor, const float offset, const Quality quality)
    : MeasuredValueNormalizedWithoutQualityImp<inherit, typeID>{ioa, value, factor, offset},
      qualityM{quality}
    {
    }

    ~MeasuredValueNormalizedImp() = default;

    [[nodiscard]] Quality getQuality() const
    {
        return qualityM;
    }

    void setQuality(const Quality quality)
    {
        qualityM = quality;
    }

protected:
    Quality qualityM;
};

}
