/***********************************************************************************
 * \file Test_InformationObjectSerializable.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 19:59:20
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#include "Mock/MockInformationObjectSerializable.hpp"
#include "elink/iec60870/io/InformationObjectUtil.hpp"

#include <gtest/gtest.h>

using namespace elink::iec60870;

class InformationObjectSerializableTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(InformationObjectSerializableTest, TypeID)
{
    const mock::MockInformationObjectSerializable io;
    EXPECT_EQ(io.getTypeID(), TypeID::M_SP_NA_1);
    EXPECT_EQ(mock::MockInformationObjectSerializable::IDENT_T, TypeID::M_SP_NA_1);
}

TEST_F(InformationObjectSerializableTest, IOA)
{
    constexpr int validIOA = 0x200;
    mock::MockInformationObjectSerializable io{IOA{validIOA}};
    EXPECT_EQ(io.getInformationObjectAddress().address(), validIOA);

    constexpr int newAddress = 0x300;
    io.setInformationObjectAddress(IOA{newAddress});
    EXPECT_EQ(io.getInformationObjectAddress().address(), newAddress);
}

TEST_F(InformationObjectSerializableTest, IOCast)
{
    mock::MockInformationObjectSerializable mockio;
    InformationObject& io = mockio;
    auto& castedSio = io_cast<mock::MockInformationObjectSerializable>(io);
    EXPECT_EQ(&castedSio, &mockio);
}
