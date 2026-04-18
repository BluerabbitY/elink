/***********************************************************************************
 * \file Test_TestCommand.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 18:57:09
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
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
#include "elink/iec60870/io/TestCommand.hpp"
#include "elink/iec60870/io/TestCommandWithCP56Time2a.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class TestCommandTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(TestCommandTest, TypeID)
{
    const TestCommand io;
    EXPECT_EQ(io.getTypeID(), TypeID::C_TS_NA_1);

    const TestCommandWithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.getTypeID(), TypeID::C_TS_TA_1);
}

TEST_F(TestCommandTest, IOLength)
{
    const TestCommand io;
    EXPECT_EQ(io.size(), 5);
    EXPECT_EQ(io.length(true), 2);

    const TestCommandWithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.size(), 12);
    EXPECT_EQ(iocp56.length(true), 9);
}

TEST_F(TestCommandTest, CommonImpValue)
{
    TestCommand io;

    EXPECT_TRUE(io.isValid());
    io.setIsValid(false);
    EXPECT_FALSE(io.isValid());

    TestCommandWithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.getCounter(), 0);
    iocp56.setCounter(12345);
    EXPECT_EQ(iocp56.getCounter(), 12345);
}

TEST_F(TestCommandTest, TestCommandSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const TestCommand::SerializePtr ios = std::make_shared<TestCommand>();
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x00, 0x00, 0xaa, 0x55};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(TestCommandTest, TestCommandDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x00, 0x00, 0xaa, 0x55};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<TestCommand>(false);
    const TestCommand::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x00);
    EXPECT_TRUE(io->isValid());
}

TEST_F(TestCommandTest, TestCommandWithCP56Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const TestCommandWithCP56Time2a::SerializePtr ios = std::make_shared<TestCommandWithCP56Time2a>(0x55aa, CP56Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x00, 0x00, 0xaa, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(TestCommandTest, TestCommandWithCP56Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x00, 0x00, 0xaa, 0x55, 0xfa, 0xd3, 0xd1, 0x8e, 0xf5, 0x0c, 0x19};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<TestCommandWithCP56Time2a>(false);
    const TestCommandWithCP56Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x00);
    EXPECT_EQ(io->getCounter(), 0x55aa);

    auto cp56Time2a = io->getTimestamp();
    EXPECT_TRUE(cp56Time2a.isInvalid());
    EXPECT_TRUE(cp56Time2a.isSummerTime());
    EXPECT_TRUE(cp56Time2a.isSubstituted());
    EXPECT_EQ(cp56Time2a.getMillisecond(), 266);
    EXPECT_EQ(cp56Time2a.getSecond(), 54);
    EXPECT_EQ(cp56Time2a.getMinute(), 17);
    EXPECT_EQ(cp56Time2a.getHour(), 14);
    EXPECT_EQ(cp56Time2a.getDayOfWeek(), 7);
    EXPECT_EQ(cp56Time2a.getDayOfMonth(), 21);
    EXPECT_EQ(cp56Time2a.getMonth(), 12);
    EXPECT_EQ(cp56Time2a.getYear(), 2025);
    EXPECT_EQ(cp56Time2a.toMsTimestamp(), 1766297874266);
}
