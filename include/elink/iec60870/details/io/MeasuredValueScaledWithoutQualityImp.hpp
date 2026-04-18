/***********************************************************************************
 * \file MeasuredValueScaledImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-01 22:25:03
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

#include "elink/iec60870/details/io/InformationObjectSerializable.hpp"
#include "elink/iec60870/details/io/util/NormalizedValueUtil.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class MeasuredValueScaledWithoutQualityImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    MeasuredValueScaledWithoutQualityImp()
        : valueM{0}
    {
    }

    MeasuredValueScaledWithoutQualityImp(const IOA ioa, const ScaledValue value)
    : InformationObjectSerializable<inherit, typeID>{ioa}, valueM{value}
    {
    }

    ~MeasuredValueScaledWithoutQualityImp() = default;

    [[nodiscard]] ScaledValue getValue() const
    {
        return valueM;
    }

    void setValue(const ScaledValue value)
    {
        valueM = value;
    }

protected:
    ScaledValue valueM;
};

}
