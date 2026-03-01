/***********************************************************************************
 * \file InformationObjectUtil.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-25 01:19:34
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

#include "elink/util/Utils.hpp"
#include "elink/iec60870/io/InformationObject.hpp"

#include <type_traits>

namespace elink::iec60870
{

template <typename T>
T& io_cast(InformationObject& io)
{
    ELINK_ASSERT(T::IDENT_T == io.getTypeID());
    ELINK_STATIC_ASSERT(std::is_base_of_v<InformationObject, T>, "Derived must inherit from InformationObject");
    return static_cast<T&>(io);
}

}
