/***********************************************************************************
 * \file DelayAcquisitionCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-12 11:07:14
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

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class DelayAcquisitionCommandImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    DelayAcquisitionCommandImp() = default;

    ~DelayAcquisitionCommandImp() = default;
};

}
