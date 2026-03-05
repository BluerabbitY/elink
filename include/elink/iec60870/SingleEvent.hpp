/***********************************************************************************
 * \file SingleEvent.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-03 19:32:31
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

#include "elink/iec60870/io/QualityDescriptorP.hpp"

#include <cstdint>

namespace elink::iec60870
{

enum class EventState : uint8_t {
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

    [[nodiscard]] constexpr std::size_t size() const
    {
        return sizeof(valueM);
    }

private:
    uint8_t valueM;
};

}
