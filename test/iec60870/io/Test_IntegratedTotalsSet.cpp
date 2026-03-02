/***********************************************************************************
 * \file Test_IntegratedTotalsSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-02 22:27:26
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
#include "elink/iec60870/io/IntegratedTotals.hpp"
#include "elink/iec60870/io/IntegratedTotalsWithCP24Time2a.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class IntegratedTotalsSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(IntegratedTotalsSetTest, TypeID)
{
    const IntegratedTotals io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_IT_NA_1);

    const IntegratedTotalsWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.getTypeID(), TypeID::M_IT_TA_1);
}

TEST_F(IntegratedTotalsSetTest, IOLength)
{
    const IntegratedTotals io;
    EXPECT_EQ(io.size(), 8);
    EXPECT_EQ(io.length(true), 5);

    const IntegratedTotalsWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.size(), 11);
    EXPECT_EQ(iocp24.length(true), 8);
}

TEST_F(IntegratedTotalsSetTest, CommonImpValue)
{
    const BinaryCounterReading bcr1{32768, 1, true, false, true};
    const BinaryCounterReading bcr2{32768, 1, true, false, true};
    IntegratedTotals io{IOA{0x200}, bcr1};

    EXPECT_EQ(io.getBCR(), bcr1);
    io.setBCR(bcr2);
    EXPECT_EQ(io.getBCR(), bcr2);
}

TEST_F(IntegratedTotalsSetTest, IntegratedTotalsSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};
    const BinaryCounterReading bcr{32768, 1, true, false, true};

    const IntegratedTotals::SerializePtr ios = std::make_shared<IntegratedTotals>(IOA{0x200}, bcr);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x00, 0xa1};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(IntegratedTotalsSetTest, IntegratedTotalsDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x00, 0x80, 0x00, 0x00, 0xa1};
    details::IStream is{buffer, sizeof(buffer)};
    const BinaryCounterReading bcr{32768, 1, true, false, true};

    const auto io = std::make_shared<IntegratedTotals>();
    const IntegratedTotals::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getBCR(), bcr);
}

TEST_F(IntegratedTotalsSetTest, IntegratedTotalsWithCP24Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};
    const BinaryCounterReading bcr{32768, 1, true, false, true};

    const IntegratedTotalsWithCP24Time2a::SerializePtr ios =
        std::make_shared<IntegratedTotalsWithCP24Time2a>(IOA{0x200}, bcr, CP24Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x00, 0xa1, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(IntegratedTotalsSetTest, IntegratedTotalsWithCP24Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x00, 0x80, 0x00, 0x00, 0xa1, 0xdc, 0xe6, 0xfb};
    details::IStream is{buffer, sizeof(buffer)};
    const BinaryCounterReading bcr{32768, 1, true, false, true};

    const auto io = std::make_shared<IntegratedTotalsWithCP24Time2a>();
    const IntegratedTotalsWithCP24Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getBCR(), bcr);

    auto cp24Time2a = io->getTimestamp();
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    EXPECT_TRUE(cp24Time2a.isInvalid());
    EXPECT_TRUE(cp24Time2a.isSubstituted());
}
