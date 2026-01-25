/***********************************************************************************
 * \file Thread.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-18 16:35:28
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#include "elink/common/details/Platform.hpp"

#if (ELINK_PLATFORM == ELINK_WIN32)
#include <windows.h>
#include <processthreadsapi.h>
#include <wstring>
#elif (ELINK_PLATFORM == ELINK_LINUX || ELINK_PLATFORM == ELINK_UNIX || ELINK_PLATFORM == ELINK_APPLE)
#include <pthread.h>
#endif

#include <thread>
#include <stop_token>

namespace elink
{

namespace details {

template <typename T>
concept ThreadConcept = requires(T& t) {
    { t.entry() } -> std::same_as<void>;
};

class ThreadName
{
public:
    static void setThreadName(const std::string& threadName)
    {
        if (!threadNameS.empty())
            return;

        threadNameS = threadName;

        // Regardless of the platform,
        // follow Linux naming conventions to ensure that thread names are the same on any platform.
        const std::string limitedThreadName = threadName.size() > 15 ? threadName.substr(0, 15) : threadName;
#if (ELINK_PLATFORM == ELINK_WIN32)
        const std::wstring winThreadName{limitedThreadName.begin(), limitedThreadName.end()};
        SetThreadDescription(GetCurrentThread(), winThreadName.c_str());
#elif (ELINK_PLATFORM == ELINK_LINUX || ELINK_PLATFORM == ELINK_UNIX)
        pthread_setname_np(pthread_self(), limitedThreadName.c_str());
#elif (ELINK_PLATFORM == ELINK_APPLE)
        pthread_setname_np(limitedThreadName.c_str());
#endif
    }

    static std::string threadName()
    {
        if (threadNameS.empty())
        {
            return threadId();
        }

        return threadNameS;
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

    thread_local static inline std::string threadNameS{};
};

}

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
