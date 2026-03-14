/***********************************************************************************
 * \file DoubleCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 20:09:56
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

#include "elink/iec60870/details/io/DoubleCommandImp.hpp"

namespace elink::iec60870
{

class DoubleCommand final : public details::DoubleCommandImp<DoubleCommand, TypeID::C_DC_NA_1>
{
public:
    DoubleCommand() = default;

    /**
     * \brief Create a double command information object
     *
     * \param[in] ioa information object address
     * \param[in] selectCommand (S/E bit) if true send "select", otherwise "execute"
     * \param[in] qu qualifier of command QU parameter(0 = no additional definition, 1 = short pulse, 2 = long pulse, 3 = persistent output
     * \param[in] command the double command state \ref DoubleCommandValue
     *
     */
    DoubleCommand(const IOA ioa, const SEBit selectCommand, const QUValue qu, const DoubleCommandValue command)
    : DoubleCommandImp{ioa, selectCommand, qu, command}
    {
    }

    ~DoubleCommand() = default;

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
