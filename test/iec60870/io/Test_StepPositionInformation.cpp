/***********************************************************************************
 * \file Test_StepPositionInformation.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test for iec60870 information object StepPositionInformation
 * \date 2026-01-02 21:06:18
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

class StepPositionInformationTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    const int validIOA = 0x200;
    StepPositionInformation sio{IOA{validIOA}, 60, true, Quality::BLOCKED};
};

TEST_F(StepPositionInformationTest, TypeID)
{
    EXPECT_EQ(sio.getTypeID(), TypeID::M_ST_NA_1);
}

TEST_F(StepPositionInformationTest, IOA)
{
    EXPECT_EQ(sio.getInformationObjectAddress().address(), validIOA);

    constexpr int newAddress = 0x300;
    sio.setInformationObjectAddress(IOA{newAddress});
    EXPECT_EQ(sio.getInformationObjectAddress().address(), newAddress);
}

TEST_F(StepPositionInformationTest, Value)
{
    EXPECT_EQ(sio.getValue(), 60);
    sio.setValue(65);
    EXPECT_EQ(sio.getValue(), 63);
}

TEST_F(StepPositionInformationTest, Quality)
{
    EXPECT_TRUE(sio.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(sio.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(sio.getQuality() & Quality::NON_TOPICAL);

    sio.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL);
    EXPECT_TRUE(sio.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(sio.getQuality() & Quality::NON_TOPICAL);
}

TEST_F(StepPositionInformationTest, Serialize)
{
    const StepPositionInformation::OriginPtr ptr = std::make_shared<StepPositionInformation>(sio);
    uint8_t buffer[256]{};
    internal::OStream os{buffer, sizeof(buffer)};
    EXPECT_TRUE(ptr->serialize(os, false));
    EXPECT_FALSE(os.hasError());
    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0xbc, 0x10};
    EXPECT_EQ(os.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(StepPositionInformationTest, Deserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x4c, 0x11};
    internal::IStream is{buffer, sizeof(buffer)};

    const auto pSio = std::make_shared<StepPositionInformation>(sio);
    const StepPositionInformation::OriginPtr iop = pSio;
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

TEST_F(StepPositionInformationTest, IOLength)
{
    EXPECT_EQ(sio.size(), 5);
}
