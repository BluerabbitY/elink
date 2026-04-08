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

#include "elink/iec60870/details/io/StatusCommandImp.hpp"

namespace elink::iec60870
{

using SingleCommandValue = bool;

namespace details {

template <typename inherit, TypeID typeID>
class SingleCommandImp : public StatusCommandImp<inherit, typeID, SingleCommandValue>
{
public:
    SingleCommandImp()
    : StatusCommandImp<inherit, typeID, SingleCommandValue>{}
    {
    }

    SingleCommandImp(const IOA ioa, const SEBit selectCommand, const QUValue qu, const SingleCommandValue command)
    : StatusCommandImp<inherit, typeID, SingleCommandValue>{ioa, selectCommand, qu, command}
    {
    }

    ~SingleCommandImp() = default;
};

}
}
