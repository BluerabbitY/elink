/***********************************************************************************
 * \file StatusCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 19:22:09
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

#include "elink/iec60870/details/io/CommandImp.hpp"

namespace elink::iec60870
{

// clang-format off
enum class QUValue : uint8_t
{
    NO_ADDITIONAL_DEFINITION = 0x00,
    SHORT_PULSE              = 0x04,
    LONG_PULSE               = 0x08,
    PERSISTENT_OUTPUT        = 0x0c,
};
// clang-format on

namespace details
{

template <typename inherit, TypeID typeID, typename StatusType>
class StatusCommandImp : public CommandImp<inherit, typeID>
{
public:
    StatusCommandImp() = default;

    StatusCommandImp(const IOA ioa, const SEBit selectCommand, const QUValue qu, const StatusType command)
    : CommandImp<inherit, typeID>{ioa, selectCommand}
    {
        setQU(qu);
        setState(command);
    }

    ~StatusCommandImp() = default;

    /**
     * \brief Get the qualifier of command QU value
     *
     * \return the \ref QUValue
     */
    [[nodiscard]] QUValue getQU() const
    {
        return static_cast<QUValue>(this->valueM & 0x7c);
    }

    void setQU(const QUValue qu)
    {
        this->valueM = (this->valueM & 0x83) | static_cast<uint8_t>(qu);
    }

    /**
     * \brief Get the state (command) value
     *
     * \return \ref DoubleCommandValue
     */
    [[nodiscard]] StatusType getState() const
    {
        return static_cast<StatusType>(this->valueM & 0x03);
    }

    void setState(const StatusType state)
    {
        this->valueM = (this->valueM & 0xfc) | static_cast<uint8_t>(state);
    }
};

}
}
