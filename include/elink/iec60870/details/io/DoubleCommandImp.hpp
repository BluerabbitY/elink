/***********************************************************************************
 * \file DoubleCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 11:59:56
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
enum class DoubleCommandValue : uint8_t
{
    NOT_PERMITTED_0 = 0x00,
    OFF             = 0x01,
    ON              = 0x02,
    NOT_PERMITTED_3 = 0x03,
};
// clang-format on

namespace details
{

template <typename inherit, TypeID typeID>
class DoubleCommandImp : public CommandImp<inherit, typeID>
{
public:
    DoubleCommandImp()
    : CommandImp<inherit, typeID>{}
    {
        setState(DoubleCommandValue::OFF);
    }

    DoubleCommandImp(const IOA ioa, const SEBit selectCommand, const QUValue qu, const DoubleCommandValue command)
    : CommandImp<inherit, typeID>{ioa, selectCommand, qu}
    {
        setState(command);
    }

    ~DoubleCommandImp() = default;

    /**
     * \brief Get the state (command) value
     *
     * \return \ref DoubleCommandValue
     */
    [[nodiscard]] DoubleCommandValue getState() const
    {
        return static_cast<DoubleCommandValue>(this->valueM & 0x03);
    }

    void setState(const DoubleCommandValue state)
    {
        this->valueM = (this->valueM & 0xfc) | static_cast<uint8_t>(state);
    }
};

}
}
