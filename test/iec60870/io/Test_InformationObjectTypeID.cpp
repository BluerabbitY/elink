/***********************************************************************************
 * \file Test_InformationObjectTypeID.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief test for information object type id
 * \date 2025-12-13 23:12:17
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

TEST(InformationObjectTypeID, Format)
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