/***********************************************************************************
 * \file Test_Formatter.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 23:40:29
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

TEST_F(FormatterTest, COTFormat)
{
    using elink::iec60870::COT;

    EXPECT_EQ(std::format("COT: {}", COT::PERIODIC), "COT: PERIODIC");
    EXPECT_EQ(std::format("COT: {}", COT::BACKGROUND_SCAN), "COT: BACKGROUND_SCAN");
    EXPECT_EQ(std::format("COT: {}", COT::SPONTANEOUS), "COT: SPONTANEOUS");
    EXPECT_EQ(std::format("COT: {}", COT::INITIALIZED), "COT: INITIALIZED");
    EXPECT_EQ(std::format("COT: {}", COT::REQUEST), "COT: REQUEST");
    EXPECT_EQ(std::format("COT: {}", COT::ACTIVATION), "COT: ACTIVATION");
    EXPECT_EQ(std::format("COT: {}", COT::ACTIVATION_CON), "COT: ACTIVATION_CON");
    EXPECT_EQ(std::format("COT: {}", COT::DEACTIVATION), "COT: DEACTIVATION");
    EXPECT_EQ(std::format("COT: {}", COT::DEACTIVATION_CON), "COT: DEACTIVATION_CON");
    EXPECT_EQ(std::format("COT: {}", COT::ACTIVATION_TERMINATION), "COT: ACTIVATION_TERMINATION");
    EXPECT_EQ(std::format("COT: {}", COT::RETURN_INFO_REMOTE), "COT: RETURN_INFO_REMOTE");
    EXPECT_EQ(std::format("COT: {}", COT::RETURN_INFO_LOCAL), "COT: RETURN_INFO_LOCAL");
    EXPECT_EQ(std::format("COT: {}", COT::FILE_TRANSFER), "COT: FILE_TRANSFER");
    EXPECT_EQ(std::format("COT: {}", COT::AUTHENTICATION), "COT: AUTHENTICATION");
    EXPECT_EQ(std::format("COT: {}", COT::MAINTENANCE_OF_AUTH_SESSION_KEY), "COT: MAINTENANCE_OF_AUTH_SESSION_KEY");
    EXPECT_EQ(std::format("COT: {}", COT::MAINTENANCE_OF_USER_ROLE_AND_UPDATE_KEY), "COT: MAINTENANCE_OF_USER_ROLE_AND_UPDATE_KEY");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_STATION), "COT: INTERROGATED_BY_STATION");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_1), "COT: INTERROGATED_BY_GROUP_1");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_2), "COT: INTERROGATED_BY_GROUP_2");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_3), "COT: INTERROGATED_BY_GROUP_3");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_4), "COT: INTERROGATED_BY_GROUP_4");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_5), "COT: INTERROGATED_BY_GROUP_5");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_6), "COT: INTERROGATED_BY_GROUP_6");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_7), "COT: INTERROGATED_BY_GROUP_7");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_8), "COT: INTERROGATED_BY_GROUP_8");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_9), "COT: INTERROGATED_BY_GROUP_9");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_10), "COT: INTERROGATED_BY_GROUP_10");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_11), "COT: INTERROGATED_BY_GROUP_11");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_12), "COT: INTERROGATED_BY_GROUP_12");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_13), "COT: INTERROGATED_BY_GROUP_13");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_14), "COT: INTERROGATED_BY_GROUP_14");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_15), "COT: INTERROGATED_BY_GROUP_15");
    EXPECT_EQ(std::format("COT: {}", COT::INTERROGATED_BY_GROUP_16), "COT: INTERROGATED_BY_GROUP_16");
    EXPECT_EQ(std::format("COT: {}", COT::REQUESTED_BY_GENERAL_COUNTER), "COT: REQUESTED_BY_GENERAL_COUNTER");
    EXPECT_EQ(std::format("COT: {}", COT::REQUESTED_BY_GROUP_1_COUNTER), "COT: REQUESTED_BY_GROUP_1_COUNTER");
    EXPECT_EQ(std::format("COT: {}", COT::REQUESTED_BY_GROUP_2_COUNTER), "COT: REQUESTED_BY_GROUP_2_COUNTER");
    EXPECT_EQ(std::format("COT: {}", COT::REQUESTED_BY_GROUP_3_COUNTER), "COT: REQUESTED_BY_GROUP_3_COUNTER");
    EXPECT_EQ(std::format("COT: {}", COT::REQUESTED_BY_GROUP_4_COUNTER), "COT: REQUESTED_BY_GROUP_4_COUNTER");
    EXPECT_EQ(std::format("COT: {}", COT::UNKNOWN_TYPE_ID), "COT: UNKNOWN_TYPE_ID");
    EXPECT_EQ(std::format("COT: {}", COT::UNKNOWN_COT), "COT: UNKNOWN_CAUSE_OF_TRANSMISSION");
    EXPECT_EQ(std::format("COT: {}", COT::UNKNOWN_CA), "COT: UNKNOWN_COMMON_ADDRESS_OF_ASDU");
    EXPECT_EQ(std::format("COT: {}", COT::UNKNOWN_IOA), "COT: UNKNOWN_INFORMATION_OBJECT_ADDRESS");
}

TEST_F(FormatterTest, InformationObjectFormat)
{
    SinglePointInformation sio{IOA{450}, true, Quality::BLOCKED};

    EXPECT_EQ(std::format("{}", sio), "SinglePointInformation{M_SP_NA_1: ioa=450 data=[0x11]}");
    EXPECT_EQ(std::format("{:b}", sio), "SinglePointInformation{M_SP_NA_1: raw=[0xc2, 0x01, 0x00, 0x11]}");
    EXPECT_EQ(std::format("{:3b}", sio), "SinglePointInformation{M_SP_NA_1: raw=[0xc2, 0x01, 0x00...]}");
    EXPECT_EQ(std::format("{:3B}", sio), "SinglePointInformation{M_SP_NA_1: raw=[0xC2, 0x01, 0x00...]}");
}

TEST_F(FormatterTest, SinglePointWithCP24Time2aFormat)
{
    SinglePointWithCP24Time2a sio{IOA{300}, true, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", sio), "SinglePointWithCP24Time2a{M_SP_TA_1: ioa=300 data=[0x11, 0x00, 0x00, 0x00]}");
}

TEST_F(FormatterTest, DoublePointInformationFormat)
{
    DoublePointInformation dio{IOA{300}, DValue::OFF, Quality::BLOCKED};
    EXPECT_EQ(std::format("{}", dio), "DoublePointInformation{M_DP_NA_1: ioa=300 data=[0x11]}");
}

TEST_F(FormatterTest, DoublePointWithCP24Time2aFormat)
{
    DoublePointWithCP24Time2a dio{IOA{300}, DValue::OFF, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", dio), "DoublePointWithCP24Time2a{M_DP_TA_1: ioa=300 data=[0x11, 0x00, 0x00, 0x00]}");
}


TEST_F(FormatterTest, StepPositionInformationFormat)
{
    StepPositionInformation sio{IOA{300}, 20, true, Quality::BLOCKED};
    EXPECT_EQ(std::format("{}", sio), "StepPositionInformation{M_ST_NA_1: ioa=300 data=[0x94, 0x10]}");
}

TEST_F(FormatterTest, StepPositionWithCP24Time2aFormat)
{
    StepPositionWithCP24Time2a sio{IOA{300}, 20, true, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", sio), "StepPositionWithCP24Time2a{M_ST_TA_1: ioa=300 data=[0x94, 0x10, 0x00, 0x00, 0x00]}");
}

TEST_F(FormatterTest, BitString32Format)
{
    BitString32 io{IOA{300}, 0x11223344, Quality::BLOCKED};
    EXPECT_EQ(std::format("{}", io), "BitString32{M_BO_NA_1: ioa=300 data=[0x44, 0x33, 0x22, 0x11, 0x10]}");
}

TEST_F(FormatterTest, BitString32WithCP24Time2aFormat)
{
    BitString32WithCP24Time2a io{IOA{300}, 0x11223344, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", io), "BitString32WithCP24Time2a{M_BO_TA_1: ioa=300 data=[0x44, 0x33, 0x22, 0x11, 0x10, 0x00, 0x00, 0x00]}");
}

TEST_F(FormatterTest, MeasuredValueNormalizedFormat)
{
    MeasuredValueNormalized io{IOA{300}, 0.5, Quality::BLOCKED};
    EXPECT_EQ(std::format("{}", io), "MeasuredValueNormalized{M_ME_NA_1: ioa=300 data=[0x00, 0x40, 0x10]}");
}

TEST_F(FormatterTest, MeasuredValueNormalizedWithCP24Time2aFormat)
{
    MeasuredValueNormalizedWithCP24Time2a sio{IOA{300}, 0.5, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", sio), "MeasuredValueNormalizedWithCP24Time2a{M_ME_TA_1: ioa=300 data=[0x00, 0x40, 0x10, 0x00, 0x00, 0x00]}");
}

TEST_F(FormatterTest, MeasuredValueScaledFormat)
{
    MeasuredValueScaled io{IOA{300}, 12799, Quality::BLOCKED};
    EXPECT_EQ(std::format("{}", io), "MeasuredValueScaled{M_ME_NB_1: ioa=300 data=[0xff, 0x31, 0x10]}");
}

TEST_F(FormatterTest, MeasuredValueScaledWithCP24Time2aFormat)
{
    MeasuredValueScaledWithCP24Time2a io{IOA{300}, 12799, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", io), "MeasuredValueScaledWithCP24Time2a{M_ME_TB_1: ioa=300 data=[0xff, 0x31, 0x10, 0x00, 0x00, 0x00]}");
}

TEST_F(FormatterTest, MeasuredValueShortFormat)
{
    MeasuredValueShort io{IOA{300}, 1.3, Quality::BLOCKED};
    EXPECT_EQ(std::format("{}", io), "MeasuredValueShort{M_ME_NC_1: ioa=300 data=[0x66, 0x66, 0xa6, 0x3f, 0x10]}");
}

TEST_F(FormatterTest, MeasuredValueShortWithCP24Time2aFormat)
{
    MeasuredValueShortWithCP24Time2a io{IOA{300}, 1.3, Quality::BLOCKED, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", io), "MeasuredValueShortWithCP24Time2a{M_ME_TC_1: ioa=300 data=[0x66, 0x66, 0xa6, 0x3f, 0x10, 0x00, 0x00, 0x00]}");
}

TEST_F(FormatterTest, IntegratedTotalsFormat)
{
    const BinaryCounterReading bcr{12, 100, true, true, true};
    IntegratedTotals io{IOA{300}, bcr};
    EXPECT_EQ(std::format("{}", io), "IntegratedTotals{M_IT_NA_1: ioa=300 data=[0x0c, 0x00, 0x00, 0x00, 0xe4]}");
}

TEST_F(FormatterTest, IntegratedTotalsWithCP24Time2aFormat)
{
    const BinaryCounterReading bcr{12, 100, true, true, true};
    IntegratedTotalsWithCP24Time2a io{IOA{300}, bcr, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", io), "IntegratedTotalsWithCP24Time2a{M_IT_TA_1: ioa=300 data=[0x0c, 0x00, 0x00, 0x00, 0xe4, 0x00, 0x00, 0x00]}");
}

TEST_F(FormatterTest, EventOfProtectionEquipmentFormat)
{
    const SingleEvent event{EventState::ON, QualityP::ELAPSED_TIME_INVALID};
    EventOfProtectionEquipment io{IOA{300}, event, CP16Time2a{12500}, CP24Time2a{}};
    EXPECT_EQ(std::format("{}", io), "EventOfProtectionEquipment{M_EP_TA_1: ioa=300 data=[0x0a, 0xd4, 0x30, 0x00, 0x00, 0x00]}");
}
