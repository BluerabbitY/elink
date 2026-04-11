/***********************************************************************************
 * \file Test_CounterInterrogationCommand.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 16:54:51
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
#include "elink/iec60870/io/CounterInterrogationCommand.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class CounterInterrogationCommandTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(CounterInterrogationCommandTest, TypeID)
{
    const CounterInterrogationCommand io;
    EXPECT_EQ(io.getTypeID(), TypeID::C_CI_NA_1);
}

TEST_F(CounterInterrogationCommandTest, IOLength)
{
    const CounterInterrogationCommand io;
    EXPECT_EQ(io.size(), 4);
    EXPECT_EQ(io.length(true), 1);
}

TEST_F(CounterInterrogationCommandTest, CommonImpValue)
{
    CounterInterrogationCommand io;

    EXPECT_EQ(io.getQCC().getQCCRequest(), QCCRequest::GENERAL);
    EXPECT_EQ(io.getQCC().getQCCFreeze(), QCCFreeze::READ);
    io.setQCC(QCC{QCCRequest::GROUP_3, QCCFreeze::FREEZE_WITHOUT_RESET});
    EXPECT_EQ(io.getQCC().getQCCRequest(), QCCRequest::GROUP_3);
    EXPECT_EQ(io.getQCC().getQCCFreeze(), QCCFreeze::FREEZE_WITHOUT_RESET);
}

TEST_F(CounterInterrogationCommandTest, EndOfInitializationSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const CounterInterrogationCommand::SerializePtr ios =
        std::make_shared<CounterInterrogationCommand>(QCC{QCCRequest::GROUP_3, QCCFreeze::FREEZE_WITHOUT_RESET});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x00, 0x00, 0x43};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(CounterInterrogationCommandTest, EndOfInitializationDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x00, 0x00, 0x43};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<CounterInterrogationCommand>();
    const CounterInterrogationCommand::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x00);
    EXPECT_EQ(io->getQCC().getQCCRequest(), QCCRequest::GROUP_3);
    EXPECT_EQ(io->getQCC().getQCCFreeze(), QCCFreeze::FREEZE_WITHOUT_RESET);
}
