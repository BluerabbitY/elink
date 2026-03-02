/***********************************************************************************
 * \file Test_BinaryCounterReading.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-02 22:06:05
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
#include "elink/iec60870/BinaryCounterReading.hpp"

#include <gtest/gtest.h>

using namespace elink::iec60870;

class BinaryCounterReadingTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(BinaryCounterReadingTest, Constructor)
{
    const BinaryCounterReading bcr{32768, 1, true, false, true};

    EXPECT_EQ(bcr.getValue(), 32768);
    EXPECT_EQ(bcr.getSequenceNumber(), 1);
    EXPECT_TRUE(bcr.hasCarry());
    EXPECT_FALSE(bcr.isAdjusted());
    EXPECT_TRUE(bcr.isInvalid());
}

TEST_F(BinaryCounterReadingTest, SetValue)
{
    BinaryCounterReading bcr{32768, 1, true, false, true};

    bcr.setValue(32778);
    EXPECT_EQ(bcr.getValue(), 32778);
    EXPECT_EQ(bcr.getSequenceNumber(), 1);
    EXPECT_TRUE(bcr.hasCarry());
    EXPECT_FALSE(bcr.isAdjusted());
    EXPECT_TRUE(bcr.isInvalid());
}
