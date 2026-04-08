/***********************************************************************************
 * \file SingleCommandWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-08 21:43:17
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

#include "elink/iec60870/details/io/SingleCommandImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class SingleCommandWithCP56Time2a final :
public details::SingleCommandImp<SingleCommandWithCP56Time2a, TypeID::C_SC_TA_1>,
public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    SingleCommandWithCP56Time2a() = default;

    SingleCommandWithCP56Time2a(const IOA ioa, const SEBit selectCommand, const QUValue qu, const SingleCommandValue command, const CP56Time2a cp56time2a = CP56Time2a::now())
    : SingleCommandImp{ioa, selectCommand, qu, command}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~SingleCommandWithCP56Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
