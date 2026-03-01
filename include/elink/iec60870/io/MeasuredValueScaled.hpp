/***********************************************************************************
 * \file MeasuredValueScaled.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-01 22:42:44
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

#include "elink/iec60870/details/io/MeasuredValueScaledImp.hpp"

namespace elink::iec60870
{

class MeasuredValueScaled final : public details::MeasuredValueScaledImp<MeasuredValueScaled, TypeID::M_ME_NB_1>
{
public:
    MeasuredValueScaled() = default;

    /**
     * \brief Create a new instance of MeasuredValueScaled information object
     *
     * \param ioa Information object address
     * \param value scaled value (range [-32768, 32767])
     * \param quality quality descriptor (according to IEC 60870-5-101:2003 7.2.6.3)
     *
     */
    MeasuredValueScaled(const IOA ioa, const ScaledValue value, const Quality quality = Quality::GOOD)
    : MeasuredValueScaledImp{ioa, value, quality}
    {
    }

    ~MeasuredValueScaled() = default;

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
