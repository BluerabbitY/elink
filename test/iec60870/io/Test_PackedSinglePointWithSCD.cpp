/***********************************************************************************
 * \file Test_PackedSinglePointWithSCD.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-10 23:30:55
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
#include "elink/iec60870/io/PackedSinglePointWithSCD.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class PackedSinglePointWithSCDSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(PackedSinglePointWithSCDSetTest, TypeID)
{
    const PackedSinglePointWithSCD io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_PS_NA_1);
}

TEST_F(PackedSinglePointWithSCDSetTest, IOLength)
{
    const PackedSinglePointWithSCD io;
    EXPECT_EQ(io.size(), 8);
    EXPECT_EQ(io.length(true), 5);
}

TEST_F(PackedSinglePointWithSCDSetTest, CommonImpValue)
{
    const StatusAndStatusChangeDetection scd{0x1234, 0x4321};
    const StatusAndStatusChangeDetection scdNew{0x1235, 0x5421};
    PackedSinglePointWithSCD io{IOA{0x200}, scd, Quality::BLOCKED};

    EXPECT_EQ(io.getSCD(), scd);
    io.setSCD(scdNew);
    EXPECT_EQ(io.getSCD(), scdNew);
}

TEST_F(PackedSinglePointWithSCDSetTest, CommonImpQuality)
{
    PackedSinglePointWithSCD io;
    io.setQuality(Quality::BLOCKED);
    EXPECT_TRUE(io.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io.getQuality() & Quality::NON_TOPICAL);

    io.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL);
    EXPECT_TRUE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(io.getQuality() & Quality::NON_TOPICAL);
}

TEST_F(PackedSinglePointWithSCDSetTest, PackedSinglePointWithSCDSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};
    const StatusAndStatusChangeDetection scd{0x1234, 0x4321};

    const PackedSinglePointWithSCD::SerializePtr ios =
        std::make_shared<PackedSinglePointWithSCD>(IOA{0x200}, scd, Quality::BLOCKED);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x34, 0x12, 0x21, 0x43, 0x10};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(PackedSinglePointWithSCDSetTest, DoublePointInformationDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x34, 0x12, 0x21, 0x43, 0x10};
    const StatusAndStatusChangeDetection scd{0x1234, 0x4321};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<PackedSinglePointWithSCD>();
    const PackedSinglePointWithSCD::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getAddress(), 0x300);
    EXPECT_EQ(io->getSCD(), scd);
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);
}
