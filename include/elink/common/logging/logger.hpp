/***********************************************************************************
 * \file logger.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-09 00:25:41
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

#include "elink/common/Type.hpp"
#include "elink/config.h"

#include <string_view>
#include <format>
#include <functional>

namespace elink
{

class Log {
public:
    using LogHandler = std::function<void(LogLevel, std::string_view, int, const std::string&)>;

    template <typename... Args>
    static void print(const LogLevel level, const std::string_view file, const int line, std::format_string<Args...> fmt, Args&&... args)
    {
        if (logHandlerS && logOutputEnabledM)
        {
            const std::size_t pos = file.find_last_of("/\\");
            logHandlerS(level, pos == std::string_view::npos ? file : file.substr(pos + 1), line, std::format(fmt, std::forward<Args>(args)...));
        }
    }

    static void print(const LogLevel level, const std::string_view file, const int line, const std::string_view msg)
    {
        if (logHandlerS && logOutputEnabledM)
        {
            const std::size_t pos = file.find_last_of("/\\");
            logHandlerS(level, pos == std::string_view::npos ? file : file.substr(pos + 1), line, std::string(msg));
        }
    }

    static void enableLogOutput(const bool value = true)
    {
        logOutputEnabledM = value;
    }

    static void setLogOutputHanlder(const LogHandler &hanlder)
    {
        logHandlerS = hanlder;
    }

private:
    Log() = default;
    ~Log() = default;

    inline static LogHandler logHandlerS{};
    inline static bool logOutputEnabledM{true};
};

}

#if (CONFIG_LOG_OUTPUT == 1)
#define LOG(level, fmt, ...)  do{ elink::Log::print(level, __FILE__, __LINE__, fmt __VA_OPT__(,) __VA_ARGS__); } while(false)
#define DLOG(fmt, ...) LOG(elink::LogLevel::DBG, fmt __VA_OPT__(,) __VA_ARGS__)
#define ILOG(fmt, ...) LOG(elink::LogLevel::INF, fmt __VA_OPT__(,) __VA_ARGS__)
#define WLOG(fmt, ...) LOG(elink::LogLevel::WRN, fmt __VA_OPT__(,) __VA_ARGS__)
#define ELOG(fmt, ...) LOG(elink::LogLevel::ERR, fmt __VA_OPT__(,) __VA_ARGS__)
#define CLOG(fmt, ...) LOG(elink::LogLevel::CRI, fmt __VA_OPT__(,) __VA_ARGS__)
#define FLOG(fmt, ...) LOG(elink::LogLevel::FAT, fmt __VA_OPT__(,) __VA_ARGS__)
#define MSG(level, msg)  do{ elink::Log::print(level, __FILE__, __LINE__, msg); } while(false)
#else
#define LOG(...) do{ } while (false)
#define DLOG(...) do { } while(false)
#define ILOG(...) do { } while(false)
#define WLOG(...) do { } while(false)
#define ELOG(...) do { } while(false)
#define CLOG(...) do { } while(false)
#define FLOG(...) do { } while(false)
#define MSG(level, msg) do { } while(false)
#endif
