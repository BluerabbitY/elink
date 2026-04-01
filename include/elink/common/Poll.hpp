/***********************************************************************************
 * \file Poll.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 14:04:15
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
#include "elink/util/Utils.hpp"
#include "elink/common/details/poll/PlatformPollConcept.hpp"

#if (ELINK_API == ELINK_API_WIN32)
#include "elink/common/details/poll/PlatformPollWindowsImp.hpp"
#elif (ELINK_API == ELINK_API_POSIX)
#include "elink/common/details/poll/PlatformPollWindowsImp.hpp"
#else
#error "Unsupported platform"
#endif

ELINK_STATIC_ASSERT(elink::details::PlatformPollConcept<elink::PlatformPoll>,
    "PlatformPoll doesn't satisfy PlatformPollConcept on current platform");
