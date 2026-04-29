/***********************************************************************************
 * \file SingleCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 11:07:02
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

#include "elink/iec60870/details/io/SingleCommandImp.hpp"

namespace elink::iec60870
{

class SingleCommand final : public details::SingleCommandImp<SingleCommand, TypeID::C_SC_NA_1>
{
public:
    SingleCommand() = default;

    /**
     * \brief Create a single point command information object
     *
     * \param[in] ioa information object address
     * \param[in] selectCommand (S/E bit) if true send "select", otherwise "execute"
     * \param[in] qu qualifier of command QU parameter \ref QUValue
     * \param[in] command the command value
     *
     */
    SingleCommand(const IOA ioa, const SEBit selectCommand, const QUValue qu, const SingleCommandValue command)
    : SingleCommandImp{ioa, selectCommand, qu, command}
    {
    }

    ~SingleCommand() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const SingleCommand& io)
    {
        return stream << io.valueM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, SingleCommand& io)
    {
        return stream >> io.valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM);
    }
};

}
