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

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const QueryLog& io)
    {
        return stream << io.nofM << io.rangeStartTimeM << io.rangeStopTimeM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, QueryLog& io)
    {
        return stream >> io.nofM >> io.rangeStartTimeM >> io.rangeStopTimeM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(nofM) + sizeof(rangeStartTimeM) + sizeof(rangeStopTimeM);
    }
};

}
