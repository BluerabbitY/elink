/***********************************************************************************
 * \file SinglePointWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-12 20:06:06
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

#include "elink/iec60870/details/io/SinglePointInformationImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870 {

class SinglePointWithCP56Time2a final : public details::SinglePointInformationImp<SinglePointWithCP56Time2a, TypeID::M_SP_TB_1>, public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    SinglePointWithCP56Time2a() = default;

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    SinglePointWithCP56Time2a(const IOA ioa, const bool value, const Quality quality = Quality::GOOD, const CP56Time2a cp56time2a = CP56Time2a::now())
        : SinglePointInformationImp{ioa, value, quality}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~SinglePointWithCP56Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OSream>
    void serialize(OSream& stream) const
    {
        stream << siqM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> siqM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(siqM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
