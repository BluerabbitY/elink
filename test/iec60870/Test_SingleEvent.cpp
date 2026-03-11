/***********************************************************************************
 * \file Test_SingleEvent.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-11 23:11:52
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
#include "elink/iec60870/SingleEvent.hpp"

#include <gtest/gtest.h>

using namespace elink::iec60870;

class SingleEventTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(SingleEventTest, DefaultConstructor)
{
    const SingleEvent se;
    EXPECT_EQ(se.getEventState(), EventState::INDETERMINATE_0);
    EXPECT_EQ(se.getQDP(), QualityP::GOOD);
}

TEST_F(SingleEventTest, ParameterConstructor)
{
    const SingleEvent se{EventState::ON, QualityP::BLOCKED | QualityP::ELAPSED_TIME_INVALID};
    EXPECT_EQ(se.getEventState(), EventState::ON);
    EXPECT_TRUE(se.getQDP() & QualityP::BLOCKED);
    EXPECT_TRUE(se.getQDP() & QualityP::ELAPSED_TIME_INVALID);
    EXPECT_FALSE(se.getQDP() & QualityP::SUBSTITUTED);
}

TEST_F(SingleEventTest, SetEventStatePreservesQDP)
{
    SingleEvent se{EventState::INDETERMINATE_3, QualityP::INVALID};

    se.setEventState(EventState::OFF);
    EXPECT_EQ(se.getEventState(), EventState::OFF);
    EXPECT_TRUE(se.getQDP() & QualityP::INVALID);
}

TEST_F(SingleEventTest, SetQDPPreservesEventState)
{
    SingleEvent se{EventState::OFF, QualityP::GOOD};
    se.setQDP(QualityP::BLOCKED | QualityP::ELAPSED_TIME_INVALID);
    EXPECT_EQ(se.getEventState(), EventState::OFF);
    EXPECT_TRUE(se.getQDP() & QualityP::BLOCKED);
    EXPECT_TRUE(se.getQDP() & QualityP::ELAPSED_TIME_INVALID);
}

TEST_F(SingleEventTest, EqualityAndCopy)
{
    const SingleEvent se1{EventState::ON, QualityP::BLOCKED};
    const SingleEvent se2{EventState::ON, QualityP::BLOCKED};
    const SingleEvent se3{EventState::OFF, QualityP::BLOCKED};

    EXPECT_TRUE(se1 == se2);
    EXPECT_FALSE(se1 != se2);
    EXPECT_FALSE(se1 == se3);
    EXPECT_TRUE(se1 != se3);

    const SingleEvent copy = se1;
    EXPECT_TRUE(copy == se1);
}
