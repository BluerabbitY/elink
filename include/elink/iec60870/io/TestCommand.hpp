/***********************************************************************************
 * \file TestCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 18:45:55
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

#include "elink/iec60870/details/io/TestCommandImp.hpp"

namespace elink::iec60870
{

class TestCommand final : public details::TestCommandImp<TestCommand, TypeID::C_TS_NA_1>
{
public:
    explicit TestCommand(const bool isValid = true)
    {
        setIsValid(isValid);
    }

    ~TestCommand() = default;

    void setAddress(IOA) = delete;

    [[nodiscard]] bool isValid() const
    {
        return valueM == FixedTestBitPattern;
    }

    void setIsValid(const bool isValid)
    {
        valueM = isValid ?  FixedTestBitPattern : 0x0000;
    }

protected:
    static constexpr uint16_t FixedTestBitPattern = 0x55aa;

    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM);
    }
};

}
