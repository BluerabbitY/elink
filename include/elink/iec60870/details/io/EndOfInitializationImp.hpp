/***********************************************************************************
 * \file EndOfInitializationImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 10:48:37
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

#include "InformationObjectSerializable.hpp"

namespace elink::iec60870
{

/**
 * \brief Cause of Initialization (COI) according to IEC 60870-5-101:2003 7.2.6.21
 */
// clang-format off
enum class CauseOfInitialization : uint8_t
{
    LOCAL_SWITCH_ON    = 0,
    LOCAL_MANUAL_RESET = 1,
    REMOTE_RESET       = 2,
};
// clang-format on

using COI = CauseOfInitialization;

namespace details
{

template <typename inherit, TypeID typeID>
class EndOfInitializationImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    EndOfInitializationImp()
    : coiM{COI::LOCAL_SWITCH_ON}
    {
    }

    explicit EndOfInitializationImp(const CauseOfInitialization coi)
    : InformationObjectSerializable<inherit, typeID>{IOA{0}}, coiM(coi)
    {
    }

    ~EndOfInitializationImp() = default;

    [[nodiscard]] CauseOfInitialization getCOI() const
    {
        return coiM;
    }

    void setCOI(const CauseOfInitialization coi)
    {
        coiM = coi;
    }

protected:
    CauseOfInitialization coiM;
};

}
}
