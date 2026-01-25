/***********************************************************************************
* \file Test_DoublePointWithCP24Time2a.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-12-31 13:42:05
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

class DoublePointWithCP24Time2aTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    const int validIOA = 0x200;
    DoublePointWithCP24Time2a dio{IOA{validIOA}, DValue::ON, Quality::BLOCKED, CP24Time2a{}};
};

TEST_F(DoublePointWithCP24Time2aTest, TypeID)
{
    EXPECT_EQ(dio.getTypeID(), TypeID::M_DP_TA_1);
}

TEST_F(DoublePointWithCP24Time2aTest, IOA)
{
    EXPECT_EQ(dio.getInformationObjectAddress().address(), validIOA);

    constexpr int newAddress = 0x300;
    dio.setInformationObjectAddress(IOA{newAddress});
    EXPECT_EQ(dio.getInformationObjectAddress().address(), newAddress);
}

TEST_F(DoublePointWithCP24Time2aTest, Value)
{
    EXPECT_TRUE(dio.getValue());
    dio.setValue(DValue::OFF);
    EXPECT_EQ(dio.getValue(), DValue::OFF);
}

TEST_F(DoublePointWithCP24Time2aTest, Quality)
{
    EXPECT_TRUE(dio.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(dio.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(dio.getQuality() & Quality::NON_TOPICAL);

    dio.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL);
    EXPECT_TRUE(dio.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(dio.getQuality() & Quality::NON_TOPICAL);
}

TEST_F(DoublePointWithCP24Time2aTest, Serialize)
{
    const DoublePointWithCP24Time2a::SerializePtr ptr = std::make_shared<DoublePointWithCP24Time2a>(dio);
    uint8_t buffer[256]{};
    internal::OStream os{buffer, sizeof(buffer)};
    EXPECT_TRUE(ptr->serialize(os, false));
    EXPECT_FALSE(os.hasError());
    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x12, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(DoublePointWithCP24Time2aTest, Deserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x13, 0x00, 0x00, 0x00};
    internal::IStream is{buffer, sizeof(buffer)};

    const auto pDio = std::make_shared<DoublePointWithCP24Time2a>(dio);
    const DoublePointWithCP24Time2a::SerializePtr iop = pDio;
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

TEST_F(DoublePointWithCP24Time2aTest, IOLength)
{
    EXPECT_EQ(dio.size(), 7);
}
