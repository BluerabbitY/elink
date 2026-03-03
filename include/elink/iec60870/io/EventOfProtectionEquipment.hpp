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

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << eventM.valueM << elapsedTimeM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> eventM.valueM >> elapsedTimeM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return eventM.size() + details::getCPxxTime2aLength(elapsedTimeM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
