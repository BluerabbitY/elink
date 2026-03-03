/***********************************************************************************
 * \file Test_EventOfProtectionEquipmentSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-03 23:41:57
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ***********************************************************************************/
#include "elink/iec60870/io/EventOfProtectionEquipment.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class EventOfProtectionEquipmentSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(EventOfProtectionEquipmentSetTest, TypeID)
{
    const EventOfProtectionEquipment io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_EP_TA_1);
}

TEST_F(EventOfProtectionEquipmentSetTest, IOLength)
{
    const EventOfProtectionEquipment io;
    EXPECT_EQ(io.size(), 9);
    EXPECT_EQ(io.length(true), 6);
}

TEST_F(EventOfProtectionEquipmentSetTest, CommonImpEvent)
{
    const SingleEvent event{EventState::ON, QualityP::GOOD};
    const SingleEvent event1{EventState::OFF, QualityP::GOOD};
    EventOfProtectionEquipment io{IOA{0x200}, event, CP16Time2a{12349}};

    EXPECT_EQ(io.getEvent().getEventState(), EventState::ON);
    io.setEvent(event1);
    EXPECT_EQ(io.getEvent().getEventState(), EventState::OFF);

    EXPECT_EQ(io.getElapsedTime().getEplapsedTimeInMs(), 12349);
    io.setElapsedTime(CP16Time2a{12350});
    EXPECT_EQ(io.getElapsedTime().getEplapsedTimeInMs(), 12350);
}

TEST_F(EventOfProtectionEquipmentSetTest, EventOfProtectionEquipmentSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const SingleEvent event{EventState::ON, QualityP::BLOCKED | QualityP::ELAPSED_TIME_INVALID};
    const EventOfProtectionEquipment::SerializePtr ios =
        std::make_shared<EventOfProtectionEquipment>(IOA{0x200}, event, CP16Time2a{12349}, CP24Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x1a, 0x3d, 0x30, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(EventOfProtectionEquipmentSetTest, EventOfProtectionEquipmentDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x1a, 0x3d, 0x30, 0xdc, 0xe6, 0xfb};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<EventOfProtectionEquipment>();
    const EventOfProtectionEquipment::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);

    auto event = io->getEvent();
    EXPECT_EQ(io->getEvent().getEventState(), EventState::ON);
    EXPECT_TRUE(event.getQDP() & QualityP::ELAPSED_TIME_INVALID);
    EXPECT_TRUE(event.getQDP() & QualityP::BLOCKED);
    EXPECT_FALSE(event.getQDP() & QualityP::SUBSTITUTED);
    EXPECT_FALSE(event.getQDP() & QualityP::NON_TOPICAL);
    EXPECT_FALSE(event.getQDP() & QualityP::INVALID);

    auto cp24Time2a = io->getTimestamp();
    EXPECT_EQ(cp24Time2a.getMillisecond(), 100);
    EXPECT_EQ(cp24Time2a.getSecond(), 59);
    EXPECT_EQ(cp24Time2a.getMinute(), 59);
    EXPECT_TRUE(cp24Time2a.isInvalid());
    EXPECT_TRUE(cp24Time2a.isSubstituted());
}
