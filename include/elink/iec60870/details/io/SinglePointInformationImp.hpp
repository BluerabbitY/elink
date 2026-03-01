/***********************************************************************************
 * \file SinglePointInformationImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-22 23:37:06
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
#include "elink/iec60870/io/QualityDescriptor.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class SinglePointInformationImp : public InformationObjectSerializable<inherit, typeID> {
public:
    SinglePointInformationImp()
        : siqM{0}
    {
    }

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    SinglePointInformationImp(const IOA ioa, const bool value, const Quality quality)
        : InformationObjectSerializable<inherit, typeID>{ioa}, siqM{0}
    {
        setValue(value);
        setQuality(quality);
    }

    ~SinglePointInformationImp() = default;

    [[nodiscard]] bool getValue() const
    {
        return siqM & 0x01;
    }

    void setValue(const bool value)
    {
        siqM = (siqM & 0xfe) | value;
    }

    [[nodiscard]] Quality getQuality() const
    {
        return static_cast<Quality>(siqM & 0xf0);
    }

    void setQuality(const Quality quality)
    {
        siqM = (siqM & 0x0f) | static_cast<uint8_t>(quality);
    }

protected:
    /** 4 bit quality + 1 bit bool */
    uint8_t siqM;
};

}
