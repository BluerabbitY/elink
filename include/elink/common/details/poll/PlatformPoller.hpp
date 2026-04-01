/***********************************************************************************
 * \file PlatformPoller.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 11:20:01
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

#include "elink/common/Result.hpp"
#include "elink/common/details/poll/PollEntry.hpp"

#if (ELINK_API == ELINK_API_WIN32)
#include "elink/common/details/poll/PlatformPollerImpWindows.hpp"
#elif (ELINK_API == ELINK_API_POSIX)
#include "elink/common/details/poll/PlatformPollerImpPosix.hpp"
#else
#error "Unsupported platform"
#endif

namespace elink::details
{

class PlatformPoller
{
public:
    /// Poll multiple handles for readability
    /// @param entries Input/output: handle field is input, ready field is output
    /// @param timeout Maximum time to wait
    /// @return Success with at lwast one ready=true, Timeout if none ready, or PollFailed on error
    static Result<int> poll(PollEntrys& entries, const std::chrono::milliseconds timeout)
    {
        return PlatformPollerImp::poll(entries, timeout);
    }
};

}
