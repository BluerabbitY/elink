/***********************************************************************************
 * \file SetpointCommandShortImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 20:52:58
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

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class SetpointCommandShortImp : public SetpointCommandImp<inherit, typeID>
{
public:
    SetpointCommandShortImp()
    : SetpointCommandImp<inherit, typeID>{}, sValueM{0.f}
    {
    }

    SetpointCommandShortImp(const IOA ioa, SEBit selectCommand, QLValue ql, const float value)
    : SetpointCommandImp<inherit, typeID>{ioa, selectCommand, ql}, sValueM{value}
    {
    }

    ~SetpointCommandShortImp() = default;

    [[nodiscard]] float getValue() const
    {
        return sValueM;
    }

    void setValue(const float value)
    {
        sValueM = value;
    }

protected:
    float sValueM;
};

}
