/***********************************************************************************
 * \file QueryLog.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 23:42:42
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

#include "elink/iec60870/details/io/QueryLogImp.hpp"

namespace elink::iec60870
{

class QueryLog final : public details::QueryLogImp<QueryLog, TypeID::F_SC_NB_1>
{
public:
    QueryLog() = default;

    ~QueryLog() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << nofM << rangeStartTimeM << rangeStopTimeM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> nofM >> rangeStartTimeM >> rangeStopTimeM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(nofM) + getCPxxTime2aLength(rangeStartTimeM) + getCPxxTime2aLength(rangeStopTimeM);
    }
};

}
