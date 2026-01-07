/***********************************************************************************
 * \file Test_OStreamCommon.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-02 23:56:58
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#include <gtest/gtest.h>

#include <cstring>

#include "../../include/elink/common/codec/OStreamCommon.hpp"
#include "elink/iec60870/io/InformationObjectTypeID.h"

using namespace elink::common::internal;

class OStreamCommonTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    uint8_t buffer[256]{};
    OStreamCommon stream{buffer, sizeof(buffer)};
};

TEST_F(OStreamCommonTest, WriteArithmetic)
{
    std::size_t length = 0;
    stream << uint8_t{0x12};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), sizeof(uint8_t));

    length = stream.writenBytes();
    stream << uint16_t{0x1234};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), length + sizeof(uint16_t));

    length = stream.writenBytes();
    stream << uint32_t{0x12345678};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), length + sizeof(uint32_t));

    constexpr uint8_t dest[] = {0x12, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12};
    EXPECT_EQ(stream.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamCommonTest, WriteFloat)
{
    constexpr float fixpoint = 11.1;
    stream << fixpoint;
    EXPECT_FALSE(stream.hasError());

    constexpr uint8_t dest[] = {0x9A, 0x99, 0x31, 0x41};
    EXPECT_EQ(stream.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamCommonTest, WriteEnumAndEnumClass)
{
    std::size_t length = 0;
    stream << elink::iec60870::TypeID::C_BO_NA_1;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), sizeof(std::underlying_type_t<elink::iec60870::TypeID>));

    length = stream.writenBytes();
    stream << elink::iec60870::TypeID::C_SC_TA_1;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), length + sizeof(std::underlying_type_t<elink::iec60870::TypeID>));

    constexpr uint8_t dest[] = {0x33, 0x3A};
    EXPECT_EQ(stream.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamCommonTest, WriteSpan)
{
    uint8_t dest[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    stream << elink::LiteBufferView{dest, sizeof(dest)};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamCommonTest, WriteOverflow)
{
    uint8_t buffer[512]{};
    stream << elink::LiteBufferView{buffer, sizeof(buffer)};
    EXPECT_TRUE(stream.hasError());
    stream.acknowledgeError();
    EXPECT_FALSE(stream.hasError());
}
