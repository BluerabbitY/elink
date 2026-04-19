/***********************************************************************************
 * \file ParameterActivation.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 13:32:18
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

#include "elink/iec60870/details/io/ParameterActivationImp.hpp"

namespace elink::iec60870
{

class ParameterActivation final : public details::ParameterActivationImp<ParameterActivation, TypeID::P_AC_NA_1>
{
public:
    ParameterActivation() = default;

    ParameterActivation(const IOA ioa, const QualifierOfParameterActivation qpa)
    : ParameterActivationImp{ioa, qpa}
    {
    }

    ~ParameterActivation() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << qpaM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> qpaM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(qpaM);
    }
};

}
