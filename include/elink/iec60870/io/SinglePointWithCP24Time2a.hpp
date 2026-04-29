/***********************************************************************************
 * \file SinglePointWithCP24Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief SinglePointWithCP24Time2a
 * \date 2025-12-22 23:25:04
 *
 * \copyright Copyright (C) 2025-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "elink/iec60870/details/io/SinglePointInformationImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870 {

class SinglePointWithCP24Time2a final : public details::SinglePointInformationImp<SinglePointWithCP24Time2a, TypeID::M_SP_TA_1>, public details::CPxxTime2aUtil<CP24Time2a>
{
public:
    SinglePointWithCP24Time2a() = default;

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    SinglePointWithCP24Time2a(const IOA ioa, const bool value, const Quality quality = Quality::GOOD, const CP24Time2a cp24time2a = CP24Time2a::now())
        : SinglePointInformationImp{ioa, value, quality}, CPxxTime2aUtil{cp24time2a}
    {
    }

    ~SinglePointWithCP24Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const SinglePointWithCP24Time2a& io)
    {
        return stream << io.siqM << io.cpxxtime2aM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, SinglePointWithCP24Time2a& io)
    {
        return stream >> io.siqM >> io.cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(siqM) + sizeof(cpxxtime2aM);
    }
};

}
