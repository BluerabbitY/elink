/***********************************************************************************
 * \file SetpointCommandScaledImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 18:50:55
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

#include "elink/iec60870/details/io/SetpointCommandImp.hpp"
#include "elink/iec60870/details/io/util/NormalizedValueUtil.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class SetpointCommandScaledImp : public SetpointCommandImp<inherit, typeID>
{
public:
    SetpointCommandScaledImp()
    : SetpointCommandImp<inherit, typeID>{}, sValueM{0}
    {
    }

    SetpointCommandScaledImp(const IOA ioa, SEBit selectCommand, QLValue ql, const ScaledValue value)
    : SetpointCommandImp<inherit, typeID>{ioa, selectCommand, ql}, sValueM{value}
    {
    }

    ~SetpointCommandScaledImp() = default;

    [[nodiscard]] ScaledValue getValue() const
    {
        return sValueM;
    }

    void setValue(const ScaledValue value)
    {
        sValueM = value;
    }

protected:
    ScaledValue sValueM;
};

}
