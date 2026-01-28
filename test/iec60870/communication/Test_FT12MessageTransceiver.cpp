/***********************************************************************************
 * \file Test_FT12MessageTransceiver.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-18 01:32:01
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
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
