/***********************************************************************************
 * \file MeasuredValueNormalized.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-01 00:28:02
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

#include "elink/iec60870/details/io/MeasuredValueNormalizedImp.hpp"

namespace elink::iec60870
{

class MeasuredValueNormalized final : public details::MeasuredValueNormalizedImp<MeasuredValueNormalized, TypeID::M_ME_NA_1>
{
public:
    MeasuredValueNormalized() = default;

    MeasuredValueNormalized(const IOA ioa, const float value, const Quality quality = Quality::GOOD)
     : MeasuredValueNormalizedImp{ioa, value, quality}
    {
    }

    MeasuredValueNormalized(const IOA ioa, const OriginalPhyValue value, const NormalizationFactor factor, const float offset = 0.f, const Quality quality = Quality::GOOD)
     : MeasuredValueNormalizedImp{ioa, value, factor, offset, quality}
    {
    }

    ~MeasuredValueNormalized() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM << qualityM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM >> qualityM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + sizeof(qualityM);
    }
};

}
