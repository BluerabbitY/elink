/***********************************************************************************
 * \file SetpointCommandNormalized.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-15 23:34:17
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

#include "elink/iec60870/details/io/SetpointCommandNormalizedImp.hpp"

namespace elink::iec60870
{

class SetpointCommandNormalized final
: public details::SetpointCommandNormalizedImp<SetpointCommandNormalized, TypeID::C_SE_NA_1>
{
public:
    SetpointCommandNormalized() = default;

    /**
     * \brief Create a normalized set point command information object
     *
     * \param[in] ioa information object address
     * \param[in] selectCommand (S/E bit) if true send "select", otherwise "execute"
     * \param[in] ql qualifier of set point command (0 = standard, 1..127 = reserved)
     * \param[in] value normalized value between -1 and 1
     *
     */
    SetpointCommandNormalized(const IOA ioa, const SEBit selectCommand, const uint8_t ql, const NormalizedValue value)
    : SetpointCommandNormalizedImp{ioa, selectCommand, ql, value}
    {
        setValue(value);
    }

    ~SetpointCommandNormalized() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM << qosM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM >> qosM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + sizeof(qosM);
    }
};

}
