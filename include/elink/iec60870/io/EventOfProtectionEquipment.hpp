/***********************************************************************************
 * \file EventOfProtectionEquipment.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-03 23:18:16
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

#include "elink/iec60870/details/io/EventOfProtectionEquipmentImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class EventOfProtectionEquipment final
: public details::EventOfProtectionEquipmentImp<EventOfProtectionEquipment, TypeID::M_EP_TA_1>,
  public details::CPxxTime2aUtil<CP24Time2a>
{
public:
    EventOfProtectionEquipment() = default;

    EventOfProtectionEquipment(const IOA ioa,
                               const SingleEvent event,
                               const CP16Time2a elapsedTime,
                               const CP24Time2a cp24time2a = CP24Time2a::now())
    : EventOfProtectionEquipmentImp{ioa, event, elapsedTime}, CPxxTime2aUtil{cp24time2a}
    {
    }

    ~EventOfProtectionEquipment() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const EventOfProtectionEquipment& io)
    {
        return stream << io.eventM.valueM << io.elapsedTimeM << io.cpxxtime2aM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, EventOfProtectionEquipment& io)
    {
        return stream >> io.eventM.valueM >> io.elapsedTimeM >> io.cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return eventM.size() + sizeof(elapsedTimeM) + sizeof(cpxxtime2aM);
    }
};

}
