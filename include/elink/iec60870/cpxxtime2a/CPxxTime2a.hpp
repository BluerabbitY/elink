/***********************************************************************************
 * \file CPXXTime2A.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2025-12-20 10:12:15
 * 
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#include <array>
#include <ctime>
#include <chrono>

namespace elink::iec60870 {

namespace internal {

constexpr auto CP16Time2aTag = 2;
constexpr auto CP24Time2aTag = 3;
constexpr auto CP32Time2aTag = 4;
constexpr auto CP56Time2aTag = 7;

template <typename T>
const uint8_t* getCPxxTime2aData(const T& cpxxtime2a)
{
    return cpxxtime2a.bufferM.data();
}

template <typename T>
constexpr std::size_t getCPxxTime2aLength(const T& cpxxtime2a)
{
    return cpxxtime2a.bufferM.size();
}

template <std::size_t N>
class CPxxTime2a {
public:
    CPxxTime2a() = default;

    explicit CPxxTime2a(const uint64_t timestamp) requires (N == CP32Time2aTag || N == CP56Time2aTag)
    {
        const auto timeVal = static_cast<time_t>(timestamp / 1000);
        const int msPart = static_cast<int>(timestamp % 1000);

        std::tm tmTime{};

        gmtime(timeVal, tmTime);

        setMillisecond(msPart);
        setSecond(tmTime.tm_sec);
        setMinute(tmTime.tm_min);
        setHour(tmTime.tm_hour);

        if constexpr (N == CP56Time2aTag)
        {
            setDayOfWeek(tmTime.tm_wday + 1);
            setDayOfMonth(tmTime.tm_mday);
            setMonth(tmTime.tm_mon + 1);
            setYear(tmTime.tm_year);
        }
    }

    ~CPxxTime2a() = default;

    CPxxTime2a(const CPxxTime2a&) = default;

    CPxxTime2a(CPxxTime2a&) = default;

    CPxxTime2a& operator=(const CPxxTime2a&) = default;

    [[nodiscard]] uint16_t getEplapsedTimeInMs() const requires (N == CP16Time2aTag)
    {
        return bufferM[0] + (bufferM[1] * 0x100);
    }

    void setEplapsedTimeInMs(uint16_t value) requires (N == CP16Time2aTag)
    {
        value = std::clamp<uint16_t>(value, 0, 59999);
        bufferM[0] = static_cast<uint8_t>(value % 0x100);
        bufferM[1] = static_cast<uint8_t>(value / 0x100);
    }

    [[nodiscard]] int getMillisecond() const requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        return (bufferM[0] + bufferM[1] * 0x100) % 1000;
    }

    void setMillisecond(int value) requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        // according to IEC60870-5-4
        value = std::clamp(value, 0, 999);

        const int millies = getSecond() * 1000 + value;

        bufferM[0] = static_cast<uint8_t>(millies & 0xff);
        bufferM[1] = static_cast<uint8_t>((millies / 0x100) & 0xff);
    }

    [[nodiscard]] int getSecond() const requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        return (bufferM[0] + (bufferM[1] * 0x100)) / 1000;
    }

    void setSecond(int value) requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        value = std::clamp(value, 0, 59);

        int millies = bufferM[0] + (bufferM[1] * 0x100);

        const int msPart = millies % 1000;

        millies = (value * 1000) + msPart;

        bufferM[0] = static_cast<uint8_t>(millies & 0xff);
        bufferM[1] = static_cast<uint8_t>((millies / 0x100) & 0xff);
    }

    [[nodiscard]] int getMinute() const requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        return bufferM[2] & 0x3f;
    }

    void setMinute(int value) requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        value = std::clamp(value, 0, 59);
        bufferM[2] = static_cast<uint8_t>(bufferM[2] & 0xc0) | (value & 0x3f);
    }

    [[nodiscard]] bool isInvalid() const requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        return (bufferM[2] & 0x80) != 0;
    }

    void setInvalid(const bool value) requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        value ? (bufferM[2] |= 0x80) : (bufferM[2] &= 0x7f);
    }

    [[nodiscard]] bool isSubstituted() const requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        return (bufferM[2] & 0x40) == 0x40;
    }

    void setSubstituted(const bool value) requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        value ? (bufferM[2] |= 0x40) : (bufferM[2] &= 0xbf);
    }

    [[nodiscard]] int getHour() const requires (N == CP32Time2aTag || N == CP56Time2aTag)
    {
        return bufferM[3] & 0x1f;
    }

    void setHour(int value) requires (N == CP32Time2aTag || N == CP56Time2aTag)
    {
        value = std::clamp(value, 0, 23);
        bufferM[3] = static_cast<uint8_t>((bufferM[3] & 0xe0) | (value & 0x1f));
    }

    [[nodiscard]] bool isSummerTime() const requires (N == CP32Time2aTag || N == CP56Time2aTag)
    {
        return (bufferM[3] & 0x80) != 0;
    }

    void setSummerTime(const bool value) requires (N == CP32Time2aTag || N == CP56Time2aTag)
    {
        value ? (bufferM[3] |= 0x80) : (bufferM[3] &= 0x7f);
    }

    [[nodiscard]] int getDayOfWeek() const requires (N == CP56Time2aTag)
    {
        return (bufferM[4] & 0xe0) >> 5;
    }

    void setDayOfWeek(int value) requires (N == CP56Time2aTag)
    {
        value = std::clamp(value, 0, 7);
        bufferM[4] = (bufferM[4] & 0x1f) | ((value & 0x07) << 5);
    }

    [[nodiscard]] int getDayOfMonth() const requires (N == CP56Time2aTag)
    {
        return bufferM[4] & 0x1f;
    }

    void setDayOfMonth(int value) requires (N == CP56Time2aTag)
    {
        value = std::clamp(value, 1, 31);
        bufferM[4] = static_cast<uint8_t>((bufferM[4] & 0xe0) + (value & 0x1f));
    }

    [[nodiscard]] int getMonth() const requires (N == CP56Time2aTag)
    {
        return bufferM[5] & 0x0f;
    }

    void setMonth(int value) requires (N == CP56Time2aTag)
    {
        value = std::clamp(value, 1, 12);
        bufferM[5] = static_cast<uint8_t>((bufferM[5] & 0xf0) + (value & 0x0f));
    }

    [[nodiscard]] int getYear(const int startYear = 2000) const requires (N == CP56Time2aTag)
    {
        return (bufferM[6] & 0x7f) + startYear;
    }

    void setYear(int value) requires (N == CP56Time2aTag)
    {
        value = value % 100;
        bufferM[6] = static_cast<uint8_t>((bufferM[6] & 0x80) + (value & 0x7f));
    }

    [[nodiscard]] uint64_t toMsTimestamp() const requires (N == CP56Time2aTag)
    {
        std::tm tmTime{};

        tmTime.tm_sec = getSecond();
        tmTime.tm_min = getMinute();
        tmTime.tm_hour = getHour();
        tmTime.tm_mday = getDayOfMonth();
        tmTime.tm_mon = getMonth() - 1;
        tmTime.tm_year = getYear(0) + 100;

        const uint64_t msTimestamp = std::mktime(&tmTime) * static_cast<uint64_t>(1000) + getMillisecond();

        return msTimestamp;
    }

    static CPxxTime2a now() requires (N == CP24Time2aTag || N == CP32Time2aTag || N == CP56Time2aTag)
    {
        const auto now = std::chrono::system_clock::now();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::tm tm{};
        gmtime(std::chrono::system_clock::to_time_t(now), tm);

        CPxxTime2a cpxxtime2a;

        if constexpr (N == CP24Time2aTag)
        {
            cpxxtime2a.setMillisecond(millis.count());
            cpxxtime2a.setSecond(tm.tm_sec);
            cpxxtime2a.setMinute(tm.tm_min);
        }

        if constexpr (N == CP32Time2aTag)
        {
            cpxxtime2a.setHour(tm.tm_hour);
        }

        if constexpr (N == CP56Time2aTag)
        {
            cpxxtime2a.setDayOfWeek(tm.tm_wday + 1);
            cpxxtime2a.setDayOfMonth(tm.tm_mday);
            cpxxtime2a.setMonth(tm.tm_mon + 1);
            cpxxtime2a.setYear(tm.tm_year);
        }

        return cpxxtime2a;
    }

protected:
    template <typename T>
    friend const uint8_t* getCPxxTime2aData(const T& cpxxtime2a);

    template <typename T>
    friend constexpr std::size_t getCPxxTime2aLength(const T& cpxxtime2a);

private:
    static std::tm* gmtime(const time_t& in, std::tm& out)
    {
#ifdef _WIN32
        return gmtime_s(&in, &out);
#else
        return gmtime_r(&in, &out);
#endif
    }

    std::array<uint8_t, N> bufferM;
};

}

using CP16Time2a = internal::CPxxTime2a<internal::CP16Time2aTag>;
using CP24Time2a = internal::CPxxTime2a<internal::CP24Time2aTag>;
using CP32Time2a = internal::CPxxTime2a<internal::CP32Time2aTag>;
using CP56Time2a = internal::CPxxTime2a<internal::CP56Time2aTag>;

}