/***********************************************************************************
 * \file ParameterNormalizedValue.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-18 23:15:16
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

#include "elink/iec60870/details/io/ParameterNormalizedValueImp.hpp"

namespace elink::iec60870
{

class ParameterNormalizedValue final
: public details::ParameterNormalizedValueImp<ParameterNormalizedValue, TypeID::P_ME_NA_1>
{
public:
    ParameterNormalizedValue() = default;

    ParameterNormalizedValue(const IOA ioa, const NormalizedValue value, const QualifierOfParameterMV qpm)
    : ParameterNormalizedValueImp{ioa, value, qpm}
    {
    }

    ParameterNormalizedValue(const IOA ioa, const OriginalPhyValue value, const NormalizationFactor factor, const float offset, const QualifierOfParameterMV qpm)
    : ParameterNormalizedValueImp{ioa, value, factor, offset, qpm}
    {
    }

    ~ParameterNormalizedValue() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM << qpmM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM >> qpmM;;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + sizeof(qpmM);
    }
};

}
