/***********************************************************************************
 * \file CommandWithQOSImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 23:49:01
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
#include "elink/iec60870/details/io/CommandImp.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class CommandWithQOSImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    CommandWithQOSImp()
    : qosM{0}
    {
    }

    /**
     * \brief Create a normalized set point command information object
     *
     * \param[in] ioa information object address
     * \param[in] selectCommand (S/E bit) if true send "select", otherwise "execute"
     * \param[in] ql qualifier of set point command (0 = standard, 1..127 = reserved)
     *
     */
    CommandWithQOSImp(const IOA ioa, const SEBit selectCommand, const uint8_t ql)
    : InformationObjectSerializable<inherit, typeID>(ioa), qosM{0}
    {
        setSelect(selectCommand);
        setQL(ql);
    }

    ~CommandWithQOSImp() = default;

    /**
     * \brief Return the value of the S/E bit of the qualifier of command
     *
     * \return S/E bit, true = select, false = execute
     */
    [[nodiscard]] SEBit isSelect() const
    {
        return (qosM & 0x80);
    }

    void setSelect(const SEBit selectCommand)
    {
        selectCommand ? qosM |= 0x80 : qosM &= 0x7f;
    }

    [[nodiscard]] uint8_t getQL() const
    {
        return (qosM & 0x7f);
    }

    void setQL(const uint8_t ql)
    {
        qosM = (qosM & 0x80) | (std::clamp<uint8_t>(ql, 0, 127) & 0x7f);
    }

protected:
    uint8_t qosM;
};

}
