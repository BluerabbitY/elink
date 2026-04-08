/***********************************************************************************
 * \file InformationObjectFormatter.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 00:16:16
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "elink/iec60870/details/io/InformationObjectSerializable.hpp"
#include "elink/iec60870/details/codec/OStream.hpp"
#include "elink/util/TypeName.hpp"

namespace std
{

template <typename inherit, elink::iec60870::TypeID typeID>
struct formatter<elink::iec60870::details::InformationObjectSerializable<inherit, typeID>> : formatter<std::string_view>
{
    using IO = elink::iec60870::details::InformationObjectSerializable<inherit, typeID>;

    bool intuitive = false;
    std::size_t maxLen = 256;
    bool upper = false;

    constexpr auto parse(std::format_parse_context& ctx)
    {
        auto it = ctx.begin();
        const auto end = ctx.end();

        intuitive = true;
        maxLen = 256;
        upper = false;

        std::size_t value = 0;
        bool hasDigits = false;

        while (it != end && *it >= '0' && *it <= '9') {
            hasDigits = true;
            value = value * 10 + (*it - '0');
            ++it;
        }

        if (hasDigits)
            maxLen = value;

        if (it != end && *it == 'b')
        {
            intuitive = false;
            ++it;
        }
        else if (it != end && *it == 'B')
        {
            intuitive = false;
            upper = true;
            ++it;
        }

        if (it == end || *it != '}')
        {
            return end;
        }

        return it;
    }

    template <class FormatContext>
    auto format(const IO& io, FormatContext& ctx) const
    {
        auto out = ctx.out();

        auto maxOutputElement = std::min(io.size(), maxLen);
        const std::unique_ptr<uint8_t[]> buffer{new uint8_t[io.size()]};
        elink::iec60870::details::OStream ostream{buffer.get(), io.size()};
        io.serialize(ostream, false);

        std::format_to(out, "{}", elink::util::type_name<inherit>());
        *out++ = '{';

        std::format_to(out, "{}", io.getTypeID());

        if (intuitive)
        {
            std::format_to(out, R"(: ioa={} data=[)", io.getInformationObjectAddress());
        }
        else
        {
            std::format_to(out, R"(: raw=[)");
        }

        for (std::size_t i = intuitive ? io.getInformationObjectAddress().length() : 0; i < io.size(); ++i)
        {
            if (i < maxOutputElement)
            {
                if (upper)
                {
                    std::format_to(out, "0x{:02X}", buffer[i]);
                }
                else
                {
                    std::format_to(out, "0x{:02x}", buffer[i]);
                }

            }
            else
            {
                std::format_to(out, "...");
                break;
            }

            if (i < maxOutputElement - 1)
                std::format_to(out, ", ");
        }

        *out++ = ']';
        *out++ = '}';

        return out;
    }
};

}

#include "elink/iec60870/io/SinglePointInformation.hpp"
#include "elink/iec60870/io/SinglePointWithCP24Time2a.hpp"
#include "elink/iec60870/io/DoublePointInformation.hpp"
#include "elink/iec60870/io/DoublePointWithCP24Time2a.hpp"
#include "elink/iec60870/io/StepPositionInformation.hpp"
#include "elink/iec60870/io/StepPositionWithCP24Time2a.hpp"
#include "elink/iec60870/io/BitString32.hpp"
#include "elink/iec60870/io/BitString32WithCP24Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueNormalized.hpp"
#include "elink/iec60870/io/MeasuredValueNormalizedWithCP24Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueScaled.hpp"
#include "elink/iec60870/io/MeasuredValueScaledWithCP24Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueShort.hpp"
#include "elink/iec60870/io/MeasuredValueShortWithCP24Time2a.hpp"
#include "elink/iec60870/io/IntegratedTotals.hpp"
#include "elink/iec60870/io/IntegratedTotalsWithCP24Time2a.hpp"
#include "elink/iec60870/io/EventOfProtectionEquipment.hpp"
#include "elink/iec60870/io/PackedStartEventsOfProtectionEquipment.hpp"
#include "elink/iec60870/io/PackedOutputCircuitInfo.hpp"
#include "elink/iec60870/io/PackedSinglePointWithSCD.hpp"
#include "elink/iec60870/io/MeasuredValueNormalizedWithoutQuality.hpp"
#include "elink/iec60870/io/SinglePointWithCP56Time2a.hpp"
#include "elink/iec60870/io/DoublePointWithCP56Time2a.hpp"
#include "elink/iec60870/io/StepPositionWithCP56Time2a.hpp"
#include "elink/iec60870/io/BitString32WithCP56Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueNormalizedWithCP56Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueScaledWithCP56Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueShortWithCP56Time2a.hpp"
#include "elink/iec60870/io/IntegratedTotalsWithCP56Time2a.hpp"
#include "elink/iec60870/io/EventOfProtectionEquipmentWithCP56Time2a.hpp"
#include "elink/iec60870/io/PackedStartEventsOfProtectionEquipmentWithCP56Time2a.hpp"
#include "elink/iec60870/io/PackedOutputCircuitInfoWithCP56Time2a.hpp"
#include "elink/iec60870/io/SingleCommand.hpp"
#include "elink/iec60870/io/DoubleCommand.hpp"
#include "elink/iec60870/io/StepCommand.hpp"
#include "elink/iec60870/io/SetpointCommandNormalized.hpp"
#include "elink/iec60870/io/SetpointCommandScaled.hpp"
#include "elink/iec60870/io/SetpointCommandShort.hpp"

namespace std {

template <>
struct formatter<elink::iec60870::SinglePointInformation>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::SinglePointInformation, elink::iec60870::TypeID::M_SP_NA_1>> {
};

template <>
struct formatter<elink::iec60870::SinglePointWithCP24Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::SinglePointWithCP24Time2a, elink::iec60870::TypeID::M_SP_TA_1>> {
};

template <>
struct formatter<elink::iec60870::DoublePointInformation>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::DoublePointInformation, elink::iec60870::TypeID::M_DP_NA_1>> {
};

template <>
struct formatter<elink::iec60870::DoublePointWithCP24Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::DoublePointWithCP24Time2a, elink::iec60870::TypeID::M_DP_TA_1>> {
};

template <>
struct formatter<elink::iec60870::StepPositionInformation>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::StepPositionInformation, elink::iec60870::TypeID::M_ST_NA_1>> {
};

template <>
struct formatter<elink::iec60870::StepPositionWithCP24Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::StepPositionWithCP24Time2a, elink::iec60870::TypeID::M_ST_TA_1>> {
};

template <>
struct formatter<elink::iec60870::BitString32>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::BitString32, elink::iec60870::TypeID::M_BO_NA_1>> {
};

template <>
struct formatter<elink::iec60870::BitString32WithCP24Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::BitString32WithCP24Time2a, elink::iec60870::TypeID::M_BO_TA_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueNormalized>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueNormalized, elink::iec60870::TypeID::M_ME_NA_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueNormalizedWithCP24Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueNormalizedWithCP24Time2a, elink::iec60870::TypeID::M_ME_TA_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueScaled>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueScaled, elink::iec60870::TypeID::M_ME_NB_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueScaledWithCP24Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueScaledWithCP24Time2a, elink::iec60870::TypeID::M_ME_TB_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueShort>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueShort, elink::iec60870::TypeID::M_ME_NC_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueShortWithCP24Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueShortWithCP24Time2a, elink::iec60870::TypeID::M_ME_TC_1>> {
};

template <>
struct formatter<elink::iec60870::IntegratedTotals>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::IntegratedTotals, elink::iec60870::TypeID::M_IT_NA_1>> {
};

template <>
struct formatter<elink::iec60870::IntegratedTotalsWithCP24Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::IntegratedTotalsWithCP24Time2a, elink::iec60870::TypeID::M_IT_TA_1>> {
};

template <>
struct formatter<elink::iec60870::EventOfProtectionEquipment>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::EventOfProtectionEquipment, elink::iec60870::TypeID::M_EP_TA_1>> {
};

template <>
struct formatter<elink::iec60870::PackedStartEventsOfProtectionEquipment>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::PackedStartEventsOfProtectionEquipment, elink::iec60870::TypeID::M_EP_TB_1>> {
};

template <>
struct formatter<elink::iec60870::PackedOutputCircuitInfo>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::PackedOutputCircuitInfo, elink::iec60870::TypeID::M_EP_TC_1>> {
};

template <>
struct formatter<elink::iec60870::PackedSinglePointWithSCD>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::PackedSinglePointWithSCD, elink::iec60870::TypeID::M_PS_NA_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueNormalizedWithoutQuality>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueNormalizedWithoutQuality, elink::iec60870::TypeID::M_ME_ND_1>> {
};

template <>
struct formatter<elink::iec60870::SinglePointWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::SinglePointWithCP56Time2a, elink::iec60870::TypeID::M_SP_TB_1>> {
};

template <>
struct formatter<elink::iec60870::DoublePointWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::DoublePointWithCP56Time2a, elink::iec60870::TypeID::M_DP_TB_1>> {
};

template <>
struct formatter<elink::iec60870::StepPositionWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::StepPositionWithCP56Time2a, elink::iec60870::TypeID::M_ST_TB_1>> {
};

template <>
struct formatter<elink::iec60870::BitString32WithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::BitString32WithCP56Time2a, elink::iec60870::TypeID::M_BO_TB_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueNormalizedWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueNormalizedWithCP56Time2a, elink::iec60870::TypeID::M_ME_TD_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueScaledWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueScaledWithCP56Time2a, elink::iec60870::TypeID::M_ME_TE_1>> {
};

template <>
struct formatter<elink::iec60870::MeasuredValueShortWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::MeasuredValueShortWithCP56Time2a, elink::iec60870::TypeID::M_ME_TF_1>> {
};

template <>
struct formatter<elink::iec60870::IntegratedTotalsWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::IntegratedTotalsWithCP56Time2a, elink::iec60870::TypeID::M_IT_TB_1>> {
};

template <>
struct formatter<elink::iec60870::EventOfProtectionEquipmentWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::EventOfProtectionEquipmentWithCP56Time2a, elink::iec60870::TypeID::M_EP_TD_1>> {
};

template <>
struct formatter<elink::iec60870::PackedStartEventsOfProtectionEquipmentWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::PackedStartEventsOfProtectionEquipmentWithCP56Time2a, elink::iec60870::TypeID::M_EP_TE_1>> {
};

template <>
struct formatter<elink::iec60870::PackedOutputCircuitInfoWithCP56Time2a>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::PackedOutputCircuitInfoWithCP56Time2a, elink::iec60870::TypeID::M_EP_TF_1>> {
};

template <>
struct formatter<elink::iec60870::SingleCommand>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::SingleCommand, elink::iec60870::TypeID::C_SC_NA_1>> {
};

template <>
struct formatter<elink::iec60870::DoubleCommand>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::DoubleCommand, elink::iec60870::TypeID::C_DC_NA_1>> {
};

template <>
struct formatter<elink::iec60870::StepCommand>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::StepCommand, elink::iec60870::TypeID::C_RC_NA_1>> {
};

template <>
struct formatter<elink::iec60870::SetpointCommandNormalized>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::SetpointCommandNormalized, elink::iec60870::TypeID::C_SE_NA_1>> {
};

template <>
struct formatter<elink::iec60870::SetpointCommandScaled>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::SetpointCommandScaled, elink::iec60870::TypeID::C_SE_NB_1>> {
};

template <>
struct formatter<elink::iec60870::SetpointCommandShort>
    : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::SetpointCommandShort, elink::iec60870::TypeID::C_SE_NC_1>> {
};

}
