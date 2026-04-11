/***********************************************************************************
 * \file ReadCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 17:08:35
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

#include "elink/iec60870/details/io/ReadCommandImp.hpp"

namespace elink::iec60870
{

class ReadCommand final : public details::ReadCommandImp<ReadCommand, TypeID::C_RD_NA_1>
{
public:
    ReadCommand() = default;

    explicit ReadCommand(const IOA ioa)
    : ReadCommandImp{ioa}
    {
    }

    ~ReadCommand() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream&) const
    {
    }

    template <typename IStream>
    void deserialize(IStream&)
    {
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return 0;
    }
};

}
