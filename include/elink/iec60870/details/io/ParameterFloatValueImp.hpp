/***********************************************************************************
 * \file ParameterFloatValueImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 11:48:59
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

#include "elink/iec60870/details/io/MeasuredValueShortWithoutQualityImp.hpp"
#include "elink/iec60870/io/QualifierOfParameterMV.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class ParameterFloatValueImp : public MeasuredValueShortWithoutQualityImp<inherit, typeID>
{
public:
    ParameterFloatValueImp()
    : qpmM{QPM::NOT_USED}
    {
    }

    ParameterFloatValueImp(const IOA ioa, const float value, const QualifierOfParameterMV qpm)
    : MeasuredValueShortWithoutQualityImp<inherit, typeID>{ioa, value}, qpmM{qpm}
    {
    }

    ~ParameterFloatValueImp() = default;

    void setQPM(const QualifierOfParameterMV qpm)
    {
        qpmM = qpm;
    }

    [[nodiscard]] QualifierOfParameterMV getQPM() const
    {
        return qpmM;
    }

protected:
    QualifierOfParameterMV qpmM;
};

}
