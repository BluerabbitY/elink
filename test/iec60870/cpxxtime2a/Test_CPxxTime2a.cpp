/***********************************************************************************
 * \file Test_CPXXTime2a.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test for CPxxTime2a
 * \date 2025-12-20 13:05:00
 * 
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#include "elink/iec60870/cpxxtime2a/CPxxTime2a.hpp"

#include <gtest/gtest.h>

class CPXXTime2aTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    elink::iec60870::CP16Time2a cp16Time2a{};
    elink::iec60870::CP24Time2a cp24Time2a{};
    elink::iec60870::CP32Time2a cp32Time2a{};
    elink::iec60870::CP56Time2a cp56Time2a{};
};

TEST_F(CPXXTime2aTest, CP16Time2a)
{
    cp16Time2a.setEplapsedTimeInMs(100);
    EXPECT_EQ(cp16Time2a.getEplapsedTimeInMs(), 100);
    cp16Time2a.setEplapsedTimeInMs(65535);
    EXPECT_EQ(cp16Time2a.getEplapsedTimeInMs(), 59999);
}

TEST_F(CPXXTime2aTest, CP24Time2a)
{
    cp24Time2a.setMillisecond(100);
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    cp24Time2a.setMillisecond(1000);
    EXPECT_EQ(cp24Time2a.getMillisecond(), 999);

    cp24Time2a.setSecond(59);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    cp24Time2a.setSecond(61);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);

    cp24Time2a.setMinute(59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    cp24Time2a.setMinute(61);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);

    EXPECT_FALSE(cp24Time2a.isInvalid());
    cp24Time2a.setInvalid(true);
    EXPECT_TRUE(cp24Time2a.isInvalid());

    EXPECT_FALSE(cp24Time2a.isSubstituted());
    cp24Time2a.setSubstituted(true);
    EXPECT_TRUE(cp24Time2a.isSubstituted());
}

TEST_F(CPXXTime2aTest, CP32Time2a)
{
    cp32Time2a.setHour(22);
    EXPECT_EQ(cp32Time2a.getHour(), 22);
    cp32Time2a.setHour(27);
    EXPECT_EQ(cp32Time2a.getHour(), 23);

    EXPECT_FALSE(cp32Time2a.isSummerTime());
    cp32Time2a.setSummerTime(true);
    EXPECT_TRUE(cp32Time2a.isSummerTime());
}

TEST_F(CPXXTime2aTest, CP56Time2a)
{
    cp56Time2a.setDayOfWeek(3);
    EXPECT_EQ(cp56Time2a.getDayOfWeek(), 3);
    cp56Time2a.setDayOfWeek(8);
    EXPECT_EQ(cp56Time2a.getDayOfWeek(), 7);

    cp56Time2a.setDayOfMonth(27);
    EXPECT_EQ(cp56Time2a.getDayOfMonth(), 27);
    cp56Time2a.setDayOfMonth(32);
    EXPECT_EQ(cp56Time2a.getDayOfMonth(), 31);

    cp56Time2a.setYear(2025);
    EXPECT_EQ(cp56Time2a.getYear(), 2025);

    cp56Time2a.setMillisecond(266);
    cp56Time2a.setSecond(54);
    cp56Time2a.setMinute(17);
    cp56Time2a.setHour(14);
    cp56Time2a.setDayOfMonth(21);
    cp56Time2a.setMonth(12);
    cp56Time2a.setYear(2025);

    EXPECT_EQ(cp56Time2a.toMsTimestamp(), 1766297874266);
}
