/***********************************************************************************
 * \file PollerPosix.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 11:18:42
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

#include <chrono>
#include <poll.h>

namespace elink::details
{

class PlatformPollerImp
{
public:
    static Result<int> poll(PollEntrys& entries, const std::chrono::milliseconds timeout)
    {
        std::vector<pollfd> fds{entries.size()};

        for (auto i = 0; i < entries.size(); i++)
        {
            fds[i].fd = entries[i].handle;
            fds[i].events = POLLIN;
            fds[i].revents = 0;
            entries[i].ready = false;
        }

        const int result = ::poll(fds.data(), fds.size(), timeout.count());

        if (result < 0)
        {
            return {ErrorCode::PollFailed, 0, "poll() failed: " + std::string{std::strerror(errno)}, errno};
        }

        if (result == 0)
        {
            return {ErrorCode::Timeout, 0, "poll() timed out"};
        }

        int ready = 0;

        for (auto i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLIN)
            {
                entries[i].ready = true;
                ready++;
            }
        }

        return {ErrorCode::Success, ready};
    }

private:
    PlatformPollerImp() = default;
    ~PlatformPollerImp() = default;
};

}
