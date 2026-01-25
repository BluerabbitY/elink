/***********************************************************************************
 * \file InformationObjectFormatter.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 00:16:16
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

#include "elink/iec60870/details/InformationObjectSerializable.hpp"
#include "elink/iec60870/codec/OStream.hpp"
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

        if (it != end && *it == 'b')
        {
            intuitive = false;
            ++it;
        }

        std::size_t value = 0;
        bool hasDigits = false;

        while (it != end && *it >= '0' && *it <= '9') {
            hasDigits = true;
            value = value * 10 + (*it - '0');
            ++it;
        }

        if (hasDigits)
            maxLen = value;

        if (it != end && (*it == 'x' || *it == 'X'))
        {
            upper = (*it == 'X');
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
        elink::iec60870::internal::OStream ostream{buffer.get(), io.size()};
        io.serialize(ostream, false);

        std::format_to(out, "{}", elink::util::type_name<inherit>());
        *out++ = '{';

        std::format_to(out, "{}", io.getTypeID());

        if (intuitive)
        {
            std::format_to(out, R"(: ioa={} raw=[)", io.getInformationObjectAddress());
        }
        else
        {
            std::format_to(out, R"(: raw=[)");
        }

        for (std::size_t i = intuitive ? io.getInformationObjectAddress().getLengthOfInformationObjectAddress() : 0; i < io.size(); ++i)
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

}
