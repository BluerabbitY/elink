/***********************************************************************************
 * \file ParameterFloatValue.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 12:42:08
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

#include "elink/iec60870/details/io/MeasuredValueShortWithoutQualityImp.hpp"
#include "elink/iec60870/details/io/util/QualifierOfParameterMVUtil.hpp"

namespace elink::iec60870
{

class ParameterFloatValue final
: public details::MeasuredValueShortWithoutQualityImp<ParameterFloatValue, TypeID::P_ME_NC_1>
, public details::QualifierOfParameterMVUtil
{
public:
    ParameterFloatValue() = default;

    ParameterFloatValue(const IOA ioa, const float value, const QualifierOfParameterMV qpm)
    : MeasuredValueShortWithoutQualityImp{ioa, value}, QualifierOfParameterMVUtil{qpm}
    {
    }

    ~ParameterFloatValue() = default;

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
