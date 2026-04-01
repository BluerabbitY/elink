/***********************************************************************************
 * \file NativeHandle.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 11:11:22
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

#include "elink/common/Platform.h"

#if (ELINK_API == ELINK_API_WIN32)
#include "elink/common/details/handle/NativeHandleWindows.hpp"
#elif (ELINK_API == ELINK_API_POSIX)
#include "elink/common/details/handle/NativeHandlePosix.hpp"
#else
#error "Unsupported platform for Handle implementation"
#endif
