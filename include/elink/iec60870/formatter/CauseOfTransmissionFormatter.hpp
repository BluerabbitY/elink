/***********************************************************************************
 * \file CauseOfTransmissionFormatter.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-30 00:03:50
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

#include "elink/iec60870/CauseOfTransmission.hpp"

#include <format>

namespace std
{

template <>
struct formatter<elink::iec60870::COT> : formatter<std::string_view> {
    using formatter<std::string_view>::parse;

    template <class FormatContext>
    auto format(const elink::iec60870::COT& cot, FormatContext& ctx) const
    {
        using elink::iec60870::COT;
        std::string_view cotStringView;
        // clang-format off
        switch (cot)
        {
            case COT::PERIODIC: cotStringView = "PERIODIC"; break;
            case COT::BACKGROUND_SCAN: cotStringView = "BACKGROUND_SCAN"; break;
            case COT::SPONTANEOUS: cotStringView = "SPONTANEOUS"; break;
            case COT::INITIALIZED: cotStringView = "INITIALIZED"; break;
            case COT::REQUEST: cotStringView = "REQUEST"; break;
            case COT::ACTIVATION: cotStringView = "ACTIVATION"; break;
            case COT::ACTIVATION_CON: cotStringView = "ACTIVATION_CON"; break;
            case COT::DEACTIVATION: cotStringView = "DEACTIVATION"; break;
            case COT::DEACTIVATION_CON: cotStringView = "DEACTIVATION_CON"; break;
            case COT::ACTIVATION_TERMINATION: cotStringView = "ACTIVATION_TERMINATION"; break;
            case COT::RETURN_INFO_REMOTE: cotStringView = "RETURN_INFO_REMOTE"; break;
            case COT::RETURN_INFO_LOCAL: cotStringView = "RETURN_INFO_LOCAL"; break;
            case COT::FILE_TRANSFER: cotStringView = "FILE_TRANSFER"; break;
            case COT::AUTHENTICATION: cotStringView = "AUTHENTICATION"; break;
            case COT::MAINTENANCE_OF_AUTH_SESSION_KEY: cotStringView = "MAINTENANCE_OF_AUTH_SESSION_KEY"; break;
            case COT::MAINTENANCE_OF_USER_ROLE_AND_UPDATE_KEY: cotStringView = "MAINTENANCE_OF_USER_ROLE_AND_UPDATE_KEY"; break;
            case COT::INTERROGATED_BY_STATION: cotStringView = "INTERROGATED_BY_STATION"; break;
            case COT::INTERROGATED_BY_GROUP_1: cotStringView = "INTERROGATED_BY_GROUP_1"; break;
            case COT::INTERROGATED_BY_GROUP_2: cotStringView = "INTERROGATED_BY_GROUP_2"; break;
            case COT::INTERROGATED_BY_GROUP_3: cotStringView = "INTERROGATED_BY_GROUP_3"; break;
            case COT::INTERROGATED_BY_GROUP_4: cotStringView = "INTERROGATED_BY_GROUP_4"; break;
            case COT::INTERROGATED_BY_GROUP_5: cotStringView = "INTERROGATED_BY_GROUP_5"; break;
            case COT::INTERROGATED_BY_GROUP_6: cotStringView = "INTERROGATED_BY_GROUP_6"; break;
            case COT::INTERROGATED_BY_GROUP_7: cotStringView = "INTERROGATED_BY_GROUP_7"; break;
            case COT::INTERROGATED_BY_GROUP_8: cotStringView = "INTERROGATED_BY_GROUP_8"; break;
            case COT::INTERROGATED_BY_GROUP_9: cotStringView = "INTERROGATED_BY_GROUP_9"; break;
            case COT::INTERROGATED_BY_GROUP_10: cotStringView = "INTERROGATED_BY_GROUP_10"; break;
            case COT::INTERROGATED_BY_GROUP_11: cotStringView = "INTERROGATED_BY_GROUP_11"; break;
            case COT::INTERROGATED_BY_GROUP_12: cotStringView = "INTERROGATED_BY_GROUP_12"; break;
            case COT::INTERROGATED_BY_GROUP_13: cotStringView = "INTERROGATED_BY_GROUP_13"; break;
            case COT::INTERROGATED_BY_GROUP_14: cotStringView = "INTERROGATED_BY_GROUP_14"; break;
            case COT::INTERROGATED_BY_GROUP_15: cotStringView = "INTERROGATED_BY_GROUP_15"; break;
            case COT::INTERROGATED_BY_GROUP_16: cotStringView = "INTERROGATED_BY_GROUP_16"; break;
            case COT::REQUESTED_BY_GENERAL_COUNTER: cotStringView = "REQUESTED_BY_GENERAL_COUNTER"; break;
            case COT::REQUESTED_BY_GROUP_1_COUNTER: cotStringView = "REQUESTED_BY_GROUP_1_COUNTER"; break;
            case COT::REQUESTED_BY_GROUP_2_COUNTER: cotStringView = "REQUESTED_BY_GROUP_2_COUNTER"; break;
            case COT::REQUESTED_BY_GROUP_3_COUNTER: cotStringView = "REQUESTED_BY_GROUP_3_COUNTER"; break;
            case COT::REQUESTED_BY_GROUP_4_COUNTER: cotStringView = "REQUESTED_BY_GROUP_4_COUNTER"; break;
            case COT::UNKNOWN_TYPE_ID: cotStringView = "UNKNOWN_TYPE_ID"; break;
            case COT::UNKNOWN_COT: cotStringView = "UNKNOWN_CAUSE_OF_TRANSMISSION"; break;
            case COT::UNKNOWN_CA: cotStringView = "UNKNOWN_COMMON_ADDRESS_OF_ASDU"; break;
            case COT::UNKNOWN_IOA: cotStringView = "UNKNOWN_INFORMATION_OBJECT_ADDRESS"; break;
            default: cotStringView = "unknown";
        }
        // clang-format on
        return formatter<std::string_view>::format(cotStringView, ctx);
    }
};

}
