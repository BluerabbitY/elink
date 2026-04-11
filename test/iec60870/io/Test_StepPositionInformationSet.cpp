/***********************************************************************************
 * \file Test_StepPositionInformationSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 22:52:37
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
#include "elink/iec60870/io/StepPositionInformation.hpp"
#include "elink/iec60870/io/StepPositionWithCP24Time2a.hpp"
#include "elink/iec60870/io/StepPositionWithCP56Time2a.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class StepPositionInformationSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(StepPositionInformationSetTest, TypeID)
{
    const StepPositionInformation io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_ST_NA_1);

    const StepPositionWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.getTypeID(), TypeID::M_ST_TA_1);

    const StepPositionWithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.getTypeID(), TypeID::M_ST_TB_1);
}

TEST_F(StepPositionInformationSetTest, IOLength)
{
    const StepPositionInformation io;
    EXPECT_EQ(io.size(), 5);
    EXPECT_EQ(io.length(true), 2);

    const StepPositionWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.size(), 8);
    EXPECT_EQ(iocp24.length(true), 5);

    const StepPositionWithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.size(), 12);
    EXPECT_EQ(iocp56.length(true), 9);
}

TEST_F(StepPositionInformationSetTest, CommonImpValue)
{
    StepPositionInformation io{IOA{0x200}, 60, true, Quality::BLOCKED};
    EXPECT_EQ(io.getValue(), 60);
    io.setValue(65);
    EXPECT_EQ(io.getValue(), 63);
}

TEST_F(StepPositionInformationSetTest, CommonImpQuality)
{
    StepPositionInformation io{IOA{0x200}, 60, true, Quality::BLOCKED};
    EXPECT_TRUE(io.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io.getQuality() & Quality::NON_TOPICAL);

    io.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL);
    EXPECT_TRUE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(io.getQuality() & Quality::NON_TOPICAL);
}

TEST_F(StepPositionInformationSetTest, StepPositionInformationSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const StepPositionInformation::SerializePtr ptr =
        std::make_shared<StepPositionInformation>(IOA{0x200}, 60, true, Quality::BLOCKED);
    EXPECT_TRUE(ptr->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0xbc, 0x10};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(StepPositionInformationSetTest, StepPositionInformationDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x4c, 0x11};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<StepPositionInformation>();
    const StepPositionInformation::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x300);
    EXPECT_EQ(io->getValue(), -52);
    EXPECT_FALSE(io->isTransient());
    EXPECT_TRUE(io->getQuality() & Quality::SPILL);
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);
}

TEST_F(StepPositionInformationSetTest, StepPositionWithCP24Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const StepPositionWithCP24Time2a::SerializePtr ios =
        std::make_shared<StepPositionWithCP24Time2a>(IOA{0x200}, 60, true, Quality::BLOCKED, CP24Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0xbc, 0x10, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(StepPositionInformationSetTest, StepPositionWithCP24Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x4c, 0x11, 0xdc, 0xe6, 0xfb};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<StepPositionWithCP24Time2a>();
    const StepPositionWithCP24Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x300);
    EXPECT_EQ(io->getValue(), -52);
    EXPECT_FALSE(io->isTransient());
    EXPECT_TRUE(io->getQuality() & Quality::SPILL);
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

TEST_F(StepPositionInformationSetTest, StepPositionWithCP56Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const StepPositionWithCP56Time2a::SerializePtr ios =
        std::make_shared<StepPositionWithCP56Time2a>(IOA{0x200}, 60, true, Quality::BLOCKED, CP56Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0xbc, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(StepPositionInformationSetTest, StepPositionWithCP56Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x4c, 0x11,  0xfa, 0xd3, 0xd1, 0x8e, 0xf5, 0x0c, 0x19};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<StepPositionWithCP56Time2a>();
    const StepPositionWithCP56Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x300);
    EXPECT_EQ(io->getValue(), -52);
    EXPECT_FALSE(io->isTransient());
    EXPECT_TRUE(io->getQuality() & Quality::SPILL);
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
