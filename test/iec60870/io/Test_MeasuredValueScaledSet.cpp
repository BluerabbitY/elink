/***********************************************************************************
 * \file Test_MeasuredValueScaledSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-01 23:04:48
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
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
#include "elink/iec60870/io/MeasuredValueScaled.hpp"
#include "elink/iec60870/io/MeasuredValueScaledWithCP24Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueScaledWithCP56Time2a.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class MeasuredValueScaledSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(MeasuredValueScaledSetTest, TypeID)
{
    const MeasuredValueScaled io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_ME_NB_1);

    const MeasuredValueScaledWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.getTypeID(), TypeID::M_ME_TB_1);

    const MeasuredValueScaledWithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.getTypeID(), TypeID::M_ME_TE_1);
}

TEST_F(MeasuredValueScaledSetTest, IOLength)
{
    const MeasuredValueScaled io;
    EXPECT_EQ(io.size(), 6);
    EXPECT_EQ(io.length(true), 3);

    const MeasuredValueScaledWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.size(), 9);
    EXPECT_EQ(iocp24.length(true), 6);

    const MeasuredValueScaledWithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.size(), 13);
    EXPECT_EQ(iocp56.length(true), 10);
}

TEST_F(MeasuredValueScaledSetTest, CommonImpValue)
{
    MeasuredValueScaled io{IOA{0x200}, 16667, Quality::BLOCKED};

    EXPECT_EQ(io.getValue(), 16667);
    io.setValue(-1);
    EXPECT_EQ(io.getValue(), -1);
}

TEST_F(MeasuredValueScaledSetTest, CommonImpQuality)
{
    MeasuredValueScaled io;
    io.setQuality(Quality::BLOCKED);
    EXPECT_TRUE(io.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io.getQuality() & Quality::NON_TOPICAL);

    io.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL);
    EXPECT_TRUE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(io.getQuality() & Quality::NON_TOPICAL);
}

TEST_F(MeasuredValueScaledSetTest, MeasuredValueScaledSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const MeasuredValueScaled::SerializePtr ios =
        std::make_shared<MeasuredValueScaled>(IOA{0x200}, 16667, Quality::BLOCKED);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x1b, 0x41, 0x10};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(MeasuredValueScaledSetTest, MeasuredValueScaledDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x1b, 0x41, 0x10};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<MeasuredValueScaled>();
    const MeasuredValueScaled::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getValue(), 16667);
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);
}

TEST_F(MeasuredValueScaledSetTest, MeasuredValueScaledWithCP24Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const MeasuredValueScaledWithCP24Time2a::SerializePtr ios =
        std::make_shared<MeasuredValueScaledWithCP24Time2a>(IOA{0x200}, 167, Quality::BLOCKED, CP24Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0xa7, 0x00, 0x10, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(MeasuredValueScaledSetTest, MeasuredValueScaledWithCP24Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0xa7, 0x00, 0x10, 0xdc, 0xe6, 0xfb};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<MeasuredValueScaledWithCP24Time2a>();
    const MeasuredValueScaledWithCP24Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getValue(), 167);
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);

    auto cp24Time2a = io->getTimestamp();
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    EXPECT_TRUE(cp24Time2a.isInvalid());
    EXPECT_TRUE(cp24Time2a.isSubstituted());
}

TEST_F(MeasuredValueScaledSetTest, MeasuredValueScaledWithCP56Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const MeasuredValueScaledWithCP56Time2a::SerializePtr ios =
        std::make_shared<MeasuredValueScaledWithCP56Time2a>(IOA{0x200}, 167, Quality::BLOCKED, CP56Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0xa7, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(MeasuredValueScaledSetTest, MeasuredValueScaledWithCP56Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0xa7, 0x00, 0x10, 0xfa, 0xd3, 0xd1, 0x8e, 0xf5, 0x0c, 0x19};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<MeasuredValueScaledWithCP56Time2a>();
    const MeasuredValueScaledWithCP56Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getValue(), 167);
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);

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
