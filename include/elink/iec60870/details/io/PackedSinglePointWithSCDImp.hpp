/***********************************************************************************
 * \file PackedSinglePointWithSCDImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-10 20:41:33
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

#include "elink/iec60870/details/io//InformationObjectSerializable.hpp"
#include "elink/iec60870/StatusAndStatusChangeDetection.hpp"
#include "elink/iec60870/io/QualityDescriptor.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class PackedSinglePointWithSCDImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    PackedSinglePointWithSCDImp()
    : scdM{0, 0}, qualityM{Quality::GOOD}
    {
    }

    PackedSinglePointWithSCDImp(const IOA ioa, const StatusAndStatusChangeDetection scd, const Quality quality)
    : InformationObjectSerializable<inherit, typeID>{ioa}, scdM{scd}, qualityM{quality}
    {
    }

    PackedSinglePointWithSCDImp(const IOA ioa, const uint16_t st, const uint16_t cd, const Quality quality)
    : InformationObjectSerializable<inherit, typeID>{ioa}, scdM{st, cd}, qualityM{quality}
    {
    }

    ~PackedSinglePointWithSCDImp() = default;

    [[nodiscard]] StatusAndStatusChangeDetection getSCD() const
    {
        return scdM;
    }

    void setSCD(const StatusAndStatusChangeDetection scd)
    {
        scdM = scd;
    }

    [[nodiscard]] Quality getQuality() const
    {
        return qualityM;
    }

    void setQuality(const Quality quality)
    {
        qualityM = quality;
    }

protected:
    StatusAndStatusChangeDetection scdM;
    Quality qualityM;
};

}
