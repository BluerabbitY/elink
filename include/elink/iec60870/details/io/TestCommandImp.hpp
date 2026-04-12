/***********************************************************************************
 * \file TestCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 18:32:38
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

#include "InformationObjectSerializable.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class TestCommandImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    TestCommandImp()
    : valueM{0}
    {
    }

    explicit TestCommandImp(const uint16_t value)
    : valueM{value}
    {
    }

    ~TestCommandImp() = default;

protected:
    uint16_t valueM;
};

}
