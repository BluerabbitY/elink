/***********************************************************************************
 * \file InformationObjectTypeIDFormatter.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 23:18:15
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#include "elink/iec60870/io/InformationObjectTypeID.h"

#include <format>

namespace std
{

template <>
struct formatter<elink::iec60870::TypeID> : formatter<std::string_view> {
    using formatter<std::string_view>::parse;

    template <class FormatContext>
    auto format(const elink::iec60870::TypeID& typeID, FormatContext& ctx) const
    {
        using elink::iec60870::TypeID;
        std::string_view typeIDStringView;
        // clang-format off
        switch (typeID)
        {
            case TypeID::M_SP_NA_1: typeIDStringView = "M_SP_NA_1";break;
            case TypeID::M_SP_TA_1: typeIDStringView = "M_SP_TA_1";break;
            case TypeID::M_DP_NA_1: typeIDStringView = "M_DP_NA_1";break;
            case TypeID::M_DP_TA_1: typeIDStringView = "M_DP_TA_1";break;
            case TypeID::M_ST_NA_1: typeIDStringView = "M_ST_NA_1";break;
            case TypeID::M_ST_TA_1: typeIDStringView = "M_ST_TA_1";break;
            case TypeID::M_BO_NA_1: typeIDStringView = "M_BO_NA_1";break;
            case TypeID::M_BO_TA_1: typeIDStringView = "M_BO_TA_1";break;
            case TypeID::M_ME_NA_1: typeIDStringView = "M_ME_NA_1";break;
            case TypeID::M_ME_TA_1: typeIDStringView = "M_ME_TA_1";break;
            case TypeID::M_ME_NB_1: typeIDStringView = "M_ME_NB_1";break;
            case TypeID::M_ME_TB_1: typeIDStringView = "M_ME_TB_1";break;
            case TypeID::M_ME_NC_1: typeIDStringView = "M_ME_NC_1";break;
            case TypeID::M_ME_TC_1: typeIDStringView = "M_ME_TC_1";break;
            case TypeID::M_IT_NA_1: typeIDStringView = "M_IT_NA_1";break;
            case TypeID::M_IT_TA_1: typeIDStringView = "M_IT_TA_1";break;
            case TypeID::M_EP_TA_1: typeIDStringView = "M_EP_TA_1";break;
            case TypeID::M_EP_TB_1: typeIDStringView = "M_EP_TB_1";break;
            case TypeID::M_EP_TC_1: typeIDStringView = "M_EP_TC_1";break;
            case TypeID::M_PS_NA_1: typeIDStringView = "M_PS_NA_1";break;
            case TypeID::M_ME_ND_1: typeIDStringView = "M_ME_ND_1";break;
            case TypeID::M_SP_TB_1: typeIDStringView = "M_SP_TB_1";break;
            case TypeID::M_DP_TB_1: typeIDStringView = "M_DP_TB_1";break;
            case TypeID::M_ST_TB_1: typeIDStringView = "M_ST_TB_1";break;
            case TypeID::M_BO_TB_1: typeIDStringView = "M_BO_TB_1";break;
            case TypeID::M_ME_TD_1: typeIDStringView = "M_ME_TD_1";break;
            case TypeID::M_ME_TE_1: typeIDStringView = "M_ME_TE_1";break;
            case TypeID::M_ME_TF_1: typeIDStringView = "M_ME_TF_1";break;
            case TypeID::M_IT_TB_1: typeIDStringView = "M_IT_TB_1";break;
            case TypeID::M_EP_TD_1: typeIDStringView = "M_EP_TD_1";break;
            case TypeID::M_EP_TE_1: typeIDStringView = "M_EP_TE_1";break;
            case TypeID::M_EP_TF_1: typeIDStringView = "M_EP_TF_1";break;
            case TypeID::C_SC_NA_1: typeIDStringView = "C_SC_NA_1";break;
            case TypeID::C_DC_NA_1: typeIDStringView = "C_DC_NA_1";break;
            case TypeID::C_RC_NA_1: typeIDStringView = "C_RC_NA_1";break;
            case TypeID::C_SE_NA_1: typeIDStringView = "C_SE_NA_1";break;
            case TypeID::C_SE_NB_1: typeIDStringView = "C_SE_NB_1";break;
            case TypeID::C_SE_NC_1: typeIDStringView = "C_SE_NC_1";break;
            case TypeID::C_BO_NA_1: typeIDStringView = "C_BO_NA_1";break;
            case TypeID::C_SC_TA_1: typeIDStringView = "C_SC_TA_1";break;
            case TypeID::C_DC_TA_1: typeIDStringView = "C_DC_TA_1";break;
            case TypeID::C_RC_TA_1: typeIDStringView = "C_RC_TA_1";break;
            case TypeID::C_SE_TA_1: typeIDStringView = "C_SE_TA_1";break;
            case TypeID::C_SE_TB_1: typeIDStringView = "C_SE_TB_1";break;
            case TypeID::C_SE_TC_1: typeIDStringView = "C_SE_TC_1";break;
            case TypeID::C_BO_TA_1: typeIDStringView = "C_BO_TA_1";break;
            case TypeID::M_EI_NA_1: typeIDStringView = "M_EI_NA_1";break;
            case TypeID::C_IC_NA_1: typeIDStringView = "C_IC_NA_1";break;
            case TypeID::C_CI_NA_1: typeIDStringView = "C_CI_NA_1";break;
            case TypeID::C_RD_NA_1: typeIDStringView = "C_RD_NA_1";break;
            case TypeID::C_CS_NA_1: typeIDStringView = "C_CS_NA_1";break;
            case TypeID::C_TS_NA_1: typeIDStringView = "C_TS_NA_1";break;
            case TypeID::C_RP_NA_1: typeIDStringView = "C_RP_NA_1";break;
            case TypeID::C_CD_NA_1: typeIDStringView = "C_CD_NA_1";break;
            case TypeID::C_TS_TA_1: typeIDStringView = "C_TS_TA_1";break;
            case TypeID::P_ME_NA_1: typeIDStringView = "P_ME_NA_1";break;
            case TypeID::P_ME_NB_1: typeIDStringView = "P_ME_NB_1";break;
            case TypeID::P_ME_NC_1: typeIDStringView = "P_ME_NC_1";break;
            case TypeID::P_AC_NA_1: typeIDStringView = "P_AC_NA_1";break;
            case TypeID::F_FR_NA_1: typeIDStringView = "F_FR_NA_1";break;
            case TypeID::F_SR_NA_1: typeIDStringView = "F_SR_NA_1";break;
            case TypeID::F_SC_NA_1: typeIDStringView = "F_SC_NA_1";break;
            case TypeID::F_LS_NA_1: typeIDStringView = "F_LS_NA_1";break;
            case TypeID::F_AF_NA_1: typeIDStringView = "F_AF_NA_1";break;
            case TypeID::F_SG_NA_1: typeIDStringView = "F_SG_NA_1";break;
            case TypeID::F_DR_TA_1: typeIDStringView = "F_DR_TA_1";break;
            case TypeID::F_SC_NB_1: typeIDStringView = "F_SC_NB_1";break;
            default: typeIDStringView = "unknown";
        }
        // clang-format on
        return formatter<std::string_view>::format(typeIDStringView, ctx);
    }
};

}
