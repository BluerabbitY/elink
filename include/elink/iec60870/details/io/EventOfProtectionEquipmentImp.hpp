/***********************************************************************************
 * \file EventOfProtectionEquipmentImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-03 21:33:26
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

#include "elink/iec60870/details/io/InformationObjectSerializable.hpp"
#include "elink/iec60870/SingleEvent.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class EventOfProtectionEquipmentImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    EventOfProtectionEquipmentImp()
    : eventM{EventState::OFF}, elapsedTimeM{0}
    {
    }

    EventOfProtectionEquipmentImp(const IOA ioa, const SingleEvent event, const CP16Time2a elapsedTime)
    : InformationObjectSerializable<inherit, typeID>{ioa}, eventM{event}, elapsedTimeM{elapsedTime}
    {
    }

    ~EventOfProtectionEquipmentImp() = default;

    [[nodiscard]] const SingleEvent& getEvent() const
    {
        return eventM;
    }

    void setEvent(const SingleEvent event)
    {
        eventM = event;
    }

    [[nodiscard]] const CP16Time2a& getElapsedTime() const
    {
        return elapsedTimeM;
    }

    void setElapsedTime(const CP16Time2a elapsedTime)
    {
        elapsedTimeM = elapsedTime;
    }

protected:
    SingleEvent eventM;
    CP16Time2a elapsedTimeM;
};

}
