/***********************************************************************************
 * \file Test_CPXXTime2a.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test for CPxxTime2a
 * \date 2025-12-20 13:05:00
 * 
 * \copyright Copyright (C) 2025-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ***********************************************************************************/
#include "elink/iec60870/CPxxTime2a.hpp"

#include <gtest/gtest.h>

class CPXXTime2aTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    elink::iec60870::CP16Time2a cp16Time2a{};
    elink::iec60870::CP24Time2a cp24Time2a{};
    elink::iec60870::CP32Time2a cp32Time2a{};
    elink::iec60870::CP56Time2a cp56Time2a{};
};

TEST_F(CPXXTime2aTest, CP16Time2a)
{
    cp16Time2a.setEplapsedTimeInMs(100);
    EXPECT_EQ(cp16Time2a.getEplapsedTimeInMs(), 100);
    cp16Time2a.setEplapsedTimeInMs(65535);
    EXPECT_EQ(cp16Time2a.getEplapsedTimeInMs(), 59999);
}

TEST_F(CPXXTime2aTest, CP24Time2a)
{
    cp24Time2a.setMillisecond(100);
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    cp24Time2a.setMillisecond(1000);
    EXPECT_EQ(cp24Time2a.getMillisecond(), 999);

    cp24Time2a.setSecond(59);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    cp24Time2a.setSecond(61);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);

    cp24Time2a.setMinute(59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    cp24Time2a.setMinute(61);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);

    EXPECT_FALSE(cp24Time2a.isInvalid());
    cp24Time2a.setInvalid(true);
    EXPECT_TRUE(cp24Time2a.isInvalid());

    EXPECT_FALSE(cp24Time2a.isSubstituted());
    cp24Time2a.setSubstituted(true);
    EXPECT_TRUE(cp24Time2a.isSubstituted());
}

TEST_F(CPXXTime2aTest, CP32Time2a)
{
    cp32Time2a.setHour(22);
    EXPECT_EQ(cp32Time2a.getHour(), 22);
    cp32Time2a.setHour(27);
    EXPECT_EQ(cp32Time2a.getHour(), 23);

    EXPECT_FALSE(cp32Time2a.isSummerTime());
    cp32Time2a.setSummerTime(true);
    EXPECT_TRUE(cp32Time2a.isSummerTime());
}

TEST_F(CPXXTime2aTest, CP56Time2a)
{
    cp56Time2a.setDayOfWeek(3);
    EXPECT_EQ(cp56Time2a.getDayOfWeek(), 3);
    cp56Time2a.setDayOfWeek(8);
    EXPECT_EQ(cp56Time2a.getDayOfWeek(), 7);

    cp56Time2a.setDayOfMonth(27);
    EXPECT_EQ(cp56Time2a.getDayOfMonth(), 27);
    cp56Time2a.setDayOfMonth(32);
    EXPECT_EQ(cp56Time2a.getDayOfMonth(), 31);

    cp56Time2a.setMonth(10);
    EXPECT_EQ(cp56Time2a.getMonth(), 10);
    cp56Time2a.setMonth(13);
    EXPECT_EQ(cp56Time2a.getMonth(), 12);

    cp56Time2a.setYear(2025);
    EXPECT_EQ(cp56Time2a.getYear(), 2025);

    cp56Time2a.setMillisecond(266);
    cp56Time2a.setSecond(54);
    cp56Time2a.setMinute(17);
    cp56Time2a.setHour(14);
    cp56Time2a.setDayOfMonth(21);
    cp56Time2a.setMonth(12);
    cp56Time2a.setYear(2025);

    EXPECT_EQ(cp56Time2a.toMsTimestamp(), 1766297874266);
}
