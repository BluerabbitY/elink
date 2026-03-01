/***********************************************************************************
 * \file Test_OStream.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test OStream
 * \date 2025-12-15 23:00:51
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
#include "elink/iec60870/details/codec/OStream.hpp"

#include <gtest/gtest.h>
#include <cstring>

class OStreamTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    uint8_t buffer[256]{};
    elink::iec60870::details::OStream stream{buffer, sizeof(buffer)};
};

TEST_F(OStreamTest, WriteIOA)
{
    std::size_t length = 0;
    const elink::iec60870::IOA ioa1(0x1234, elink::iec60870::IOAByteLength::Two);
    stream << ioa1;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.size(), static_cast<int>(elink::iec60870::IOAByteLength::Two));

    length = stream.size();
    const elink::iec60870::IOA ioa2(0x123456);
    stream << ioa2;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.size(), length + static_cast<int>(elink::iec60870::IOAByteLength::Three));

    constexpr uint8_t dest[] = {0x34, 0x12, 0x56, 0x34, 0x12};
    EXPECT_EQ(stream.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamTest, WriteCPxxtime2a)
{
    std::size_t length = 0;
    elink::iec60870::CP16Time2a cp16Time2a{};
    cp16Time2a.setEplapsedTimeInMs(100);
    stream << cp16Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::details::CP16Time2aTag;
    EXPECT_EQ(stream.size(), length);

    elink::iec60870::CP24Time2a cp24Time2a{};
    cp24Time2a.setMillisecond(100);
    cp24Time2a.setSecond(59);
    cp24Time2a.setMinute(59);
    cp24Time2a.setInvalid(true);
    cp24Time2a.setSubstituted(true);
    stream << cp24Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::details::CP24Time2aTag;
    EXPECT_EQ(stream.size(), length);

    elink::iec60870::CP32Time2a cp32Time2a{};
    cp32Time2a.setHour(22);
    cp32Time2a.setSummerTime(true);
    stream << cp32Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::details::CP32Time2aTag;
    EXPECT_EQ(stream.size(), length);

    elink::iec60870::CP56Time2a cp56Time2a{};
    cp56Time2a.setDayOfWeek(3);
    cp56Time2a.setDayOfMonth(27);
    cp56Time2a.setYear(2025);
    stream << cp56Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::details::CP56Time2aTag;
    EXPECT_EQ(stream.size(), length);

    constexpr uint8_t dest[] = {0x64, 0x00, 0xdc, 0xe6, 0xfb, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x00, 0x7b,
                                0x00, 0x19};
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamTest, WriteBitString32Value)
{
    uint8_t buffer[] = {};
    constexpr uint8_t dest[] = {0x55, 0x55, 0x55, 0x55};

    elink::iec60870::details::OStream stream{buffer, sizeof(dest)};
    const elink::iec60870::BitString32Value bs32Value{"01010101010101010101010101010101"};

    stream << bs32Value;

    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}