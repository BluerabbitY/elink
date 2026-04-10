/***********************************************************************************
 * \file SetpointCommandScaledWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 00:34:50
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

#include "elink/iec60870/details/io/SetpointCommandScaledImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class SetpointCommandScaledWithCP56Time2a final
: public details::SetpointCommandScaledImp<SetpointCommandScaledWithCP56Time2a, TypeID::C_SE_TB_1>
, public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    SetpointCommandScaledWithCP56Time2a() = default;

    SetpointCommandScaledWithCP56Time2a(const IOA ioa,
                                        const SEBit selectCommand,
                                        const QLValue ql,
                                        const ScaledValue value,
                                        const CP56Time2a cp56time2a = CP56Time2a::now())
    : SetpointCommandScaledImp{ioa, selectCommand, ql, value}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~SetpointCommandScaledWithCP56Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << sValueM << valueM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> sValueM >> valueM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(sValueM) + sizeof(valueM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
