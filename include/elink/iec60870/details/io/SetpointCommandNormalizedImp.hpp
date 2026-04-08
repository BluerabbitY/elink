/***********************************************************************************
 * \file SetpointCommandNormalizedImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-15 01:19:08
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

#include "elink/iec60870/details/io/SetpointCommandImp.hpp"
#include "elink/iec60870/details/io/util/NormalizedValueUtil.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class SetpointCommandNormalizedImp : public SetpointCommandImp<inherit, typeID>
{
public:
    SetpointCommandNormalizedImp()
    : sValueM{0}
    {
    }

    /**
     * \brief Create a normalized set point command information object
     *
     * \param[in] ioa information object address
     * \param[in] selectCommand (S/E bit) if true send "select", otherwise "execute"
     * \param[in] ql qualifier of set point command (0 = standard, 1..127 = reserved)
     * \param[in] value normalized value between -1 and 1
     *
     */
    SetpointCommandNormalizedImp(const IOA ioa, const SEBit selectCommand, const QLValue ql, const NormalizedValue value)
    : SetpointCommandImp<inherit, typeID>{ioa, selectCommand, ql}, sValueM{0}
    {
        setValue(value);
    }

    ~SetpointCommandNormalizedImp() = default;

    [[nodiscard]] NormalizedValue getValue() const
    {
        return scaledToNormalized(sValueM);
    }

    void setValue(const NormalizedValue value)
    {
        sValueM = normalizedToScaled(value);
    }

protected:
    NormalizedValueBuffer sValueM;
};

}

