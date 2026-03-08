/***********************************************************************************
 * \file Test_PackedOutputCircuitInfoSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-07 20:32:37
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
#include "elink/iec60870/io/PackedOutputCircuitInfo.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class PackedOutputCircuitInfoSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(PackedOutputCircuitInfoSetTest, TypeID)
{
    const PackedOutputCircuitInfo io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_EP_TC_1);
}

TEST_F(PackedOutputCircuitInfoSetTest, IOLength)
{
    const PackedOutputCircuitInfo io;
    EXPECT_EQ(io.size(), 10);
    EXPECT_EQ(io.length(true), 7);
}

TEST_F(PackedOutputCircuitInfoSetTest, CommonImpValue)
{
    PackedOutputCircuitInfo io{IOA{0x200}, OutputCircuitInfo::OUTPUT_CI_CL3, QualityP::BLOCKED, CP16Time2a{123}, CP24Time2a{}};

    EXPECT_EQ(io.getOCI(), OutputCircuitInfo::OUTPUT_CI_CL3);
    io.setOCI(OutputCircuitInfo::OUTPUT_CI_CL2);
    EXPECT_EQ(io.getOCI(), OutputCircuitInfo::OUTPUT_CI_CL2);

    EXPECT_EQ(io.getQuality(), QualityP::BLOCKED);
    io.setQuality(QualityP::ELAPSED_TIME_INVALID);
    EXPECT_EQ(io.getQuality(), QualityP::ELAPSED_TIME_INVALID);

    EXPECT_EQ(io.getOperatingTime().getEplapsedTimeInMs(), 123);
    io.setOperatingTime(CP16Time2a{1278});
    EXPECT_EQ(io.getOperatingTime().getEplapsedTimeInMs(), 1278);
}

TEST_F(PackedOutputCircuitInfoSetTest, CommonImpQuality)
{
    PackedOutputCircuitInfo io;
    io.setQuality(QualityP::BLOCKED);
    EXPECT_FALSE(io.getQuality() & QualityP::ELAPSED_TIME_INVALID);
    EXPECT_TRUE(io.getQuality() & QualityP::BLOCKED);
    EXPECT_FALSE(io.getQuality() & QualityP::SUBSTITUTED);
    EXPECT_FALSE(io.getQuality() & QualityP::NON_TOPICAL);
    EXPECT_FALSE(io.getQuality() & QualityP::INVALID);

    io.setQuality(QualityP::SUBSTITUTED | QualityP::NON_TOPICAL);
    EXPECT_TRUE(io.getQuality() & QualityP::SUBSTITUTED);
    EXPECT_TRUE(io.getQuality() & QualityP::NON_TOPICAL);
}

TEST_F(PackedOutputCircuitInfoSetTest, PackedOutputCircuitInfoSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const PackedOutputCircuitInfo::SerializePtr ios =
        std::make_shared<PackedOutputCircuitInfo>(IOA{0x200}, OutputCircuitInfo::OUTPUT_CI_CL3, QualityP::BLOCKED, CP16Time2a{123}, CP24Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x08, 0x10, 0x7b, 0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(PackedOutputCircuitInfoSetTest, PackedOutputCircuitInfoDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x08, 0x10, 0xfe, 0x04, 0xdc, 0xe6, 0xfb};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<PackedOutputCircuitInfo>();
    const PackedOutputCircuitInfo::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getOCI(), OutputCircuitInfo::OUTPUT_CI_CL3);
    EXPECT_EQ(io->getOperatingTime().getEplapsedTimeInMs(), 1278);
    EXPECT_FALSE(io->getQuality() & QualityP::ELAPSED_TIME_INVALID);
    EXPECT_TRUE(io->getQuality() & QualityP::BLOCKED);
    EXPECT_FALSE(io->getQuality() & QualityP::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & QualityP::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & QualityP::INVALID);

    auto cp24Time2a = io->getTimestamp();
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    EXPECT_TRUE(cp24Time2a.isInvalid());
    EXPECT_TRUE(cp24Time2a.isSubstituted());
}
