/***********************************************************************************
 * \file ResetProcessCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-12 00:22:59
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

#include "elink/iec60870/details/io/ResetProcessCommandImp.hpp"

namespace elink::iec60870
{

class ResetProcessCommand final : public details::ResetProcessCommandImp<ResetProcessCommand, TypeID::C_RP_NA_1>
{
public:
    ResetProcessCommand() = default;

    explicit ResetProcessCommand(const QualifierOfRPC qrp)
    : ResetProcessCommandImp{qrp}
    {
    }

    ~ResetProcessCommand() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << qrpM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> qrpM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(qrpM);
    }
};

}
