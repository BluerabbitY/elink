/***********************************************************************************
 * \file ParameterScaledValue.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 11:10:49
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

#include "elink/iec60870/details/io/MeasuredValueScaledWithoutQualityImp.hpp"
#include "elink/iec60870/details/io/util/QualifierOfParameterMVUtil.hpp"

namespace elink::iec60870
{

class ParameterScaledValue final
: public details::MeasuredValueScaledWithoutQualityImp<ParameterScaledValue, TypeID::P_ME_NB_1>
, public details::QualifierOfParameterMVUtil
{
public:
    ParameterScaledValue() = default;

    ParameterScaledValue(const IOA ioa, const ScaledValue value, const QualifierOfParameterMV qpm)
    : MeasuredValueScaledWithoutQualityImp{ioa, value}, QualifierOfParameterMVUtil{qpm}
    {
    }

    ~ParameterScaledValue() = default;

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
