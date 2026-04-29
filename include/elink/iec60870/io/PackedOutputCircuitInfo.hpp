/***********************************************************************************
 * \file PackedOutputCircuitInfo.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-07 20:22:21
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

#include "elink/iec60870/details/io/PackedOutputCircuitInfoImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class PackedOutputCircuitInfo final
: public details::PackedOutputCircuitInfoImp<PackedOutputCircuitInfo, TypeID::M_EP_TC_1>,
  public details::CPxxTime2aUtil<CP24Time2a>
{
public:
    PackedOutputCircuitInfo() = default;

    PackedOutputCircuitInfo(const IOA ioa,
                            const OutputCircuitInfo oci,
                            const QualityP qdp,
                            const CP16Time2a operatingTime,
                            const CP24Time2a cp24time2a = CP24Time2a::now())
    : PackedOutputCircuitInfoImp{ioa, oci, qdp, operatingTime}, CPxxTime2aUtil{cp24time2a}
    {
    }

    ~PackedOutputCircuitInfo() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const PackedOutputCircuitInfo& io)
    {
        return stream << io.ociM << io.qdpM << io.operatingTimeM << io.cpxxtime2aM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, PackedOutputCircuitInfo& io)
    {
        return stream >> io.ociM >> io.qdpM >> io.operatingTimeM >> io.cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(ociM) + sizeof(qdpM) + sizeof(operatingTimeM) + sizeof(cpxxtime2aM);
    }
};

}
