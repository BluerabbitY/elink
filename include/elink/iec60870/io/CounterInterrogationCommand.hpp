/***********************************************************************************
 * \file CounterInterrogationCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 16:41:34
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

#include "elink/iec60870/details/io/CounterInterrogationCommandImp.hpp"

namespace elink::iec60870
{

class CounterInterrogationCommand final
: public details::CounterInterrogationCommandImp<CounterInterrogationCommand, TypeID::C_CI_NA_1>
{
public:
    CounterInterrogationCommand() = default;

    explicit CounterInterrogationCommand(const QualifierOfCIC qcc)
    : CounterInterrogationCommandImp{IOA{0}, qcc}
    {
    }

    ~CounterInterrogationCommand() = default;

    void setAddress(IOA) = delete;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << qccM.valueM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> qccM.valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(qccM.valueM);
    }
};

}
