/***********************************************************************************
 * \file Test_Formatter.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 23:40:29
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#include "elink/iec60870/formatter/Formatter.h"

#include <gtest/gtest.h>

using namespace elink::iec60870;

class FormatterTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(FormatterTest, IOAFormat)
{
    constexpr int validIOA = 200;
    InformationObjectAddress ioaParam{validIOA, IOAByteLength::Two};

    EXPECT_EQ(std::format("IOA: {}", ioaParam), "IOA: 200");
    EXPECT_EQ(std::format("{:#06x}", ioaParam), "0x00c8");
    EXPECT_EQ(std::format("{:#06X}", ioaParam), "0X00C8");
}

TEST_F(FormatterTest, TypeIDFormat)
{
    using elink::iec60870::TypeID;

    // IEC60870 TypeID
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_SP_NA_1), "Ti: M_SP_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_SP_TA_1), "Ti: M_SP_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_DP_NA_1), "Ti: M_DP_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_DP_TA_1), "Ti: M_DP_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ST_NA_1), "Ti: M_ST_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ST_TA_1), "Ti: M_ST_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_BO_NA_1), "Ti: M_BO_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_BO_TA_1), "Ti: M_BO_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_NA_1), "Ti: M_ME_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_TA_1), "Ti: M_ME_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_NB_1), "Ti: M_ME_NB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_TB_1), "Ti: M_ME_TB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_NC_1), "Ti: M_ME_NC_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_TC_1), "Ti: M_ME_TC_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_IT_NA_1), "Ti: M_IT_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_IT_TA_1), "Ti: M_IT_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_EP_TA_1), "Ti: M_EP_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_EP_TB_1), "Ti: M_EP_TB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_EP_TC_1), "Ti: M_EP_TC_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_PS_NA_1), "Ti: M_PS_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_ND_1), "Ti: M_ME_ND_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_SP_TB_1), "Ti: M_SP_TB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_DP_TB_1), "Ti: M_DP_TB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ST_TB_1), "Ti: M_ST_TB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_BO_TB_1), "Ti: M_BO_TB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_TD_1), "Ti: M_ME_TD_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_TE_1), "Ti: M_ME_TE_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_ME_TF_1), "Ti: M_ME_TF_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_IT_TB_1), "Ti: M_IT_TB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_EP_TD_1), "Ti: M_EP_TD_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_EP_TE_1), "Ti: M_EP_TE_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_EP_TF_1), "Ti: M_EP_TF_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_SC_NA_1), "Ti: C_SC_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_DC_NA_1), "Ti: C_DC_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_RC_NA_1), "Ti: C_RC_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_SE_NA_1), "Ti: C_SE_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_SE_NB_1), "Ti: C_SE_NB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_SE_NC_1), "Ti: C_SE_NC_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_BO_NA_1), "Ti: C_BO_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_SC_TA_1), "Ti: C_SC_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_DC_TA_1), "Ti: C_DC_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_RC_TA_1), "Ti: C_RC_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_SE_TA_1), "Ti: C_SE_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_SE_TB_1), "Ti: C_SE_TB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_SE_TC_1), "Ti: C_SE_TC_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_BO_TA_1), "Ti: C_BO_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::M_EI_NA_1), "Ti: M_EI_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_IC_NA_1), "Ti: C_IC_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_CI_NA_1), "Ti: C_CI_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_RD_NA_1), "Ti: C_RD_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_CS_NA_1), "Ti: C_CS_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_TS_NA_1), "Ti: C_TS_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_RP_NA_1), "Ti: C_RP_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_CD_NA_1), "Ti: C_CD_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::C_TS_TA_1), "Ti: C_TS_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::P_ME_NA_1), "Ti: P_ME_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::P_ME_NB_1), "Ti: P_ME_NB_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::P_ME_NC_1), "Ti: P_ME_NC_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::P_AC_NA_1), "Ti: P_AC_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::F_FR_NA_1), "Ti: F_FR_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::F_SR_NA_1), "Ti: F_SR_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::F_SC_NA_1), "Ti: F_SC_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::F_LS_NA_1), "Ti: F_LS_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::F_AF_NA_1), "Ti: F_AF_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::F_SG_NA_1), "Ti: F_SG_NA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::F_DR_TA_1), "Ti: F_DR_TA_1");
    EXPECT_EQ(std::format("Ti: {}", TypeID::F_SC_NB_1), "Ti: F_SC_NB_1");
}

TEST_F(FormatterTest, InformationObjectFormat)
{
    SinglePointInformation sio{IOA{450}, true, Quality::BLOCKED};

    EXPECT_EQ(std::format("{:}", sio), "SinglePointInformation{M_SP_NA_1: ioa=450 raw=[0x11]}");
    EXPECT_EQ(std::format("{:b}", sio), "SinglePointInformation{M_SP_NA_1: raw=[0xc2, 0x01, 0x00, 0x11]}");
    EXPECT_EQ(std::format("{:b3}", sio), "SinglePointInformation{M_SP_NA_1: raw=[0xc2, 0x01, 0x00...]}");
    EXPECT_EQ(std::format("{:b3x}", sio), "SinglePointInformation{M_SP_NA_1: raw=[0xc2, 0x01, 0x00...]}");
    EXPECT_EQ(std::format("{:b3X}", sio), "SinglePointInformation{M_SP_NA_1: raw=[0xC2, 0x01, 0x00...]}");
}

TEST_F(FormatterTest, SinglePointWithCP24Time2aFormat)
{
    SinglePointWithCP24Time2a sio{IOA{300}, true, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{:}", sio), "SinglePointWithCP24Time2a{M_SP_TA_1: ioa=300 raw=[0x11, 0x00, 0x00, 0x00]}");
}

TEST_F(FormatterTest, DoublePointInformationFormat)
{
    DoublePointInformation dio{IOA{300}, DValue::OFF, Quality::BLOCKED};
    EXPECT_EQ(std::format("{:}", dio), "DoublePointInformation{M_DP_NA_1: ioa=300 raw=[0x11]}");
}

TEST_F(FormatterTest, DoublePointWithCP24Time2aFormat)
{
    DoublePointWithCP24Time2a dio{IOA{300}, DValue::OFF, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{:}", dio), "DoublePointWithCP24Time2a{M_DP_TA_1: ioa=300 raw=[0x11, 0x00, 0x00, 0x00]}");
}


TEST_F(FormatterTest, StepPositionInformationFormat)
{
    StepPositionInformation sio{IOA{300}, 20, true, Quality::BLOCKED};
    EXPECT_EQ(std::format("{:}", sio), "StepPositionInformation{M_ST_NA_1: ioa=300 raw=[0x94, 0x10]}");
}

TEST_F(FormatterTest, StepPositionWithCP24Time2aFormat)
{
    StepPositionWithCP24Time2a sio{IOA{300}, 20, true, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{:}", sio), "StepPositionWithCP24Time2a{M_ST_TA_1: ioa=300 raw=[0x94, 0x10, 0x00, 0x00, 0x00]}");
}
