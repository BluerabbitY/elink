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
#include "elink/iec60870/io/BitString32Command.hpp"
#include "elink/iec60870/io/SingleCommandWithCP56Time2a.hpp"
#include "elink/iec60870/io/DoubleCommandWithCP56Time2a.hpp"
#include "elink/iec60870/io/StepCommandWithCP56Time2a.hpp"
#include "elink/iec60870/io/SetpointCommandNormalizedWithCP56Time2a.hpp"
#include "elink/iec60870/io/SetpointCommandScaledWithCP56Time2a.hpp"

namespace std {

#define ELINK_IO_FORMATTER(ioType)                                                                                  \
    template <>                                                                                                     \
    struct formatter<elink::iec60870::ioType>                                                                       \
        : formatter<elink::iec60870::details::InformationObjectSerializable<elink::iec60870::ioType,                \
                                                                             elink::iec60870::ioType::IDENT_T>> {}

ELINK_IO_FORMATTER(SinglePointInformation);
ELINK_IO_FORMATTER(SinglePointWithCP24Time2a);
ELINK_IO_FORMATTER(DoublePointInformation);
ELINK_IO_FORMATTER(DoublePointWithCP24Time2a);
ELINK_IO_FORMATTER(StepPositionInformation);
ELINK_IO_FORMATTER(StepPositionWithCP24Time2a);
ELINK_IO_FORMATTER(BitString32);
ELINK_IO_FORMATTER(BitString32WithCP24Time2a);
ELINK_IO_FORMATTER(MeasuredValueNormalized);
ELINK_IO_FORMATTER(MeasuredValueNormalizedWithCP24Time2a);
ELINK_IO_FORMATTER(MeasuredValueScaled);
ELINK_IO_FORMATTER(MeasuredValueScaledWithCP24Time2a);
ELINK_IO_FORMATTER(MeasuredValueShort);
ELINK_IO_FORMATTER(MeasuredValueShortWithCP24Time2a);
ELINK_IO_FORMATTER(IntegratedTotals);
ELINK_IO_FORMATTER(IntegratedTotalsWithCP24Time2a);
ELINK_IO_FORMATTER(EventOfProtectionEquipment);
ELINK_IO_FORMATTER(PackedStartEventsOfProtectionEquipment);
ELINK_IO_FORMATTER(PackedOutputCircuitInfo);
ELINK_IO_FORMATTER(PackedSinglePointWithSCD);
ELINK_IO_FORMATTER(MeasuredValueNormalizedWithoutQuality);
ELINK_IO_FORMATTER(SinglePointWithCP56Time2a);
ELINK_IO_FORMATTER(DoublePointWithCP56Time2a);
ELINK_IO_FORMATTER(StepPositionWithCP56Time2a);
ELINK_IO_FORMATTER(BitString32WithCP56Time2a);
ELINK_IO_FORMATTER(MeasuredValueNormalizedWithCP56Time2a);
ELINK_IO_FORMATTER(MeasuredValueScaledWithCP56Time2a);
ELINK_IO_FORMATTER(MeasuredValueShortWithCP56Time2a);
ELINK_IO_FORMATTER(IntegratedTotalsWithCP56Time2a);
ELINK_IO_FORMATTER(EventOfProtectionEquipmentWithCP56Time2a);
ELINK_IO_FORMATTER(PackedStartEventsOfProtectionEquipmentWithCP56Time2a);
ELINK_IO_FORMATTER(PackedOutputCircuitInfoWithCP56Time2a);
ELINK_IO_FORMATTER(SingleCommand);
ELINK_IO_FORMATTER(DoubleCommand);
ELINK_IO_FORMATTER(StepCommand);
ELINK_IO_FORMATTER(SetpointCommandNormalized);
ELINK_IO_FORMATTER(SetpointCommandScaled);
ELINK_IO_FORMATTER(SetpointCommandShort);
ELINK_IO_FORMATTER(BitString32Command);
ELINK_IO_FORMATTER(SingleCommandWithCP56Time2a);
ELINK_IO_FORMATTER(DoubleCommandWithCP56Time2a);
ELINK_IO_FORMATTER(StepCommandWithCP56Time2a);
ELINK_IO_FORMATTER(SetpointCommandNormalizedWithCP56Time2a);
ELINK_IO_FORMATTER(SetpointCommandScaledWithCP56Time2a);

#undef ELINK_DEFINE_IO_FORMATTER

}
