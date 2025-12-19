/***********************************************************************************
 * \file Test_IStream.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test IStream
 * \date 2025-12-17 23:11:00
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

class IStreamTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(IStreamTest, ReadArithmetic)
{
    constexpr uint8_t buffer[256]{0x12, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12};
    elink::iec60870::internal::IStream stream{buffer, sizeof(buffer)};

    std::size_t length = 0;
    uint8_t value_u8{0x00};
    stream >> value_u8;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.readBytes(), sizeof(uint8_t));
    EXPECT_EQ(value_u8, 0x12);

    length = stream.readBytes();
    uint16_t value_u16{0x0000};
    stream >> value_u16;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.readBytes(), length + sizeof(uint16_t));
    EXPECT_EQ(value_u16, 0x1234);

    length = stream.readBytes();
    uint32_t value_u32{0};
    stream >> value_u32;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.readBytes(), length + sizeof(uint32_t));
    EXPECT_EQ(value_u32, 0x12345678);
}

TEST_F(IStreamTest, ReadFloat)
{
    constexpr uint8_t buffer[] = {0x9A, 0x99, 0x31, 0x41};
    elink::iec60870::internal::IStream stream{buffer, sizeof(buffer)};

    float fixpoint = 0;
    stream >> fixpoint;
    EXPECT_FALSE(stream.hasError());
    EXPECT_FLOAT_EQ(fixpoint, 11.1F);
}

TEST_F(IStreamTest, ReadEnumAndEnumClass)
{
    constexpr uint8_t buffer[] = {0x33, 0x3A};
    elink::iec60870::internal::IStream stream{buffer, sizeof(buffer)};

    std::size_t length = 0;
    elink::iec60870::TypeID iotypeid;
    stream >> iotypeid;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.readBytes(), sizeof(std::underlying_type_t<elink::iec60870::TypeID>));
    EXPECT_EQ(iotypeid, elink::iec60870::TypeID::C_BO_NA_1);

    length = stream.readBytes();
    stream >> iotypeid;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.readBytes(), length + sizeof(std::underlying_type_t<elink::iec60870::TypeID>));
    EXPECT_EQ(iotypeid, elink::iec60870::TypeID::C_SC_TA_1);
}

TEST_F(IStreamTest, ReadIOA)
{
    constexpr uint8_t buffer[] = {0x34, 0x12, 0x56, 0x34, 0x12};
    elink::iec60870::internal::IStream stream{buffer, sizeof(buffer)};

    std::size_t length = 0;
    elink::iec60870::IOA ioa(0, elink::iec60870::IOAByteLength::Two);
    stream >> ioa;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.readBytes(), static_cast<int>(elink::iec60870::IOAByteLength::Two));
    EXPECT_EQ(ioa.address(), 0x1234);

    length = stream.readBytes();
    ioa.resetLengthOfInformationObjectAddress(elink::iec60870::IOAByteLength::Three);
    stream >> ioa;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.readBytes(), length + static_cast<int>(elink::iec60870::IOAByteLength::Three));
    EXPECT_EQ(ioa.address(), 0x123456);
}

TEST_F(IStreamTest, ReadSpan)
{
    constexpr uint8_t buffer[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    elink::iec60870::internal::IStream stream{buffer, sizeof(buffer)};

    uint8_t dest[sizeof(buffer)]{};
    std::span span_dest{dest, sizeof(dest)};

    stream >> span_dest;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.readBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(IStreamTest, ReadOverflow)
{
    uint8_t buffer[16]{};
    elink::iec60870::internal::IStream stream{buffer, sizeof(buffer)};

    uint8_t dest[512]{};
    std::span span_dest{dest, sizeof(dest)};

    stream >> span_dest;
    EXPECT_TRUE(stream.hasError());
    stream.acknowledgeError();
    EXPECT_FALSE(stream.hasError());
}
