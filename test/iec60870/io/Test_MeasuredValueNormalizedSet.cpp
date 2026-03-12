/***********************************************************************************
 * \file Test_MeasuredValueNormalizedSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-01 14:45:45
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
#include "elink/iec60870/io/MeasuredValueNormalized.hpp"
#include "elink/iec60870/io/MeasuredValueNormalizedWithCP24Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueNormalizedWithoutQuality.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class BMeasuredValueNormalizedSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(BMeasuredValueNormalizedSetTest, TypeID)
{
    const MeasuredValueNormalized io;
    EXPECT_EQ(io.getTypeID(), elink::iec60870::TypeID::M_ME_NA_1);

    const MeasuredValueNormalizedWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.getTypeID(), elink::iec60870::TypeID::M_ME_TA_1);

    const MeasuredValueNormalizedWithoutQuality ionq;
    EXPECT_EQ(ionq.getTypeID(), elink::iec60870::TypeID::M_ME_ND_1);
}

TEST_F(BMeasuredValueNormalizedSetTest, IOLength)
{
    const MeasuredValueNormalized io;
    EXPECT_EQ(io.size(), 6);
    EXPECT_EQ(io.length(true), 3);

    const MeasuredValueNormalizedWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.size(), 9);
    EXPECT_EQ(iocp24.length(true), 6);

    const MeasuredValueNormalizedWithoutQuality ionq;
    EXPECT_EQ(ionq.size(), 5);
    EXPECT_EQ(ionq.length(true), 2);
}

TEST_F(BMeasuredValueNormalizedSetTest, CommonImpValue)
{
    const MeasuredValueNormalized io1{IOA{0x300}, 0.5f, Quality::BLOCKED};
    EXPECT_EQ(io1.getInformationObjectAddress(), 0x300);
    EXPECT_FLOAT_EQ(io1.getValue(), 0.5f);
    EXPECT_EQ(io1.getQuality(), Quality::BLOCKED);

    const MeasuredValueNormalized io2{IOA{0x300}, 98, 100, 50, Quality::NON_TOPICAL};
    EXPECT_EQ(io2.getInformationObjectAddress(), 0x300);
    EXPECT_TRUE(io2.getValue() - 0.48f < 0.002f);
    EXPECT_TRUE(io2.getValue(100, 50) - 98.f < 0.002f);
    EXPECT_EQ(io2.getQuality(), Quality::NON_TOPICAL);
}

TEST_F(BMeasuredValueNormalizedSetTest, CommonImpQuality)
{
    MeasuredValueNormalized io;
    io.setQuality(Quality::BLOCKED);
    EXPECT_TRUE(io.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io.getQuality() & Quality::NON_TOPICAL);

    io.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL | Quality::SPILL);
    EXPECT_TRUE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(io.getQuality() & Quality::NON_TOPICAL);
    EXPECT_TRUE(io.getQuality() & Quality::SPILL);
}

TEST_F(BMeasuredValueNormalizedSetTest, MeasuredValueNormalizedSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const MeasuredValueNormalized::SerializePtr ios =
        std::make_shared<MeasuredValueNormalized>(IOA{0x200}, 0.5f, Quality::BLOCKED);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x00, 0x40, 0x10};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(BMeasuredValueNormalizedSetTest, MeasuredValueNormalizedDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x00, 0x40, 0x10};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<MeasuredValueNormalized>();
    const MeasuredValueNormalized::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_FLOAT_EQ(io->getValue(), 0.5f);
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SPILL);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);
}

TEST_F(BMeasuredValueNormalizedSetTest, MeasuredValueNormalizedWithCP24Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const MeasuredValueNormalizedWithCP24Time2a::SerializePtr ios =
        std::make_shared<MeasuredValueNormalizedWithCP24Time2a>(IOA{0x200}, 0.5f, Quality::BLOCKED, CP24Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x00, 0x40, 0x10, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(BMeasuredValueNormalizedSetTest, MeasuredValueNormalizedWithCP24Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x00, 0x40, 0x10, 0xdc, 0xe6, 0xfb};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<MeasuredValueNormalizedWithCP24Time2a>();
    const MeasuredValueNormalizedWithCP24Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_FLOAT_EQ(io->getValue(), 0.5f);
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

TEST_F(BMeasuredValueNormalizedSetTest, MeasuredValueNormalizedWithoutQualitySerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const MeasuredValueNormalizedWithoutQuality::SerializePtr ios =
        std::make_shared<MeasuredValueNormalizedWithoutQuality>(IOA{0x200}, 0.5f);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x00, 0x40};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(BMeasuredValueNormalizedSetTest, MeasuredValueNormalizedWithoutQualityDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x00, 0x40};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<MeasuredValueNormalizedWithoutQuality>();
    const MeasuredValueNormalizedWithoutQuality::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_FLOAT_EQ(io->getValue(), 0.5f);
}
