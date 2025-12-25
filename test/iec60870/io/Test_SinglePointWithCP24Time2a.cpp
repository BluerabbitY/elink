/***********************************************************************************
 * \file Test_SinglePointWithCP24Time2a.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test for SinglePointWithCP24Time2a
 * \date 2025-12-22 23:31:58
 * 
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#include "elink/elink.h"

#include <gtest/gtest.h>

using namespace elink::iec60870;

class SinglePointWithCP24Time2aTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    const int validIOA = 0x200;
    SinglePointWithCP24Time2a sio{IOA{validIOA}, true, SQuality::BLOCKED, CP24Time2a{}};
};

TEST_F(SinglePointWithCP24Time2aTest, TypeID)
{
    EXPECT_EQ(sio.getTypeID(), TypeID::M_SP_TA_1);
}

TEST_F(SinglePointWithCP24Time2aTest, IOA)
{
    EXPECT_EQ(sio.getInformationObjectAddress().address(), validIOA);

    constexpr int newAddress = 0x300;
    sio.setInformationObjectAddress(IOA{newAddress});
    EXPECT_EQ(sio.getInformationObjectAddress().address(), newAddress);
}

TEST_F(SinglePointWithCP24Time2aTest, Value)
{
    EXPECT_TRUE(sio.getValue());
    sio.setValue(false);
    EXPECT_FALSE(sio.getValue());
}

TEST_F(SinglePointWithCP24Time2aTest, Quality)
{
    EXPECT_TRUE(sio.getQuality() & SQuality::BLOCKED);
    EXPECT_FALSE(sio.getQuality() & SQuality::SUBSTITUTED);
    EXPECT_FALSE(sio.getQuality() & SQuality::NON_TOPICAL);

    sio.setQuality(SQuality::SUBSTITUTED | SQuality::NON_TOPICAL);
    EXPECT_TRUE(sio.getQuality() & SQuality::SUBSTITUTED);
    EXPECT_TRUE(sio.getQuality() & SQuality::NON_TOPICAL);
}

TEST_F(SinglePointWithCP24Time2aTest, Serialize)
{
    const SinglePointWithCP24Time2a::OriginPtr ptr = std::make_shared<SinglePointWithCP24Time2a>(sio);
    uint8_t buffer[256]{};
    internal::OStream os{buffer, sizeof(buffer)};
    EXPECT_TRUE(ptr->serialize(os, false));
    EXPECT_FALSE(os.hasError());
    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x11, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(SinglePointWithCP24Time2aTest, Deserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x10, 0xdc, 0xe6, 0xfb};
    internal::IStream is{buffer, sizeof(buffer)};

    const auto pSio = std::make_shared<SinglePointWithCP24Time2a>(sio);
    const SinglePointWithCP24Time2a::OriginPtr iop = pSio;
    EXPECT_TRUE(iop->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.readBytes(), sizeof(buffer));

    EXPECT_EQ(iop->getInformationObjectAddress().address(), 0x300);
    EXPECT_FALSE(pSio->getValue());
    EXPECT_TRUE(pSio->getQuality() & SQuality::BLOCKED);
    EXPECT_FALSE(pSio->getQuality() & SQuality::SUBSTITUTED);
    EXPECT_FALSE(pSio->getQuality() & SQuality::NON_TOPICAL);
    EXPECT_FALSE(pSio->getQuality() & SQuality::INVALID);

    auto cp24Time2a = pSio->getTimestamp();
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    EXPECT_TRUE(cp24Time2a.isInvalid());
    EXPECT_TRUE(cp24Time2a.isSubstituted());
}

TEST_F(SinglePointWithCP24Time2aTest, Timestamp)
{
    auto cp24Time2a = sio.getTimestamp();
    EXPECT_EQ(cp24Time2a.getMillisecond(), 0);
    EXPECT_EQ(cp24Time2a.getSecond(), 0);
    EXPECT_EQ(cp24Time2a.getMinute(), 0);
    EXPECT_FALSE(cp24Time2a.isInvalid());
    EXPECT_FALSE(cp24Time2a.isSubstituted());

    cp24Time2a.setInvalid(true);
    sio.setTimestamp(cp24Time2a);
    EXPECT_EQ(sio.getTimestamp().isInvalid(), true);
}

TEST_F(SinglePointWithCP24Time2aTest, IOLength)
{
    EXPECT_EQ(sio.size(), 7);
}
