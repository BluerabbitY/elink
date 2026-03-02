/***********************************************************************************
 * \file MeasuredValueShortImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-02 19:04:27
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

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class MeasuredValueShortImp : public InformationObjectSerializable<inherit, typeID> {
public:
    MeasuredValueShortImp()
    : valueM{}, qualityM{Quality::GOOD}
    {
    }

    MeasuredValueShortImp(const IOA ioa, const float value, const Quality quality)
    : InformationObjectSerializable<inherit, typeID>{ioa}, valueM{value}, qualityM{quality}
    {
    }

    ~MeasuredValueShortImp() = default;

    [[nodiscard]] float getValue() const
    {
        return valueM;
    }

    void setValue(const float value)
    {
        valueM = value;
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
    float valueM;
    Quality qualityM;
};

}
