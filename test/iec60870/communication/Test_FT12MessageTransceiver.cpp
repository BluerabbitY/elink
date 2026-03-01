/***********************************************************************************
 * \file Test_FT12MessageTransceiver.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-18 01:32:01
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
#include "elink/iec60870/communication/link_layer/FT12MessageTransceiver.hpp"
#include "elink/iec60870/communication/link_layer/SerialFT12MessageTransceiver.hpp"

#include "./mock/MockSerial.hpp"

#include <gtest/gtest.h>

class FT12MessageTransceiverTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    elink::Component componentM{};
    int addressLengthM{2};
    elink::iec60870::ft12::Transceiver<mock::Serial> transceiverM{componentM, addressLengthM};
};

TEST_F(FT12MessageTransceiverTest, Construct)
{
    const auto ptr = std::make_unique<elink::iec60870::ft12::SerialTransceiver>(componentM, addressLengthM);
    EXPECT_NE(ptr, nullptr);
}

TEST_F(FT12MessageTransceiverTest, Run)
{
}
