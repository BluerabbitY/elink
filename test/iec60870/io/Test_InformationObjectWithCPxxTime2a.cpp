/***********************************************************************************
 * \file Test_InformationObjectWithCPxxTime2a.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 20:55:37
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
#include "Mock/MockInformationObjectWithCPxxTime2a.hpp"

#include <gtest/gtest.h>

class InformationObjectWithCPxxTime2aTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(InformationObjectWithCPxxTime2aTest, Construct)
{
    mock::MockInformationObjectWithCPxxTime2a<elink::iec60870::CP56Time2a> mockCP56Time2a;
    mockCP56Time2a.setTimestamp(elink::iec60870::CP56Time2a{});
    EXPECT_EQ(mockCP56Time2a.getTimestamp(), elink::iec60870::CP56Time2a{});

    mock::MockInformationObjectWithCPxxTime2a<elink::iec60870::CP32Time2a> mockCP32Time2a;
    mockCP32Time2a.setTimestamp(elink::iec60870::CP32Time2a{});
    EXPECT_EQ(mockCP32Time2a.getTimestamp(), elink::iec60870::CP32Time2a{});

    mock::MockInformationObjectWithCPxxTime2a<elink::iec60870::CP24Time2a> mockCP24Time2a;
    mockCP24Time2a.setTimestamp(elink::iec60870::CP24Time2a{});
    EXPECT_EQ(mockCP24Time2a.getTimestamp(), elink::iec60870::CP24Time2a{});

    mock::MockInformationObjectWithCPxxTime2a<elink::iec60870::CP16Time2a> mockCP16Time2a;
    mockCP16Time2a.setTimestamp(elink::iec60870::CP16Time2a{});
    EXPECT_EQ(mockCP16Time2a.getTimestamp(), elink::iec60870::CP16Time2a{});
}

TEST_F(InformationObjectWithCPxxTime2aTest, Timestamp)
{
    mock::MockInformationObjectWithCPxxTime2a io{elink::iec60870::CP24Time2a{}};

    auto cp24Time2a = io.getTimestamp();
    EXPECT_EQ(cp24Time2a.getMillisecond(), 0);
    EXPECT_EQ(cp24Time2a.getSecond(), 0);
    EXPECT_EQ(cp24Time2a.getMinute(), 0);
    EXPECT_FALSE(cp24Time2a.isInvalid());
    EXPECT_FALSE(cp24Time2a.isSubstituted());

    cp24Time2a.setInvalid(true);
    io.setTimestamp(cp24Time2a);
    EXPECT_TRUE(io.getTimestamp().isInvalid());
}
