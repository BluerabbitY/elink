/***********************************************************************************
 * \file Test_BitString32Set.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 23:15:46
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
#include "elink/iec60870/io/BitString32.hpp"
#include "elink/iec60870/io/BitString32WithCP24Time2a.hpp"
#include "elink/iec60870/io/BitString32WithCP56Time2a.hpp"
#include "elink/iec60870/io/BitString32Command.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class BitString32SetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(BitString32SetTest, TypeID)
{
    const BitString32 io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_BO_NA_1);

    const BitString32WithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.getTypeID(), TypeID::M_BO_TA_1);

    const BitString32WithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.getTypeID(), TypeID::M_BO_TB_1);

    const BitString32Command command;
    EXPECT_EQ(command.getTypeID(), TypeID::C_BO_NA_1);
}

TEST_F(BitString32SetTest, IOLength)
{
    const BitString32 io;
    EXPECT_EQ(io.size(), 8);
    EXPECT_EQ(io.length(true), 5);

    const BitString32WithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.size(), 11);
    EXPECT_EQ(iocp24.length(true), 8);

    const BitString32WithCP56Time2a iocp56;
    EXPECT_EQ(iocp56.size(), 15);
    EXPECT_EQ(iocp56.length(true), 12);

    const BitString32Command command;
    EXPECT_EQ(command.size(), 7);
    EXPECT_EQ(command.length(true), 4);
}

TEST_F(BitString32SetTest, CommonImpValue)
{
    constexpr BitString32Value value1{0x55555555};
    constexpr BitString32Value value2{0xaaaaaaaa};
    BitString32 io{IOA{0x200}, 0x55555555, Quality::BLOCKED};

    EXPECT_EQ(io.getValue(), value1);
    io.setValue(value2);
    EXPECT_EQ(io.getValue(), value2);
}

TEST_F(BitString32SetTest, CommonImpPosValue)
{
    BitString32 io{IOA{0x200}, 0x55555555, Quality::BLOCKED};

    EXPECT_TRUE(io.getValue(0));
    EXPECT_FALSE(io.getValue(1));
    io.setValue(1, true);
    EXPECT_TRUE(io.getValue(1));
}

TEST_F(BitString32SetTest, CommonImpQuality)
{
    BitString32 io;
    io.setQuality(Quality::BLOCKED);
    EXPECT_TRUE(io.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io.getQuality() & Quality::NON_TOPICAL);

    io.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL | Quality::SPILL);
    EXPECT_TRUE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(io.getQuality() & Quality::NON_TOPICAL);
    EXPECT_TRUE(io.getQuality() & Quality::SPILL);
}

TEST_F(BitString32SetTest, BitString32Serialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const BitString32::SerializePtr ios =
        std::make_shared<BitString32>(IOA{0x200}, 0x5d5c5b5a, Quality::BLOCKED);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x5a, 0x5b, 0x5c, 0x5d, 0x10};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(BitString32SetTest, BitString32Deserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x5a, 0x5b, 0x5c, 0x5d, 0x10};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<BitString32>();
    const BitString32::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getValue(), BitString32Value{0x5d5c5b5a});
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SPILL);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);
}

TEST_F(BitString32SetTest, BitString32WithCP24Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const BitString32WithCP24Time2a::SerializePtr ios =
        std::make_shared<BitString32WithCP24Time2a>(IOA{0x200}, 0x5d5c5b5a, Quality::BLOCKED, CP24Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x5a, 0x5b, 0x5c, 0x5d, 0x10, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(BitString32SetTest, BitString32WithCP24Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x5a, 0x5b, 0x5c, 0x5d, 0x10, 0xdc, 0xe6, 0xfb};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<BitString32WithCP24Time2a>();
    const BitString32WithCP24Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getValue(), BitString32Value{0x5d5c5b5a});
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

TEST_F(BitString32SetTest, BitString32WithCP56Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const BitString32WithCP56Time2a::SerializePtr ios =
        std::make_shared<BitString32WithCP56Time2a>(IOA{0x200}, 0x5d5c5b5a, Quality::BLOCKED, CP56Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x5a, 0x5b, 0x5c, 0x5d, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(BitString32SetTest, BitString32WithCP56Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x5a, 0x5b, 0x5c, 0x5d, 0x10, 0xfa, 0xd3, 0xd1, 0x8e, 0xf5, 0x0c, 0x19};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<BitString32WithCP56Time2a>();
    const BitString32WithCP56Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getValue(), BitString32Value{0x5d5c5b5a});
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

TEST_F(BitString32SetTest, BitString32CommandSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const BitString32Command::SerializePtr ios =
        std::make_shared<BitString32Command>(IOA{0x200}, 0x5d5c5b5a);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x5a, 0x5b, 0x5c, 0x5d};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(BitString32SetTest, BitString32CommandDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x5a, 0x5b, 0x5c, 0x5d};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<BitString32Command>();
    const BitString32Command::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getValue(), BitString32Value{0x5d5c5b5a});
}
