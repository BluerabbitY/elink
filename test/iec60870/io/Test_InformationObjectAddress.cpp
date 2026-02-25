/***********************************************************************************
 * \file Test_InformationObjectAddress.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief unit test for class InformationObjectAddress
 * \date 2025-12-12 23:46:59
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

class InformationObjectAddressTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    static int MaxLengthOfIOAInBytes(const elink::iec60870::IOAByteLength length)
    {
        return (1 << 8 * static_cast<int>(length)) - 1;
    }

    const int validIOA = 200;
    elink::iec60870::InformationObjectAddress ioaDefault;
    elink::iec60870::InformationObjectAddress ioaParam{validIOA, elink::iec60870::IOAByteLength::Two};
};

TEST_F(InformationObjectAddressTest, Constructor)
{
    EXPECT_EQ(ioaDefault.address(), 0);
    EXPECT_EQ(ioaDefault.getLengthOfInformationObjectAddress(),
              static_cast<size_t>(elink::iec60870::IOAByteLength::Three));

    EXPECT_EQ(ioaParam.address(), validIOA);
    EXPECT_EQ(ioaParam.getLengthOfInformationObjectAddress(),
              static_cast<size_t>(elink::iec60870::IOAByteLength::Two));
}

TEST_F(InformationObjectAddressTest, ConstructorFromBuffer)
{
    uint8_t ioabuffer1[] = {0x12};
    const elink::LiteBuffer buffer1{ioabuffer1};
    const elink::iec60870::IOA ioa1{buffer1};
    EXPECT_EQ(ioa1.address(), 18);
    EXPECT_EQ(ioa1.getLengthOfInformationObjectAddress(), static_cast<size_t>(elink::iec60870::IOAByteLength::One));

    uint8_t ioabuffer2[] = {0xfe, 0xff};
    const elink::LiteBuffer buffer2{ioabuffer2};
    const elink::iec60870::IOA ioa2{buffer2};
    EXPECT_EQ(ioa2.address(), 65'534);
    EXPECT_EQ(ioa2.getLengthOfInformationObjectAddress(), static_cast<size_t>(elink::iec60870::IOAByteLength::Two));

    uint8_t ioabuffer3[] = {0xfe, 0xff, 0xff};
    const elink::LiteBuffer buffer3{ioabuffer3};
    const elink::iec60870::IOA ioa3{buffer3};
    EXPECT_EQ(ioa3.address(), 16'777'214);
    EXPECT_EQ(ioa3.getLengthOfInformationObjectAddress(), static_cast<size_t>(elink::iec60870::IOAByteLength::Three));
}

// test operator== and operator!=
TEST_F(InformationObjectAddressTest, OperatorEuqal)
{
    const elink::iec60870::InformationObjectAddress ioaCMP1{validIOA - 1, elink::iec60870::IOAByteLength::Two};
    EXPECT_NE(ioaParam, ioaCMP1);

    const elink::iec60870::InformationObjectAddress ioaCMP2{validIOA, elink::iec60870::IOAByteLength::One};
    EXPECT_NE(ioaParam, ioaCMP2);

    const elink::iec60870::InformationObjectAddress ioaCMP3{validIOA, elink::iec60870::IOAByteLength::Two};
    EXPECT_EQ(ioaParam, ioaCMP3);
}

// test operator=
TEST_F(InformationObjectAddressTest, OperatorAssignment)
{
    constexpr int invalidIOA{65536};

    EXPECT_FALSE(ioaParam.setAddress(invalidIOA));
    EXPECT_EQ(ioaParam.address(), MaxLengthOfIOAInBytes(ioaParam.getLengthOfInformationObjectAddressStrategy()));

    ioaParam = invalidIOA;
    EXPECT_EQ(ioaParam.address(), MaxLengthOfIOAInBytes(ioaParam.getLengthOfInformationObjectAddressStrategy()));

    EXPECT_TRUE(ioaParam.setAddress(validIOA));
    EXPECT_EQ(ioaParam.address(), validIOA);

    ioaParam = validIOA;
    EXPECT_EQ(ioaParam.address(), validIOA);
}

// test operator+=
TEST_F(InformationObjectAddressTest, OperatorPlus)
{
    elink::iec60870::IOA ioa{1234};
    ioa += 10;
    EXPECT_EQ(ioa.address(), 1244);
}

// test operator-
TEST_F(InformationObjectAddressTest, OperatorMinus)
{
    elink::iec60870::IOA ioa{1234};
    ioa -= 10;
    EXPECT_EQ(ioa.address(), 1224);
}

TEST_F(InformationObjectAddressTest, Limits)
{
    constexpr int invalidIOALow{-1};
    constexpr int invalidIOAOneByteHigh{256};
    constexpr int invalidIOATwoByteHigh{65536};
    constexpr int invalidIOAThreeByteHigh{16777216};

    elink::iec60870::InformationObjectAddress ioaOneByte{validIOA, elink::iec60870::IOAByteLength::One};
    EXPECT_EQ(ioaOneByte.getLengthOfInformationObjectAddress(), 1);
    EXPECT_EQ(ioaOneByte.getLengthOfInformationObjectAddressStrategy(), elink::iec60870::IOAByteLength::One);
    EXPECT_FALSE(ioaOneByte.setAddress(invalidIOALow));
    EXPECT_EQ(ioaOneByte.address(), 0);
    EXPECT_FALSE(ioaOneByte.setAddress(invalidIOAOneByteHigh));
    EXPECT_EQ(ioaOneByte.address(), MaxLengthOfIOAInBytes(elink::iec60870::IOAByteLength::One));

    elink::iec60870::InformationObjectAddress ioaTwoByte{validIOA, elink::iec60870::IOAByteLength::Two};
    EXPECT_EQ(ioaTwoByte.getLengthOfInformationObjectAddress(), 2);
    EXPECT_EQ(ioaTwoByte.getLengthOfInformationObjectAddressStrategy(), elink::iec60870::IOAByteLength::Two);
    EXPECT_FALSE(ioaTwoByte.setAddress(invalidIOALow));
    EXPECT_EQ(ioaTwoByte.address(), 0);
    EXPECT_FALSE(ioaTwoByte.setAddress(invalidIOATwoByteHigh));
    EXPECT_EQ(ioaTwoByte.address(), MaxLengthOfIOAInBytes(elink::iec60870::IOAByteLength::Two));

    elink::iec60870::InformationObjectAddress ioaThreeByte{validIOA, elink::iec60870::IOAByteLength::Three};
    EXPECT_EQ(ioaThreeByte.getLengthOfInformationObjectAddress(), 3);
    EXPECT_EQ(ioaThreeByte.getLengthOfInformationObjectAddressStrategy(), elink::iec60870::IOAByteLength::Three);
    EXPECT_FALSE(ioaThreeByte.setAddress(invalidIOALow));
    EXPECT_EQ(ioaThreeByte.address(), 0);
    EXPECT_FALSE(ioaThreeByte.setAddress(invalidIOAThreeByteHigh));
    EXPECT_EQ(ioaThreeByte.address(), MaxLengthOfIOAInBytes(elink::iec60870::IOAByteLength::Three));
}

TEST_F(InformationObjectAddressTest, ResetLength)
{
    constexpr int invalidIOAHigh{16777216};
    ioaDefault = invalidIOAHigh;

    EXPECT_EQ(ioaDefault.address(), MaxLengthOfIOAInBytes(elink::iec60870::IOAByteLength::Three));

    ioaDefault.resetLengthOfInformationObjectAddress(elink::iec60870::IOAByteLength::Two);
    EXPECT_EQ(ioaDefault.address(), MaxLengthOfIOAInBytes(elink::iec60870::IOAByteLength::Two));

    ioaDefault.resetLengthOfInformationObjectAddress(elink::iec60870::IOAByteLength::One);
    EXPECT_EQ(ioaDefault.address(), MaxLengthOfIOAInBytes(elink::iec60870::IOAByteLength::One));
}
