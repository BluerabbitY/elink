/***********************************************************************************
 * \file Test_StepPositionWithCP24Time2a.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2026-01-03 11:34:05
 *
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 ***********************************************************************************/
#include "elink/elink.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class StepPositionWithCP24Time2aTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    const int validIOA = 0x200;
    StepPositionWithCP24Time2a sio{IOA{validIOA}, 60, true, Quality::BLOCKED, CP24Time2a{}};
};

TEST_F(StepPositionWithCP24Time2aTest, TypeID)
{
    EXPECT_EQ(sio.getTypeID(), TypeID::M_ST_TA_1);
}

TEST_F(StepPositionWithCP24Time2aTest, IOA)
{
    EXPECT_EQ(sio.getInformationObjectAddress().address(), validIOA);

    constexpr int newAddress = 0x300;
    sio.setInformationObjectAddress(IOA{newAddress});
    EXPECT_EQ(sio.getInformationObjectAddress().address(), newAddress);
}

TEST_F(StepPositionWithCP24Time2aTest, Value)
{
    EXPECT_EQ(sio.getValue(), 60);
    sio.setValue(65);
    EXPECT_EQ(sio.getValue(), 63);
}

TEST_F(StepPositionWithCP24Time2aTest, Quality)
{
    EXPECT_TRUE(sio.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(sio.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(sio.getQuality() & Quality::NON_TOPICAL);

    sio.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL);
    EXPECT_TRUE(sio.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(sio.getQuality() & Quality::NON_TOPICAL);
}

TEST_F(StepPositionWithCP24Time2aTest, Serialize)
{
    const StepPositionWithCP24Time2a::OriginPtr ptr = std::make_shared<StepPositionWithCP24Time2a>(sio);
    uint8_t buffer[256]{};
    internal::OStream os{buffer, sizeof(buffer)};
    EXPECT_TRUE(ptr->serialize(os, false));
    EXPECT_FALSE(os.hasError());
    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0xbc, 0x10, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(StepPositionWithCP24Time2aTest, Deserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x4c, 0x11, 0x00, 0x00, 0x00};
    internal::IStream is{buffer, sizeof(buffer)};

    const auto pSio = std::make_shared<StepPositionWithCP24Time2a>(sio);
    const StepPositionWithCP24Time2a::OriginPtr iop = pSio;
    EXPECT_TRUE(iop->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.readBytes(), sizeof(buffer));

    EXPECT_EQ(iop->getInformationObjectAddress().address(), 0x300);
    EXPECT_EQ(pSio->getValue(), -52);
    EXPECT_FALSE(pSio->isTransient());
    EXPECT_TRUE(pSio->getQuality() & Quality::OVERFLOW);
    EXPECT_TRUE(pSio->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(pSio->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(pSio->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(pSio->getQuality() & Quality::INVALID);
}

TEST_F(StepPositionWithCP24Time2aTest, Timestamp)
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

TEST_F(StepPositionWithCP24Time2aTest, IOLength)
{
    EXPECT_EQ(sio.size(), 8);
}
