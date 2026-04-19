/***********************************************************************************
 * \file ParameterScaledValueImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 10:47:01
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

#include "elink/iec60870/details/io/MeasuredValueScaledWithoutQualityImp.hpp"
#include "elink/iec60870/io/QualifierOfParameterMV.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class ParameterScaledValueImp : public MeasuredValueScaledWithoutQualityImp<inherit, typeID>
{
public:
    ParameterScaledValueImp()
    : qpmM{QPM::NOT_USED}
    {
    }

    ParameterScaledValueImp(const IOA ioa, const ScaledValue value, const QualifierOfParameterMV qpm)
    : MeasuredValueScaledWithoutQualityImp<inherit, typeID>{ioa, value}, qpmM{qpm}
    {
    }

    ~ParameterScaledValueImp() = default;

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
