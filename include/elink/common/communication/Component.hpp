/***********************************************************************************
 * \file Component.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-11 16:30:11
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

#include "elink/common/thread/Thread.hpp"

#include <asio/io_context.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>

namespace elink
{

class Component;

namespace detail {
inline asio::io_context& getIOcontext(Component& component);
}

class Component
{
public:
    Component() : runningM{false}, workGuardM{asio::make_work_guard(ioM)}
    {
    }

    ~Component() = default;

    void runOnThisThread()
    {
        if (bool expected = false; runningM.compare_exchange_strong(expected, true))
        {
            ioM.run();
        }
    }

    void runOnNewThread(std::string_view threadName = "ComponentThread")
    {
        if (bool expected = false; runningM.compare_exchange_strong(expected, true))
        {
            componentThreadM = std::make_unique<ComponentThread>(threadName, *this);
        }
    }

    template <typename F, typename... Args>
    void addHandler(F&& f, Args&&... args)
    {
        asio::co_spawn(ioM,
            [func = std::forward<F>(f), tup = std::make_tuple(std::forward<Args>(args)...) ]() mutable -> asio::awaitable<void>
            {
                co_await std::apply(func, std::move(tup));
            }, asio::detached);
    }

    void stop()
    {
        if (runningM.load(std::memory_order_acquire))
        {
            workGuardM.reset();
            ioM.stop();
        }
    }

    friend inline asio::io_context& detail::getIOcontext(Component& component);

private:
    void run()
    {
        runningM = true;
        ioM.run();
    }

    class ComponentThread : public Thread<ComponentThread>
    {
    public:
        explicit ComponentThread(const std::string_view threadName, Component& component)
        : Thread{threadName, IMMEDIATE}, componentM{component}
        {

        }

        ~ComponentThread() = default;

        friend class Thread;

    private:
        void entry() const
        {
            componentM.ioM.run();
            componentM.runningM = false;
        }

        Component& componentM;
    };

    std::atomic_bool runningM;
    std::unique_ptr<ComponentThread> componentThreadM;
    asio::io_context ioM;
    asio::executor_work_guard<asio::io_context::executor_type> workGuardM;
};

namespace detail
{
inline asio::io_context& getIOcontext(Component& component)
{
    return component.ioM;
}
}

}
