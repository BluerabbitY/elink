/***********************************************************************************
 * \file Test_DoublePointInformation.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2025-12-25 22:51:23
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
#include <cstring>

using namespace elink::iec60870;

class DoublePointInformationTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    const int validIOA = 0x200;
    DoublePointInformation dio{IOA{validIOA}, DValue::ON, Quality::BLOCKED};
};

TEST_F(DoublePointInformationTest, TypeID)
{
    EXPECT_EQ(dio.getTypeID(), TypeID::M_DP_NA_1);
}

TEST_F(DoublePointInformationTest, IOA)
{
    EXPECT_EQ(dio.getInformationObjectAddress().address(), validIOA);

    constexpr int newAddress = 0x300;
    dio.setInformationObjectAddress(IOA{newAddress});
    EXPECT_EQ(dio.getInformationObjectAddress().address(), newAddress);
}

TEST_F(DoublePointInformationTest, Value)
{
    EXPECT_TRUE(dio.getValue());
    dio.setValue(DValue::OFF);
    EXPECT_EQ(dio.getValue(), DValue::OFF);
}

TEST_F(DoublePointInformationTest, Quality)
{
    EXPECT_TRUE(dio.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(dio.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(dio.getQuality() & Quality::NON_TOPICAL);

    dio.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL);
    EXPECT_TRUE(dio.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(dio.getQuality() & Quality::NON_TOPICAL);
}

TEST_F(DoublePointInformationTest, Serialize)
{
    const DoublePointInformation::OriginPtr ptr = std::make_shared<DoublePointInformation>(dio);
    uint8_t buffer[256]{};
    internal::OStream os{buffer, sizeof(buffer)};
    EXPECT_TRUE(ptr->serialize(os, false));
    EXPECT_FALSE(os.hasError());
    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x12};
    EXPECT_EQ(os.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(DoublePointInformationTest, Deserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x13};
    internal::IStream is{buffer, sizeof(buffer)};

    const auto pDio = std::make_shared<DoublePointInformation>(dio);
    const DoublePointInformation::OriginPtr iop = pDio;
    EXPECT_TRUE(iop->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.readBytes(), sizeof(buffer));

    EXPECT_EQ(iop->getInformationObjectAddress().address(), 0x300);
    EXPECT_EQ(pDio->getValue(), DValue::INDETERMINATE);
    EXPECT_TRUE(pDio->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(pDio->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(pDio->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(pDio->getQuality() & Quality::INVALID);
}

TEST_F(DoublePointInformationTest, IOLength)
{
    EXPECT_EQ(dio.size(), 4);
}

