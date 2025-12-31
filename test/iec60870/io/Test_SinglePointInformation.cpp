/***********************************************************************************
 * \file Test_SinglePointInformation.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test SinglePointInformation
 * \date 2025-12-16 22:14:09
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

class SinglePointInformationTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    const int validIOA = 0x200;
    SinglePointInformation sio{IOA{validIOA}, true, SQuality::BLOCKED};
};

TEST_F(SinglePointInformationTest, TypeID)
{
    EXPECT_EQ(sio.getTypeID(), TypeID::M_SP_NA_1);
}

TEST_F(SinglePointInformationTest, IOA)
{
    EXPECT_EQ(sio.getInformationObjectAddress().address(), validIOA);

    constexpr int newAddress = 0x300;
    sio.setInformationObjectAddress(IOA{newAddress});
    EXPECT_EQ(sio.getInformationObjectAddress().address(), newAddress);
}

TEST_F(SinglePointInformationTest, Value)
{
    EXPECT_TRUE(sio.getValue());
    sio.setValue(false);
    EXPECT_FALSE(sio.getValue());
}

TEST_F(SinglePointInformationTest, Quality)
{
    EXPECT_TRUE(sio.getQuality() & SQuality::BLOCKED);
    EXPECT_FALSE(sio.getQuality() & SQuality::SUBSTITUTED);
    EXPECT_FALSE(sio.getQuality() & SQuality::NON_TOPICAL);

    sio.setQuality(SQuality::SUBSTITUTED | SQuality::NON_TOPICAL);
    EXPECT_TRUE(sio.getQuality() & SQuality::SUBSTITUTED);
    EXPECT_TRUE(sio.getQuality() & SQuality::NON_TOPICAL);
}

TEST_F(SinglePointInformationTest, Serialize)
{
    const SinglePointInformation::OriginPtr ptr = std::make_shared<SinglePointInformation>(sio);
    uint8_t buffer[256]{};
    internal::OStream os{buffer, sizeof(buffer)};
    EXPECT_TRUE(ptr->serialize(os, false));
    EXPECT_FALSE(os.hasError());
    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x11};
    EXPECT_EQ(os.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(SinglePointInformationTest, Deserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x10};
    internal::IStream is{buffer, sizeof(buffer)};

    const auto pSio = std::make_shared<SinglePointInformation>(sio);
    const SinglePointInformation::OriginPtr iop = pSio;
    EXPECT_TRUE(iop->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.readBytes(), sizeof(buffer));

    EXPECT_EQ(iop->getInformationObjectAddress().address(), 0x300);
    EXPECT_FALSE(pSio->getValue());
    EXPECT_TRUE(pSio->getQuality() & SQuality::BLOCKED);
    EXPECT_FALSE(pSio->getQuality() & SQuality::SUBSTITUTED);
    EXPECT_FALSE(pSio->getQuality() & SQuality::NON_TOPICAL);
    EXPECT_FALSE(pSio->getQuality() & SQuality::INVALID);
}

TEST_F(SinglePointInformationTest, IOLength)
{
    EXPECT_EQ(sio.size(), 4);
}
