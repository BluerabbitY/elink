/***********************************************************************************
 * \file PackedSinglePointWithSCD.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-10 22:57:39
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

#include "elink/iec60870/details/io/PackedSinglePointWithSCDImp.hpp"

namespace elink::iec60870
{

class PackedSinglePointWithSCD final : public details::PackedSinglePointWithSCDImp<PackedSinglePointWithSCD, TypeID::M_PS_NA_1>
{
public:
    PackedSinglePointWithSCD() = default;

    PackedSinglePointWithSCD(const IOA ioa, const StatusAndStatusChangeDetection scd, const Quality quality)
    : PackedSinglePointWithSCDImp{ioa, scd, quality}
    {
    }

    PackedSinglePointWithSCD(const IOA ioa, const uint16_t st, const uint16_t cd, const Quality quality)
    : PackedSinglePointWithSCDImp{ioa, st, cd, quality}
    {
    }

    ~PackedSinglePointWithSCD() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const PackedSinglePointWithSCD& io)
    {
        return stream << io.scdM.getST() << io.scdM.getCD() << io.qualityM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, PackedSinglePointWithSCD& io)
    {
        return stream >> io.scdM.stM >> io.scdM.cdM >> io.qualityM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return scdM.size() + sizeof(qualityM);
    }
};

}
