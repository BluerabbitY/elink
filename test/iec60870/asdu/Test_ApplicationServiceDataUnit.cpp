/***********************************************************************************
 * \file Test_ApplicationServiceDataUnit.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2026-02-16 00:12:11
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
#include "elink/iec60870/ApplicationServiceDataUnit.hpp"
#include "elink/iec60870/io/SinglePointInformation.hpp"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class ApplicationServiceDataUnitTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(ApplicationServiceDataUnitTest, Constructor)
{
    const AppLayerParameters params;
    cs101::ASDU asdu{params, true, COT::REQUEST, 250, 200, true, true};

    EXPECT_TRUE(asdu.isSequence());
    EXPECT_EQ(asdu.getCOT(), COT::REQUEST);
    EXPECT_TRUE(asdu.isTest());
    EXPECT_TRUE(asdu.isNegative());
    EXPECT_EQ(asdu.getOA(), 250);
    EXPECT_EQ(asdu.getCA(), 200);
}

TEST_F(ApplicationServiceDataUnitTest, SetGetFields)
{
    // defaults: COT length = Two, CA = Two, IOA = Three
    const AppLayerParameters params;
    cs101::ASDU asdu{params};

    asdu.setTypeID(TypeID::M_SP_NA_1);
    EXPECT_EQ(asdu.getTypeID(), TypeID::M_SP_NA_1);

    asdu.setSequence(true);
    EXPECT_TRUE(asdu.isSequence());
    asdu.setSequence(false);
    EXPECT_FALSE(asdu.isSequence());

    EXPECT_EQ(asdu.getNumberOfElements(), 0);
    asdu.setNumberOfElements(5);
    EXPECT_EQ(asdu.getNumberOfElements(), 5);

    asdu.setCOT(COT::SPONTANEOUS);
    EXPECT_EQ(asdu.getCOT(), COT::SPONTANEOUS);

    asdu.setTest(true);
    EXPECT_TRUE(asdu.isTest());
    asdu.setTest(false);
    EXPECT_FALSE(asdu.isTest());

    asdu.setNegative(true);
    EXPECT_TRUE(asdu.isNegative());
    asdu.setNegative(false);
    EXPECT_FALSE(asdu.isNegative());

    // OA and CA (Common Address) operations
    asdu.setOA(200);
    EXPECT_EQ(asdu.getOA(), 200);

    asdu.setCA(250);
    EXPECT_EQ(asdu.getCA(), 250);
}

TEST_F(ApplicationServiceDataUnitTest, PayloadAndRemove)
{
    const AppLayerParameters params;
    cs101::ASDU asdu{params};

    constexpr uint8_t data[] = {0xaa, 0xbb, 0xcc, 0xdd};
    EXPECT_TRUE(asdu.addPayload(elink::LiteBufferView{data, static_cast<int>(sizeof(data))}));

    const auto payload = asdu.getPayload();
    EXPECT_EQ(payload.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(payload.data(), data, sizeof(data)), 0);

    asdu.setNumberOfElements(3);
    EXPECT_EQ(asdu.getNumberOfElements(), 3);
    asdu.removeAllElements();
    EXPECT_EQ(asdu.getNumberOfElements(), 0);
    const auto payload2 = asdu.getPayload();
    EXPECT_EQ(payload2.size(), 0);
}

TEST_F(ApplicationServiceDataUnitTest, AddInformationObject)
{
    AppLayerParameters params;
    cs101::ASDU asdu{params};

    asdu.setSequence(true);

    const SinglePointInformation sio1{IOA{0x200}, true, Quality::BLOCKED};

    EXPECT_TRUE(asdu.addInformationObject(sio1));

    const auto payload = asdu.getPayload();
    EXPECT_EQ(payload.size(), sio1.size());
    EXPECT_EQ(asdu.getNumberOfElements(), 1);

    const SinglePointInformation sio2{IOA{0x201}, true, Quality::SUBSTITUTED};
    EXPECT_TRUE(asdu.addInformationObject(sio2));
    EXPECT_EQ(asdu.getNumberOfElements(), 2);

    const SinglePointInformation sio3{IOA{0x202}, true, Quality::INVALID};
    EXPECT_TRUE(asdu.addInformationObject(sio3));
    EXPECT_EQ(asdu.getNumberOfElements(), 3);

    const SinglePointInformation sio4{IOA{0x204}, true, Quality::SUBSTITUTED};
    EXPECT_FALSE(asdu.addInformationObject(sio4));
    EXPECT_EQ(asdu.getNumberOfElements(), 3);

    auto sio = asdu.getElement<SinglePointInformation>(4);
    EXPECT_EQ(sio, std::nullopt);

    auto dio = asdu.getElement<DoublePointInformation>(0);
    EXPECT_EQ(dio, std::nullopt);

    auto validsio = asdu.getElement<SinglePointInformation>(2);
    EXPECT_TRUE(validsio.has_value());

    EXPECT_EQ(validsio->getInformationObjectAddress().address(), 0x202);
    EXPECT_EQ(validsio->getValue(), true);
    EXPECT_EQ(validsio->getQuality(), Quality::INVALID);
}

// Duplicate tests for CS104 ASDU
TEST_F(ApplicationServiceDataUnitTest, SetGetFields_CS104)
{
    const AppLayerParameters params;
    cs104::ASDU asdu{params};

    asdu.setTypeID(TypeID::M_SP_NA_1);
    EXPECT_EQ(asdu.getTypeID(), TypeID::M_SP_NA_1);

    asdu.setSequence(true);
    EXPECT_TRUE(asdu.isSequence());
    asdu.setSequence(false);
    EXPECT_FALSE(asdu.isSequence());

    asdu.setNumberOfElements(5);
    EXPECT_EQ(asdu.getNumberOfElements(), 5);

    asdu.setCOT(COT::SPONTANEOUS);
    EXPECT_EQ(asdu.getCOT(), COT::SPONTANEOUS);

    asdu.setTest(true);
    EXPECT_TRUE(asdu.isTest());
    asdu.setTest(false);
    EXPECT_FALSE(asdu.isTest());

    asdu.setNegative(true);
    EXPECT_TRUE(asdu.isNegative());
    asdu.setNegative(false);
    EXPECT_FALSE(asdu.isNegative());

    asdu.setOA(0x11);
    EXPECT_EQ(asdu.getOA(), 0x11);

    asdu.setCA(0x1234);
    EXPECT_EQ(asdu.getCA(), 0x1234);
}

TEST_F(ApplicationServiceDataUnitTest, PayloadAndRemove_CS104)
{
    const AppLayerParameters params;
    cs104::ASDU asdu{params};

    constexpr uint8_t data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    EXPECT_TRUE(asdu.addPayload(elink::LiteBufferView{data, static_cast<int>(sizeof(data))}));

    const auto payload = asdu.getPayload();
    EXPECT_EQ(payload.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(payload.data(), data, sizeof(data)), 0);

    asdu.setNumberOfElements(3);
    EXPECT_EQ(asdu.getNumberOfElements(), 3);
    asdu.removeAllElements();
    EXPECT_EQ(asdu.getNumberOfElements(), 0);
    const auto payload2 = asdu.getPayload();
    EXPECT_EQ(payload2.size(), 0);
}

TEST_F(ApplicationServiceDataUnitTest, ConstructorFlags_CS104)
{
    const AppLayerParameters params;
    cs104::ASDU asdu{params, true, COT::REQUEST, 0x22, 0x55, true, true};

    EXPECT_TRUE(asdu.isSequence());
    EXPECT_EQ(asdu.getCOT(), COT::REQUEST);
    EXPECT_TRUE(asdu.isTest());
    EXPECT_TRUE(asdu.isNegative());
    EXPECT_EQ(asdu.getOA(), 0x22);
    EXPECT_EQ(asdu.getCA(), 0x55);
}

TEST_F(ApplicationServiceDataUnitTest, AddInformationObjectSerialize_CS104)
{
    const AppLayerParameters params;
    cs104::ASDU asdu{params};

    SinglePointInformation sio{IOA{0x200}, true, Quality::BLOCKED};

    uint8_t buffer[256]{};
    const SinglePointInformation::SerializePtr ptr = std::make_shared<SinglePointInformation>(sio);
    details::OStream os{buffer, sizeof(buffer)};

    EXPECT_TRUE(ptr->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    const std::size_t serLen = os.size();
    EXPECT_TRUE(asdu.addPayload(elink::LiteBufferView{buffer, serLen}));

    const auto payload = asdu.getPayload();
    EXPECT_EQ(payload.size(), serLen);
    EXPECT_EQ(std::memcmp(payload.data(), buffer, serLen), 0);
}
