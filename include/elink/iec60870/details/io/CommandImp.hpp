/***********************************************************************************
 * \file CommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 18:24:22
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

#include "elink/iec60870/details/io/InformationObjectSerializable.hpp"

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

using SEBit = bool;

namespace details
{

template <typename inherit, TypeID typeID>
class CommandImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    CommandImp()
    : valueM{0}
    {
    }

    CommandImp(const IOA ioa, const SEBit selectCommand, const QUValue qu)
    : InformationObjectSerializable<inherit, typeID>{ioa}, valueM{0}
    {
        setSelect(selectCommand);
        setQU(qu);
    }

    ~CommandImp() = default;

    /**
     * \brief Return the value of the S/E bit of the qualifier of command
     *
     * \return S/E bit, true = select, false = execute
     */
    [[nodiscard]] bool isSelect() const
    {
        return valueM & 0x80;
    }

    void setSelect(const SEBit select)
    {
        select ? valueM |= 0x80 : valueM &= 0x7f;
    }

    /**
     * \brief Get the qualifier of command QU value
     *
     * \return the \ref QUValue
     */
    [[nodiscard]] QUValue getQU() const
    {
        return static_cast<QUValue>(valueM & 0x7c);
    }

    void setQU(const QUValue qu)
    {
        valueM = (valueM & 0x83) | static_cast<uint8_t>(qu);
    }

protected:
    uint8_t valueM;
};

}
}
