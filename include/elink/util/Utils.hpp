/***********************************************************************************
 * \file Utils.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-26 00:06:46
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

#include <cassert>

#ifndef ELINK_ASSERT
#define ELINK_ASSERT(x) assert(x)
#endif

#ifndef ELINK_STATIC_ASSERT
#define ELINK_STATIC_ASSERT(x, ...) static_assert(x __VA_OPT__(,) __VA_ARGS__)
#endif

namespace elink::util
{

}
