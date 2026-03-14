/***********************************************************************************
 * \file SingleCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 10:34:30
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

using SingleCommandValue = bool;

namespace details {

template <typename inherit, TypeID typeID>
class SingleCommandImp : public CommandImp<inherit, typeID>
{
public:
    SingleCommandImp()
    : CommandImp<inherit, typeID>{}
    {
    }

    SingleCommandImp(const IOA ioa, const SEBit selectCommand, const QUValue qu, const SingleCommandValue command)
    : CommandImp<inherit, typeID>{ioa, selectCommand, qu}
    {
        setState(command);
    }

    ~SingleCommandImp() = default;

    /**
     * \brief Get the state (command) value
     */
    [[nodiscard]] bool getState() const
    {
        return this->valueM & 0x01;
    }

    void setState(const bool state)
    {
        state ? this->valueM |= 0x01 : this->valueM &= 0xfe;
    }
};

}
}
