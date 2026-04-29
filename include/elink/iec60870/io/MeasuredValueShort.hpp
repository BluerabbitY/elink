/***********************************************************************************
 * \file MeasuredValueShort.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-02 19:11:39
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

#include "elink/iec60870/details/io/MeasuredValueShortImp.hpp"

namespace elink::iec60870
{

class MeasuredValueShort final : public details::MeasuredValueShortImp<MeasuredValueShort, TypeID::M_ME_NC_1>
{
public:
    MeasuredValueShort() = default;

    MeasuredValueShort(const IOA ioa, const float value, const Quality quality = Quality::GOOD)
    : MeasuredValueShortImp{ioa, value, quality}
    {
    }

    ~MeasuredValueShort() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const MeasuredValueShort& io)
    {
        return stream << io.valueM << io.qualityM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, MeasuredValueShort& io)
    {
        return stream >> io.valueM >> io.qualityM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + sizeof(qualityM);
    }
};

}
