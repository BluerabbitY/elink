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

#include "InformationObjectSerializable.hpp"
#include "elink/iec60870/io/QualityDescriptor.hpp"
#include "elink/iec60870/details/io/util/NormalizedValueUtil.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class MeasuredValueNormalizedImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    MeasuredValueNormalizedImp()
    : valueM{0}, qualityM{Quality::GOOD}
    {
    }

    MeasuredValueNormalizedImp(const IOA ioa, const NormalizedValue value, const Quality quality)
    : InformationObjectSerializable<inherit, typeID>{ioa},
      valueM{0},
      qualityM{quality}
    {
        setValue(value);
    }

    MeasuredValueNormalizedImp(const IOA ioa, const OriginalPhyValue value, const NormalizationFactor factor, const float offset, const Quality quality)
    : InformationObjectSerializable<inherit, typeID>{ioa},
      valueM{0},
      qualityM{quality}
    {
        setValue(value, factor, offset);
    }

    ~MeasuredValueNormalizedImp() = default;

    [[nodiscard]] NormalizedValue getValue() const
    {
        return scaledToNormalized(valueM);
    }

    void setValue(const NormalizedValue value)
    {
        valueM = normalizedToScaled(value);
    }

    // Multiply normalized value by the scale factor to retrieve the original physical value.
    [[nodiscard]] OriginalPhyValue getValue(const ScaledFactor factor, const float offset = 0.f) const
    {
        return getValue() * factor + offset;
    }

    void setValue(const OriginalPhyValue value, const NormalizationFactor factor, const float offset = 0.f)
    {
        setValue((value - offset) / factor);
    }

    [[nodiscard]] Quality getQuality() const
    {
        return qualityM;
    }

    void setQuality(const Quality quality)
    {
        qualityM = quality;
    }

protected:
    NormalizedValueBuffer valueM;
    Quality qualityM;
};

}
