/***********************************************************************************
 * \file Test_InformationObjectWithCPxxTime2a.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 20:55:37
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
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
