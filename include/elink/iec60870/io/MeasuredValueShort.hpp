/***********************************************************************************
 * \file MeasuredValueShort.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-02 19:11:39
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

#include "elink/iec60870/details/io/MeasuredValueShortImp.hpp"

namespace elink::iec60870
{

class MeasuredValueShort final : public details::MeasuredValueShortImp<MeasuredValueShort, TypeID::M_ME_NC_1>
{
public:
    MeasuredValueShort() = default;

    MeasuredValueShort(const IOA ioa, const float value, const Quality quality = Quality::GOOD)
    : MeasuredValueShortImp{ioa, value, quality}
    {
    }

    ~MeasuredValueShort() = default;

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
