/***********************************************************************************
 * \file SetpointCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 19:12:36
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

#include "elink/iec60870/details/io/CommandImp.hpp"

namespace elink::iec60870
{

using QLValue = uint8_t;

namespace details
{

template <typename inherit, TypeID typeID>
class SetpointCommandImp : public CommandImp<inherit, typeID>
{
public:
    SetpointCommandImp() = default;

    SetpointCommandImp(const IOA ioa, const SEBit selectCommand, const QLValue ql)
    : CommandImp<inherit, typeID>{ioa, selectCommand}
    {
        setQL(ql);
    }

    [[nodiscard]] QLValue getQL() const
    {
        return (this->valueM & 0x7f);
    }

    void setQL(const QLValue ql)
    {
        this->valueM = this->valueM & 0x80 | (std::clamp<uint8_t>(ql, 0, 127) & 0x7f);
    }

    ~SetpointCommandImp() = default;
};

}
}
