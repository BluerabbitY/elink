/***********************************************************************************
 * \file PlatformPollerImpWindows.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 11:58:12
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

#if (ELINK_COMPILER == ELINK_COMPILER_MSVC)
#pragma coment(lib, "Ws2_32.lib")
#endif

namespace elink::details
{

class PlatformPollerImp
{
public:
    static Result<int> poll(PollEntrys& entries, const std::chrono::milliseconds timeout)
    {
        std::vector<WSAPOLLFD> fds{entries.size()};

        for (auto i = 0; i < entries.size(); i++)
        {
            fds[i].fd = entries[i].handle;
            fds[i].events = POLLRDNORM;
            fds[i].revents = 0;
            entries[i].ready = false;
        }

        const int result = ::WSAPoll(fds.data(), fds.size(), timeout.count());

        if (result == SOCKET_ERROR)
        {
            return {ErrorCode::PollFailed, 0, "WSAPoll() failed: " + std::to_string(::WSAGetLastError()), ::WSAGetLastError()};
        }

        if (result == 0)
        {
            return {ErrorCode::Timeout, 0, "WSAPoll() timed out",};
        }

        int ready = 0;

        for (auto i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLRDNORM)
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
