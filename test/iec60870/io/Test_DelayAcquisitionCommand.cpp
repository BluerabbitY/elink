/***********************************************************************************
 * \file Test_DelayAcquisitionCommand.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-12 12:04:54
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
#include "elink/iec60870/io/DelayAcquisitionCommand.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class DelayAcquisitionCommandTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(DelayAcquisitionCommandTest, TypeID)
{
    const DelayAcquisitionCommand io;
    EXPECT_EQ(io.getTypeID(), TypeID::C_CD_NA_1);
}

TEST_F(DelayAcquisitionCommandTest, IOLength)
{
    const DelayAcquisitionCommand io;
    EXPECT_EQ(io.size(), 5);
    EXPECT_EQ(io.length(true), 2);
}

TEST_F(DelayAcquisitionCommandTest, DelayAcquisitionCommandSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const DelayAcquisitionCommand::SerializePtr ios = std::make_shared<DelayAcquisitionCommand>(CP16Time2a{12345});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x00, 0x00, 0x39, 0x30};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(DelayAcquisitionCommandTest, DelayAcquisitionCommandDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x00, 0x00, 0x39, 0x30};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<DelayAcquisitionCommand>();
    const DelayAcquisitionCommand::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x00);
    EXPECT_EQ(io->getTimestamp().getEplapsedTimeInMs(), 12345);
}
