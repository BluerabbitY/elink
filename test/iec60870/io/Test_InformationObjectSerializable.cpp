/***********************************************************************************
 * \file Test_InformationObjectSerializable.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 19:59:20
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
#include "Mock/MockInformationObjectSerializable.hpp"
#include "elink/iec60870/io/InformationObjectUtil.hpp"

#include <gtest/gtest.h>

using namespace elink::iec60870;

class InformationObjectSerializableTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(InformationObjectSerializableTest, TypeID)
{
    const mock::MockInformationObjectSerializable io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_SP_NA_1);
    EXPECT_EQ(mock::MockInformationObjectSerializable::IDENT_T, TypeID::M_SP_NA_1);
}

TEST_F(InformationObjectSerializableTest, IOA)
{
    constexpr int validIOA = 0x200;
    mock::MockInformationObjectSerializable io{IOA{validIOA}};
    EXPECT_EQ(io.getAddress(), validIOA);

    constexpr int newAddress = 0x300;
    io.setAddress(IOA{newAddress});
    EXPECT_EQ(io.getAddress(), newAddress);
}

TEST_F(InformationObjectSerializableTest, IOCast)
{
    mock::MockInformationObjectSerializable mockio;
    InformationObject& io = mockio;
    auto& castedSio = io_cast<mock::MockInformationObjectSerializable>(io);
    EXPECT_EQ(&castedSio, &mockio);
}
