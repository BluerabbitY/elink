/***********************************************************************************
 * \file StepCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 21:38:59
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

/**
 * \brief Regulating step command state (RCS) according to IEC 60870-5-101:2003 7.2.6.17
 */
enum class StepCommandValue {
    INVALID_0 = 0,
    LOWER = 1,
    HIGHER = 2,
    INVALID_3 = 3
};

namespace details
{

template <typename inherit, TypeID typeID>
class StepCommandImp : public CommandImp<inherit, typeID, StepCommandValue>
{
public:
    StepCommandImp()
    : CommandImp<inherit, typeID, StepCommandValue>{}
    {
        CommandImp<inherit, typeID, StepCommandValue>::setState(StepCommandValue::LOWER);
    }

    StepCommandImp(const IOA ioa, SEBit selectCommand, QUValue qu, StepCommandValue command)
    : CommandImp<inherit, typeID, StepCommandValue>{ioa, selectCommand, qu, command}
    {
    }

    ~StepCommandImp() = default;
};

}
}
