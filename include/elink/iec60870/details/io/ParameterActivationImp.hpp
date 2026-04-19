/***********************************************************************************
 * \file ParameterActivationImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 13:26:02
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

namespace elink::iec60870
{

/**
 * \brief Qualifier of parameter activation (QPA) according to IEC 60870-5-101:2003 7.2.6.25
 */
enum class QualifierOfParameterActivation : uint8_t
{
    NOT_USED = 0,
    DE_ACT_PREV_LOADED_PARAMETER = 1,
    DE_ACT_OBJECT_PARAMETER = 2,
    DE_ACT_OBJECT_TRANSMISSION = 4,
};

using QPA = QualifierOfParameterActivation;

namespace details
{

template <typename inherit, TypeID typeID>
class ParameterActivationImp : public InformationObjectSerializable<inherit, typeID> {
public:
    ParameterActivationImp()
    : qpaM{QPA::NOT_USED}
    {
    }

    ParameterActivationImp(const IOA ioa, const QualifierOfParameterActivation qpa)
    : InformationObjectSerializable<inherit, typeID>{ioa}, qpaM{qpa}
    {
    }

    ~ParameterActivationImp() = default;

    [[nodiscard]] QualifierOfParameterActivation getQPA() const
    {
        return qpaM;
    }

    void setQPA(const QualifierOfParameterActivation apa)
    {
        qpaM = apa;
    }

protected:
    QualifierOfParameterActivation qpaM;
};

}
}
