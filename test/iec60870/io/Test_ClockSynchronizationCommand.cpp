/***********************************************************************************
 * \file Test_ClockSynchronizationCommand.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 17:54:28
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
#include "elink/iec60870/io/ClockSynchronizationCommand.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class ClockSynchronizationCommandTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(ClockSynchronizationCommandTest, TypeID)
{
    const ClockSynchronizationCommand io;
    EXPECT_EQ(io.getTypeID(), TypeID::C_CS_NA_1);
}

TEST_F(ClockSynchronizationCommandTest, IOLength)
{
    const ClockSynchronizationCommand io;
    EXPECT_EQ(io.size(), 10);
    EXPECT_EQ(io.length(true), 7);
}

TEST_F(ClockSynchronizationCommandTest, ClockSynchronizationCommandSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const ClockSynchronizationCommand::SerializePtr ios = std::make_shared<ClockSynchronizationCommand>(CP56Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(ClockSynchronizationCommandTest, ClockSynchronizationCommandDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x00, 0x00, 0xfa, 0xd3, 0xd1, 0x8e, 0xf5, 0x0c, 0x19};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<ClockSynchronizationCommand>();
    const ClockSynchronizationCommand::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

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
