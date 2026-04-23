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
#include "elink/iec60870/io/QualityDescriptorP.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"

namespace elink::iec60870
{

enum class EventState : uint8_t
{
    INDETERMINATE_0 = 0,
    OFF = 1,
    ON = 2,
    INDETERMINATE_3 = 3
};

class SingleEvent
{
public:
    SingleEvent()
    : valueM{}
    {
    }

    explicit SingleEvent(const EventState eventState, const QualityP qdp = QualityP::GOOD)
    : valueM{}
    {
        setEventState(eventState);
        setQDP(qdp);
    }

    ~SingleEvent() = default;

    SingleEvent(const SingleEvent&) = default;

    SingleEvent(SingleEvent&&) = default;

    SingleEvent& operator=(const SingleEvent&) = default;

    bool operator==(const SingleEvent other) const
    {
        return valueM == other.valueM;
    }

    bool operator!=(const SingleEvent other) const
    {
        return valueM != other.valueM;
    }

    void setEventState(EventState eventState)
    {
        valueM = (valueM & 0xfc) | (static_cast<uint8_t>(eventState) & 0x03);
    }

    [[nodiscard]] EventState getEventState() const
    {
        return static_cast<EventState>(valueM & 0x3);
    }

    void setQDP(QualityP qdp)
    {
        valueM = (valueM & 0x03) | (static_cast<uint8_t>(qdp) & 0xfc);
    }

    [[nodiscard]] QualityP getQDP() const
    {
        return static_cast<QualityP>(valueM & 0xfc);
    }

protected:
    friend class EventOfProtectionEquipment;
    friend class EventOfProtectionEquipmentWithCP56Time2a;

    [[nodiscard]] constexpr std::size_t size() const
    {
        return sizeof(valueM);
    }

private:
    uint8_t valueM;
};

namespace details
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
}
