/***********************************************************************************
 * \file BitString32Imp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-25 18:42:48
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

#include "elink/iec60870/details/io/BitString32WithoutQualityImp.hpp"
#include "elink/iec60870/io/QualityDescriptor.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class BitString32Imp : public BitString32WithoutQualityImp<inherit, typeID>
{
public:
    BitString32Imp() : BitString32WithoutQualityImp<inherit, typeID>{}, qualityM{Quality::GOOD}
    {
    }

    BitString32Imp(const IOA ioa, const uint32_t value, const Quality quality)
     : BitString32WithoutQualityImp<inherit, typeID>{ioa, value}, qualityM{quality}
    {
    }

    ~BitString32Imp() = default;

    [[nodiscard]] Quality getQuality() const
    {
        return qualityM;
    }

    void setQuality(const QualityDescriptor quality)
    {
        qualityM = quality;
    }

protected:
    QualityDescriptor qualityM;
};

}
