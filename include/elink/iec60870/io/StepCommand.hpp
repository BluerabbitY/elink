/***********************************************************************************
 * \file StepCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 23:20:37
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

#include "elink/iec60870/details/io/StepCommandImp.hpp"

namespace elink::iec60870
{

class StepCommand final : public details::StepCommandImp<StepCommand, TypeID::C_RC_NA_1>
{
public:
    StepCommand() = default;

    StepCommand(const IOA ioa, const SEBit selectCommand, const QUValue qu, const StepCommandValue command)
    : StepCommandImp{ioa, selectCommand, qu, command}
    {
    }

    ~StepCommand() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM);
    }
};

}
