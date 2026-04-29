/***********************************************************************************
 * \file SetpointCommandShort.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 20:56:31
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

#include "elink/iec60870/details/io/SetpointCommandShortImp.hpp"

namespace elink::iec60870
{

class SetpointCommandShort final : public details::SetpointCommandShortImp<SetpointCommandShort, TypeID::C_SE_NC_1>
{
public:
    SetpointCommandShort() = default;

    SetpointCommandShort(const IOA ioa, const SEBit selectCommand, const QLValue ql, const float value)
    : SetpointCommandShortImp{ioa, selectCommand, ql, value}
    {
    }

    ~SetpointCommandShort() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const SetpointCommandShort& io)
    {
        return stream << io.sValueM << io.valueM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, SetpointCommandShort& io)
    {
        return stream >> io.sValueM >> io.valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(sValueM) + sizeof(valueM);
    }
};

}
