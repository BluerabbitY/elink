/***********************************************************************************
 * \file NativeHandleWindows.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 11:12:09
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

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <winsock2.h>

namespace elink::details
{

using PollHandle = SOCKET;
inline constexpr PollHandle INVALID_HANDLE = INVALID_SOCKET;

}
