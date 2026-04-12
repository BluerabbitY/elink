/***********************************************************************************
 * \file DelayAcquisitionCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-12 11:06:08
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

#include "elink/iec60870/details/io/DelayAcquisitionCommandImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class DelayAcquisitionCommand final
: public details::DelayAcquisitionCommandImp<DelayAcquisitionCommand, TypeID::C_CD_NA_1>
, public details::CPxxTime2aUtil<CP16Time2a>
{
public:
    DelayAcquisitionCommand() = default;

    explicit DelayAcquisitionCommand(const CP16Time2a cp16time2a)
    : CPxxTime2aUtil{cp16time2a}
    {
    }

    ~DelayAcquisitionCommand() = default;

    void setAddress(IOA) = delete;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
