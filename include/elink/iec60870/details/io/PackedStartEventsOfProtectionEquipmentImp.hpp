/***********************************************************************************
 * \file PackedStartEventsOfProtectionEquipmentImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-04 23:06:11
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

#include "InformationObjectSerializable.hpp"
#include "elink/iec60870/io/QualityDescriptorP.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"

namespace elink::iec60870
{

// clang-format off
/**
 * \brief SPE - Start events of protection equipment according to IEC 60870-5-101:2003 7.2.6.11
 */
enum class StartEvent : uint8_t
{
    NONE = 0x00,
    GS   = 0x01, /* General start of operation */
    SL1  = 0x02, /* Start of operation phase L1 */
    SL2  = 0x04, /* Start of operation phase L2 */
    SL3  = 0x08, /* Start of operation phase L3 */
    SIE  = 0x10, /* Start of operation IE (earth current) */
    SRD  = 0x20, /* Start of operation in reverse direction */
};
// clang-format on

namespace details {
template <typename inherit, TypeID typeID>
class PackedStartEventsOfProtectionEquipmentImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    PackedStartEventsOfProtectionEquipmentImp()
    : eventM{StartEvent::NONE}, qdpM{QualityP::GOOD}, elapsedTimeM{0}
    {
    }

    PackedStartEventsOfProtectionEquipmentImp(const IOA ioa,
                                              const StartEvent event,
                                              const QualityP qdp,
                                              const CP16Time2a elapsedTime)
    : InformationObjectSerializable<inherit, typeID>{ioa}, eventM{event}, qdpM{qdp}, elapsedTimeM{elapsedTime}
    {
    }

    ~PackedStartEventsOfProtectionEquipmentImp() = default;

    [[nodiscard]] StartEvent getEvent() const
    {
        return eventM;
    }

    void setEvent(const StartEvent event)
    {
        eventM = event;
    }

    [[nodiscard]] QualityP getQuality() const
    {
        return qdpM;
    }

    void setQuality(const QualityP quality)
    {
        qdpM = quality;
    }

    [[nodiscard]] const CP16Time2a& getElapsedTime() const
    {
        return elapsedTimeM;
    }

    void setElapsedTime(const CP16Time2a cp16time2a)
    {
        elapsedTimeM = cp16time2a;
    }

protected:
    StartEvent eventM;
    QualityP qdpM;
    CP16Time2a elapsedTimeM;
};

}
}
