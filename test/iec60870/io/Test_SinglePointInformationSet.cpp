/***********************************************************************************
 * \file Test_SinglePointInformationSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 22:04:27
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#include "elink/iec60870/io/SinglePointInformation.hpp"
#include "elink/iec60870/io/SinglePointWithCP24Time2a.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class SinglePointInformationSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(SinglePointInformationSetTest, TypeID)
{
    const SinglePointInformation io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_SP_NA_1);

    const SinglePointWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.getTypeID(), TypeID::M_SP_TA_1);
}

TEST_F(SinglePointInformationSetTest, IOLength)
{
    const SinglePointInformation io;
    EXPECT_EQ(io.size(), 4);
    EXPECT_EQ(io.length(true), 1);

    const SinglePointWithCP24Time2a iocp24;
    EXPECT_EQ(iocp24.size(), 7);
    EXPECT_EQ(iocp24.length(true), 4);
}

TEST_F(SinglePointInformationSetTest, CommomImpValue)
{
    SinglePointInformation io{IOA{0x200}, true, Quality::BLOCKED};

    EXPECT_TRUE(io.getValue());
    io.setValue(false);
    EXPECT_FALSE(io.getValue());
}

TEST_F(SinglePointInformationSetTest, CommomImpQuality)
{
    SinglePointInformation io{IOA{0x200}, true, Quality::BLOCKED};

    EXPECT_TRUE(io.getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io.getQuality() & Quality::NON_TOPICAL);

    io.setQuality(Quality::SUBSTITUTED | Quality::NON_TOPICAL);
    EXPECT_TRUE(io.getQuality() & Quality::SUBSTITUTED);
    EXPECT_TRUE(io.getQuality() & Quality::NON_TOPICAL);
}

TEST_F(SinglePointInformationSetTest, SinglePointInformationSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const SinglePointInformation::SerializePtr ios =
        std::make_shared<SinglePointInformation>(IOA{0x200}, true, Quality::BLOCKED);

    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x11};
    EXPECT_EQ(os.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(SinglePointInformationSetTest, SinglePointInformationDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x10};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<SinglePointInformation>(IOA{0x200}, true, Quality::BLOCKED);
    const SinglePointInformation::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.readBytes(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress().address(), 0x300);
    EXPECT_FALSE(io->getValue());
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);
}

TEST_F(SinglePointInformationSetTest, SinglePointWithCP24Time2aSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const SinglePointWithCP24Time2a::SerializePtr ios =
        std::make_shared<SinglePointWithCP24Time2a>(IOA{0x200}, true, Quality::BLOCKED, CP24Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x11, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.writenBytes(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(SinglePointInformationSetTest, SinglePointWithCP24Time2aDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x10, 0xdc, 0xe6, 0xfb};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<SinglePointWithCP24Time2a>(IOA{0x200}, true, Quality::BLOCKED, CP24Time2a{});
    const SinglePointWithCP24Time2a::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.readBytes(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress().address(), 0x300);
    EXPECT_FALSE(io->getValue());
    EXPECT_TRUE(io->getQuality() & Quality::BLOCKED);
    EXPECT_FALSE(io->getQuality() & Quality::SUBSTITUTED);
    EXPECT_FALSE(io->getQuality() & Quality::NON_TOPICAL);
    EXPECT_FALSE(io->getQuality() & Quality::INVALID);

    auto cp24Time2a = io->getTimestamp();
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    EXPECT_TRUE(cp24Time2a.isInvalid());
    EXPECT_TRUE(cp24Time2a.isSubstituted());
}
