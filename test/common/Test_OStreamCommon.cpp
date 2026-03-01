/***********************************************************************************
 * \file Test_OStreamCommon.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-02 23:56:58
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
#include <gtest/gtest.h>

#include <cstring>

#include "mock/MockOStream.hpp"
#include "elink/iec60870/io/InformationObjectTypeID.h"

using namespace elink::details;

class OStreamCommonTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    uint8_t buffer[256]{};
    mock::OStream stream{buffer, sizeof(buffer)};
};

TEST_F(OStreamCommonTest, WriteArithmetic)
{
    std::size_t length = 0;
    stream << uint8_t{0x12};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.size(), sizeof(uint8_t));

    length = stream.size();
    stream << uint16_t{0x1234};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.size(), length + sizeof(uint16_t));

    length = stream.size();
    stream << uint32_t{0x12345678};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.size(), length + sizeof(uint32_t));

    constexpr uint8_t dest[] = {0x12, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12};
    EXPECT_EQ(stream.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamCommonTest, WriteFloat)
{
    constexpr float fixpoint = 11.1;
    stream << fixpoint;
    EXPECT_FALSE(stream.hasError());

    constexpr uint8_t dest[] = {0x9A, 0x99, 0x31, 0x41};
    EXPECT_EQ(stream.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamCommonTest, WriteEnumAndEnumClass)
{
    std::size_t length = 0;
    stream << elink::iec60870::TypeID::C_BO_NA_1;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.size(), sizeof(std::underlying_type_t<elink::iec60870::TypeID>));

    length = stream.size();
    stream << elink::iec60870::TypeID::C_SC_TA_1;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.size(), length + sizeof(std::underlying_type_t<elink::iec60870::TypeID>));

    constexpr uint8_t dest[] = {0x33, 0x3A};
    EXPECT_EQ(stream.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamCommonTest, WriteSpan)
{
    uint8_t dest[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    stream << elink::LiteBufferView{dest, sizeof(dest)};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamCommonTest, WriteOverflow)
{
    uint8_t buffer[512]{};
    stream << elink::LiteBufferView{buffer, sizeof(buffer)};
    EXPECT_TRUE(stream.hasError());
    stream.acknowledgeError();
    EXPECT_FALSE(stream.hasError());
}
