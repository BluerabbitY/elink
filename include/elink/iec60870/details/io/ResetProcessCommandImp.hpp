/***********************************************************************************
 * \file ResetProcessCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-12 00:17:14
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

/**
 * \brief QRP (Qualifier of reset process command) according to IEC 60870-5-101:2003 7.2.6.27
 */
enum class QualifierOfRPC : uint8_t
{
    NOT_USED = 0,
    GENERAL_RESET = 1,
    RESET_PENDING_INFO_WITH_TIME_TAG = 2,
};

using QRP = QualifierOfRPC;

namespace details
{

template <typename inherit, TypeID typeID>
class ResetProcessCommandImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    ResetProcessCommandImp()
    : qrpM{QRP::NOT_USED}
    {
    }

    explicit ResetProcessCommandImp(const QualifierOfRPC qrp)
    : InformationObjectSerializable<inherit, typeID>{}, qrpM{qrp}
    {
    }

    ~ResetProcessCommandImp() = default;

    void setAddress(IOA) = delete;

    [[nodiscard]] QualifierOfRPC getQRP() const
    {
        return qrpM;
    }

    void setQRP(const QualifierOfRPC qrp)
    {
        qrpM = qrp;
    }

protected:
    QualifierOfRPC qrpM;
};

}
}
