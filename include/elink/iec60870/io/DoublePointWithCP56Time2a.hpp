/***********************************************************************************
 * \file DoublePointWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-12 20:56:14
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

#include "elink/iec60870/details/io/DoublePointInformationImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870 {

class DoublePointWithCP56Time2a final : public details::DoublePointInformationImp<DoublePointWithCP56Time2a, TypeID::M_DP_TB_1>, public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    DoublePointWithCP56Time2a() = default;

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    DoublePointWithCP56Time2a(const IOA ioa, const DValue value, const Quality quality = Quality::GOOD, const CP56Time2a cp56time2a = CP56Time2a::now())
        : DoublePointInformationImp{ioa, value, quality}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~DoublePointWithCP56Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << diqM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> diqM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(diqM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
