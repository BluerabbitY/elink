/***********************************************************************************
 * \file Test_CommandSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 11:12:04
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
#include "elink/iec60870/io/SingleCommand.hpp"
#include "elink/iec60870/io/DoubleCommand.hpp"
#include "elink/iec60870/io/StepCommand.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class CommandSetTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(CommandSetTest, TypeID)
{
    const SingleCommand sio;
    EXPECT_EQ(sio.getTypeID(), TypeID::C_SC_NA_1);

    const DoubleCommand dio;
    EXPECT_EQ(dio.getTypeID(), TypeID::C_DC_NA_1);

    const StepCommand stepio;
    EXPECT_EQ(stepio.getTypeID(), TypeID::C_RC_NA_1);
}

TEST_F(CommandSetTest, IOLength)
{
    const SingleCommand sio;
    EXPECT_EQ(sio.size(), 4);
    EXPECT_EQ(sio.length(true), 1);

    const SingleCommand dio;
    EXPECT_EQ(dio.size(), 4);
    EXPECT_EQ(dio.length(true), 1);

    const StepCommand stepio;
    EXPECT_EQ(stepio.size(), 4);
    EXPECT_EQ(stepio.length(true), 1);
}

TEST_F(CommandSetTest, CommonImpSelect)
{
    SingleCommand io;
    EXPECT_FALSE(io.isSelect());
    io.setSelect(true);
    EXPECT_TRUE(io.isSelect());
}

TEST_F(CommandSetTest, CommonImpQU)
{
    SingleCommand io;
    EXPECT_EQ(io.getQU(), QUValue::NO_ADDITIONAL_DEFINITION);
    io.setQU(QUValue::PERSISTENT_OUTPUT);
    EXPECT_EQ(io.getQU(), QUValue::PERSISTENT_OUTPUT);
}

TEST_F(CommandSetTest, CommonImpState)
{
    SingleCommand sio;
    EXPECT_FALSE(sio.getState());
    sio.setState(true);
    EXPECT_TRUE(sio.getState());

    DoubleCommand dio;
    EXPECT_EQ(dio.getState(), DoubleCommandValue::OFF);
    dio.setState(DoubleCommandValue::ON);
    EXPECT_EQ(dio.getState(), DoubleCommandValue::ON);

    StepCommand stepio;
    EXPECT_EQ(stepio.getState(), StepCommandValue::LOWER);
    stepio.setState(StepCommandValue::HIGHER);
    EXPECT_EQ(stepio.getState(), StepCommandValue::HIGHER);
}

TEST_F(CommandSetTest, SingleCommandSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const SingleCommand::SerializePtr ios =
        std::make_shared<SingleCommand>(IOA{0x200}, true, QUValue::NO_ADDITIONAL_DEFINITION, true);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x81};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(CommandSetTest, SingleCommandDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x81};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<SingleCommand>();
    const SingleCommand::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_TRUE(io->getState());
    EXPECT_TRUE(io->isSelect());
    EXPECT_EQ(io->getQU(), QUValue::NO_ADDITIONAL_DEFINITION);
}

TEST_F(CommandSetTest, DoubleCommandSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const DoubleCommand::SerializePtr ios =
        std::make_shared<DoubleCommand>(IOA{0x200}, true, QUValue::NO_ADDITIONAL_DEFINITION, DoubleCommandValue::OFF);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x81};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(CommandSetTest, DoubleCommandDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x82};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<DoubleCommand>();
    const DoubleCommand::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getState(), DoubleCommandValue::ON);
    EXPECT_TRUE(io->isSelect());
    EXPECT_EQ(io->getQU(), QUValue::NO_ADDITIONAL_DEFINITION);
}

TEST_F(CommandSetTest, StepCommandSerialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const StepCommand::SerializePtr ios =
        std::make_shared<StepCommand>(IOA{0x200}, true, QUValue::NO_ADDITIONAL_DEFINITION, StepCommandValue::HIGHER);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x82};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);
}

TEST_F(CommandSetTest, StepCommandDeserialize)
{
    constexpr uint8_t buffer[] = {0x00, 0x03, 0x00, 0x82};
    details::IStream is{buffer, sizeof(buffer)};

    const auto io = std::make_shared<StepCommand>();
    const StepCommand::SerializePtr ios = io;
    EXPECT_TRUE(ios->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(buffer));

    EXPECT_EQ(ios->getInformationObjectAddress(), 0x300);
    EXPECT_EQ(io->getState(), StepCommandValue::HIGHER);
    EXPECT_TRUE(io->isSelect());
    EXPECT_EQ(io->getQU(), QUValue::NO_ADDITIONAL_DEFINITION);
}
