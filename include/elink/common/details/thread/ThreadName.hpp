/***********************************************************************************
 * \file ThreadName.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-31 22:59:21
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
#if (ELINK_PLATFORM == ELINK_WIN32)
#include "elink/common/details/thread/ThreadNameImpWindows.hpp"
#elif (ELINK_PLATFORM == ELINK_LINUX || ELINK_PLATFORM == ELINK_UNIX)
#include "elink/common/details/thread/ThreadNameImpPosix.hpp"
#elif (ELINK_PLATFORM == ELINK_APPLE)
#include "elink/common/details/thread/ThreadNameImpMacOS.hpp"
#else
#error "Unsupported platform for ThreadName implementation"
#endif

#include <sstream>

namespace elink::details
{

class ThreadName
{
public:
    static void setThreadName(const std::string& threadName)
    {
        if (!threadNameStorage().empty())
            return;

        threadNameStorage() = threadName;

        // Regardless of the platform,
        // follow Linux naming conventions to ensure that thread names are the same on any platform.
        const std::string limitedThreadName = threadName.size() > 15 ? threadName.substr(0, 15) : threadName;

        ThreadNameImp::setThreadName(limitedThreadName);
    }

    static std::string threadName()
    {
        if (threadNameStorage().empty())
        {
            return threadId();
        }

        return threadNameStorage();
    }

private:
    ThreadName() = default;
    ~ThreadName() = default;

    static const std::string& threadId()
    {
        thread_local std::string id = [] {
            std::stringstream ss;
            ss << std::this_thread::get_id();
            return ss.str();
        } ();

        return id;
    }

    static std::string& threadNameStorage()
    {
        // Header-only safe accessor: returns a reference to a function-local thread_local string.
        // This avoids emitting TLS init functions in every translation unit that includes this header.
        thread_local std::string s;
        return s;
    }
};

}
