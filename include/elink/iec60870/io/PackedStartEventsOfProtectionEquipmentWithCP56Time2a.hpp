/***********************************************************************************
 * \file PackedStartEventsOfProtectionEquipmentWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 10:02:19
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

#include "elink/iec60870/details/io/PackedStartEventsOfProtectionEquipmentImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class PackedStartEventsOfProtectionEquipmentWithCP56Time2a final
: public details::PackedStartEventsOfProtectionEquipmentImp<PackedStartEventsOfProtectionEquipmentWithCP56Time2a, TypeID::M_EP_TE_1>,
  public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    PackedStartEventsOfProtectionEquipmentWithCP56Time2a() = default;

    PackedStartEventsOfProtectionEquipmentWithCP56Time2a(const IOA ioa,
                                           const StartEvent event,
                                           const QualityP qdp,
                                           const CP16Time2a elapsedTime,
                                           const CP56Time2a cp56time2a = CP56Time2a::now())
    : PackedStartEventsOfProtectionEquipmentImp{ioa, event, qdp, elapsedTime}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~PackedStartEventsOfProtectionEquipmentWithCP56Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << eventM << qdpM << elapsedTimeM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> eventM >> qdpM >> elapsedTimeM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(eventM) + sizeof(qdpM) + details::getCPxxTime2aLength(elapsedTimeM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
