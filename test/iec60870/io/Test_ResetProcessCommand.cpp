/***********************************************************************************
 * \file Test_ResetProcessCommand.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-12 00:31:06
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
#include "elink/iec60870/io/ResetProcessCommand.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class ResetProcessCommandTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(ResetProcessCommandTest, TypeID)
{
    const ResetProcessCommand io;
    EXPECT_EQ(io.getTypeID(), TypeID::C_RP_NA_1);
}

TEST_F(ResetProcessCommandTest, IOLength)
{
    const ResetProcessCommand io;
    EXPECT_EQ(io.size(), 4);
    EXPECT_EQ(io.length(true), 1);
}

TEST_F(ResetProcessCommandTest, CommonImpValue)
{
    ResetProcessCommand io;

    EXPECT_EQ(io.getQRP(), QRP::NOT_USED);
    io.setQRP(QRP::GENERAL_RESET);
    EXPECT_EQ(io.getQRP(), QRP::GENERAL_RESET);
}

TEST_F(ResetProcessCommandTest, EndOfInitializationSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const ResetProcessCommand::SerializePtr ios = std::make_shared<ResetProcessCommand>(QRP::GENERAL_RESET);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x00, 0x00, 0x01};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(ResetProcessCommandTest, EndOfInitializationDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x00, 0x00, 0x02};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<ResetProcessCommand>();
    const ResetProcessCommand::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x00);
    EXPECT_EQ(io->getQRP(), QRP::RESET_PENDING_INFO_WITH_TIME_TAG);
}
