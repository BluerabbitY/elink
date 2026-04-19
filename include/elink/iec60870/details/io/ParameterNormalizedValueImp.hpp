/***********************************************************************************
 * \file ParameterNormalizedValueImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-18 23:02:36
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
#include "elink/iec60870/io/QualifierOfParameterMV.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class ParameterNormalizedValueImp : public MeasuredValueNormalizedWithoutQualityImp<inherit, typeID>
{
public:
    ParameterNormalizedValueImp()
    : qpmM{QPM::NOT_USED}
    {
    }

    ParameterNormalizedValueImp(const IOA ioa, const NormalizedValue value, const QualifierOfParameterMV qpm)
    : MeasuredValueNormalizedWithoutQualityImp<inherit, typeID>{ioa, value}, qpmM{qpm}
    {
    }

    ParameterNormalizedValueImp(const IOA ioa, const OriginalPhyValue value, const NormalizationFactor factor, const float offset, const QualifierOfParameterMV qpm)
    : MeasuredValueNormalizedWithoutQualityImp<inherit, typeID>{ioa, value, factor, offset}, qpmM{qpm}
    {
    }

    ~ParameterNormalizedValueImp() = default;

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
