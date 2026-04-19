/***********************************************************************************
 * \file MeasuredValueShortWithoutQualityImp.hpp
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

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class MeasuredValueShortWithoutQualityImp : public InformationObjectSerializable<inherit, typeID> {
public:
    MeasuredValueShortWithoutQualityImp()
    : valueM{}
    {
    }

    MeasuredValueShortWithoutQualityImp(const IOA ioa, const float value)
    : InformationObjectSerializable<inherit, typeID>{ioa}, valueM{value}
    {
    }

    ~MeasuredValueShortWithoutQualityImp() = default;

    [[nodiscard]] float getValue() const
    {
        return valueM;
    }

    void setValue(const float value)
    {
        valueM = value;
    }

protected:
    float valueM;
};

}
