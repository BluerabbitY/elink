/***********************************************************************************
 * \file CounterInterrogationCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 13:04:52
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

enum class QCCRequest : uint8_t
{
    GROUP_1 = 0x01,
    GROUP_2 = 0x02,
    GROUP_3 = 0x03,
    GROUP_4 = 0x04,
    GENERAL = 0x05,
};

enum class QCCFreeze : uint8_t
{
    READ                 = 0x00,
    FREEZE_WITHOUT_RESET = 0x40,
    FREEZE_WITH_RESET    = 0x80,
    COUNTER_RESET        = 0xc0,
};

/**
 * \brief QCC (Qualifier of counter interrogation command) according to IEC 60870-5-101:2003 7.2.6.23
 */
class QualifierOfCIC
{
public:
    QualifierOfCIC()
    : valueM{0x05}
    {
    }

    explicit QualifierOfCIC(const uint8_t value)
    : valueM{value}
    {
    }

    QualifierOfCIC(const QCCRequest request, const QCCFreeze freeze) : valueM{0}
    {
        setRequest(request);
        setFreeze(freeze);
    }

    [[nodiscard]] QCCFreeze getQCCFreeze() const
    {
        return static_cast<QCCFreeze>(valueM & 0xc0);
    }

    void setFreeze(const QCCFreeze freeze)
    {
        valueM = (valueM & 0x3f) | (static_cast<uint8_t>(freeze) & 0xc0);
    }

    [[nodiscard]] QCCRequest getQCCRequest() const
    {
        return static_cast<QCCRequest>(valueM & 0x3f);
    }

    void setRequest(const QCCRequest request)
    {
        valueM = (valueM & 0xc0) | (static_cast<uint8_t>(request) & 0x3f);
    }

protected:
    friend class CounterInterrogationCommand;

private:
    uint8_t valueM;
};

using QCC = QualifierOfCIC;

namespace details
{

template <typename inherit, TypeID typeID>
class CounterInterrogationCommandImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    CounterInterrogationCommandImp() = default;

    CounterInterrogationCommandImp(IOA ioa, const QualifierOfCIC qcc)
    : InformationObjectSerializable<inherit, typeID>(ioa), qccM{qcc}
    {
    }

    ~CounterInterrogationCommandImp() = default;

    [[nodiscard]] QualifierOfCIC getQCC() const
    {
        return qccM;
    }

    void setQCC(const QualifierOfCIC qcc)
    {
        qccM = qcc;
    }

protected:
    QualifierOfCIC qccM;
};

}
}
