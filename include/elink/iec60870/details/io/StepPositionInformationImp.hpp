/***********************************************************************************
 * \file StepPositionInformationImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-23 00:12:48
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
#include "elink/iec60870/io/QualityDescriptor.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class StepPositionInformationImp : public InformationObjectSerializable<inherit, typeID> {
public:
    StepPositionInformationImp()
        : vtiM{0}, qualityM{static_cast<uint8_t>(Quality::GOOD)}
    {
    }

    // Valid Quality: GOOD, OVERFLOW, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    StepPositionInformationImp(const IOA ioa, const int value, const bool isTransient, const Quality quality)
        : InformationObjectSerializable<inherit, typeID>{ioa}, vtiM{0}, qualityM{static_cast<uint8_t>(quality)}
    {
        setValue(value);
        setTransient(isTransient);
    }

    ~StepPositionInformationImp() = default;

    [[nodiscard]] int getValue() const
    {
        int value = vtiM & 0x7f;

        if (value > upLimit)
            value -= offset;

        return value;
    }

    void setValue(const int value)
    {
        vtiM = std::clamp(value, lowLimit, upLimit);

        if (vtiM < 0)
            vtiM += offset;
    }

    [[nodiscard]] bool isTransient() const
    {
        return (vtiM & 0x80) == 0x80;
    }

    void setTransient(const bool isTransient)
    {
        isTransient ? vtiM |= 0x80 : vtiM &= 0x7f;
    }

    [[nodiscard]] Quality getQuality() const
    {
        return static_cast<Quality>(qualityM);
    }

    void setQuality(const Quality quality)
    {
        qualityM = static_cast<uint8_t>(quality) & 0xf1;
    }

protected:
    static constexpr int upLimit = 63;
    static constexpr int lowLimit = -64;
    static constexpr int offset = 128;

    uint8_t vtiM;
    uint8_t qualityM;
};

}
