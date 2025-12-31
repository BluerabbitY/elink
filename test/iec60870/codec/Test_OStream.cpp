/***********************************************************************************
 * \file Test_OStream.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test OStream
 * \date 2025-12-15 23:00:51
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

class OStreamTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    uint8_t buffer[256]{};
    elink::iec60870::internal::OStream stream{buffer, sizeof(buffer)};
};

TEST_F(OStreamTest, WriteArithmetic)
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

TEST_F(OStreamTest, WriteFloat)
{
    constexpr float fixpoint = 11.1;
    stream << fixpoint;
    EXPECT_FALSE(stream.hasError());

    constexpr uint8_t dest[] = {0x9A, 0x99, 0x31, 0x41};
    EXPECT_EQ(stream.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamTest, WriteEnumAndEnumClass)
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

TEST_F(OStreamTest, WriteIOA)
{
    std::size_t length = 0;
    const elink::iec60870::IOA ioa1(0x1234, elink::iec60870::IOAByteLength::Two);
    stream << ioa1;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), static_cast<int>(elink::iec60870::IOAByteLength::Two));

    length = stream.writenBytes();
    const elink::iec60870::IOA ioa2(0x123456);
    stream << ioa2;
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), length + static_cast<int>(elink::iec60870::IOAByteLength::Three));

    constexpr uint8_t dest[] = {0x34, 0x12, 0x56, 0x34, 0x12};
    EXPECT_EQ(stream.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamTest, WriteCPxxtime2a)
{
    std::size_t length = 0;
    elink::iec60870::CP16Time2a cp16Time2a{};
    cp16Time2a.setEplapsedTimeInMs(100);
    stream << cp16Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::internal::CP16Time2aTag;
    EXPECT_EQ(stream.writenBytes(), length);

    elink::iec60870::CP24Time2a cp24Time2a{};
    cp24Time2a.setMillisecond(100);
    cp24Time2a.setSecond(59);
    cp24Time2a.setMinute(59);
    cp24Time2a.setInvalid(true);
    cp24Time2a.setSubstituted(true);
    stream << cp24Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::internal::CP24Time2aTag;
    EXPECT_EQ(stream.writenBytes(), length);

    elink::iec60870::CP32Time2a cp32Time2a{};
    cp32Time2a.setHour(22);
    cp32Time2a.setSummerTime(true);
    stream << cp32Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::internal::CP32Time2aTag;
    EXPECT_EQ(stream.writenBytes(), length);

    elink::iec60870::CP56Time2a cp56Time2a{};
    cp56Time2a.setDayOfWeek(3);
    cp56Time2a.setDayOfMonth(27);
    cp56Time2a.setYear(2025);
    stream << cp56Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::internal::CP56Time2aTag;
    EXPECT_EQ(stream.writenBytes(), length);

    constexpr uint8_t dest[] = {0x64, 0x00, 0xdc, 0xe6, 0xfb, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x00, 0x7b,
                                0x00, 0x19};
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamTest, WriteSpan)
{
    constexpr uint8_t dest[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    stream << std::span{dest, sizeof(dest)};
    EXPECT_FALSE(stream.hasError());
    EXPECT_EQ(stream.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(OStreamTest, WriteOverflow)
{
    constexpr uint8_t buffer[512]{};
    stream << std::span{buffer, sizeof(buffer)};
    EXPECT_TRUE(stream.hasError());
    stream.acknowledgeError();
    EXPECT_FALSE(stream.hasError());
}
