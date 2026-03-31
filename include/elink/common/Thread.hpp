/***********************************************************************************
 * \file Thread.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-18 16:35:28
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

#include "elink/common/details/thread/ThreadConcept.hpp"
#include "elink/common/details/thread/ThreadName.hpp"

#include <thread>
#include <stop_token>

namespace elink
{

template <typename T>
class Thread
{
public:

    enum StartMode : uint8_t { IMMEDIATE, DEFERRED };

    explicit Thread(const std::string_view threadName, const StartMode startMode = DEFERRED)
        : startModeM{startMode}, threadNameM{threadName}
    {
        static_assert(details::ThreadConcept<T>, "Derived class must satisfy ThreadConcept (implement entry)");

        if (startModeM == IMMEDIATE)
        {
            start();
        }
    }

    ~Thread() = default;

    void start()
    {
        if (startModeM == DEFERRED && threadM != nullptr)
        {
            threadM = std::make_unique<std::jthread>([this](const std::stop_token &st) { this->entry(st); });
        }
    }

    void stop() const
    {
        if (threadM)
        {
            threadM->request_stop();
        }
    }

protected:
    [[nodiscard]] bool resume() const
    {
        if (threadM)
        {
            return !threadM->get_stop_token().stop_requested();
        }

        return false;
    }

private:
    void entry(const std::stop_token&)
    {
        details::ThreadName::setThreadName(threadNameM);
        static_cast<T*>(this)->entry();
    }

    StartMode startModeM;
    std::unique_ptr<std::jthread> threadM;
    std::string threadNameM;
};

}
