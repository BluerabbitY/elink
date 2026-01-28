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
#include <cstring>

class IStreamTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(IStreamTest, ReadIOA)
{
    constexpr uint8_t buffer[] = {0x34, 0x12, 0x56, 0x34, 0x12};
    elink::iec60870::details::IStream stream{buffer, sizeof(buffer)};

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

TEST_F(IStreamTest, ReadCPxxtime2a)
{
    constexpr uint8_t buffer[] = {0x64, 0x00, 0xdc, 0xe6, 0xfb, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x00, 0x7b,
                                  0x00, 0x19};
    elink::iec60870::details::IStream stream{buffer, sizeof(buffer)};

    std::size_t length = 0;
    elink::iec60870::CP16Time2a cp16Time2a{};
    stream >> cp16Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::details::CP16Time2aTag;
    EXPECT_EQ(stream.readBytes(), length);
    EXPECT_EQ(cp16Time2a.getEplapsedTimeInMs(), 100);

    elink::iec60870::CP24Time2a cp24Time2a{};
    stream >> cp24Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::details::CP24Time2aTag;
    EXPECT_EQ(stream.readBytes(), length);
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    EXPECT_TRUE(cp24Time2a.isInvalid());
    EXPECT_TRUE(cp24Time2a.isSubstituted());

    elink::iec60870::CP32Time2a cp32Time2a{};
    stream >> cp32Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::details::CP32Time2aTag;
    EXPECT_EQ(stream.readBytes(), length);
    EXPECT_EQ(cp32Time2a.getHour(), 22);
    EXPECT_TRUE(cp32Time2a.isSummerTime());

    elink::iec60870::CP56Time2a cp56Time2a{};
    stream >> cp56Time2a;
    EXPECT_FALSE(stream.hasError());
    length += elink::iec60870::details::CP56Time2aTag;
    EXPECT_EQ(stream.readBytes(), length);
    EXPECT_EQ(cp56Time2a.getDayOfWeek(), 3);
    EXPECT_EQ(cp56Time2a.getDayOfMonth(), 27);
    EXPECT_EQ(cp56Time2a.getYear(), 2025);
}
