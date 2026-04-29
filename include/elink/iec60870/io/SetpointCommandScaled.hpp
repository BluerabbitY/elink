/***********************************************************************************
 * \file SetpointCommandScaled.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 20:00:59
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

namespace elink::iec60870
{

class SetpointCommandScaled final : public details::SetpointCommandScaledImp<SetpointCommandScaled, TypeID::C_SE_NB_1>
{
public:
    SetpointCommandScaled() = default;

    SetpointCommandScaled(const IOA ioa, const SEBit selectCommand, const QLValue ql, const ScaledValue value)
    : SetpointCommandScaledImp{ioa, selectCommand, ql, value}
    {
    }

    ~SetpointCommandScaled() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const SetpointCommandScaled& io)
    {
        return stream << io.sValueM << io.valueM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, SetpointCommandScaled& io)
    {
        return stream >> io.sValueM >> io.valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(sValueM) + sizeof(valueM);
    }
};

}
