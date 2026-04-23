/***********************************************************************************
 * \file QueryLogImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 23:30:19
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

#include "elink/iec60870/details/io/FileImp.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class QueryLogImp : public FileImp<inherit, typeID> {
public:
    QueryLogImp() = default;

    QueryLogImp(const IOA ioa, const NOF nof, const CP56Time2a rangeStartTime, const CP56Time2a rangeStopTime)
    : FileImp<inherit, typeID>{ioa, nof}, rangeStartTimeM{rangeStartTime}, rangeStopTimeM{rangeStopTime}
    {
    }

    ~QueryLogImp() = default;

    [[nodiscard]] CP56Time2a getRangeStartTime() const
    {
        return rangeStartTimeM;
    }

    void setRangeStartTime(const CP56Time2a rangeStartTime)
    {
        rangeStartTimeM = rangeStartTime;
    }

    [[nodiscard]] CP56Time2a getRangeStopTime() const
    {
        return rangeStopTimeM;
    }

    void setRangeStopTime(const CP56Time2a rangeStopTime)
    {
        rangeStopTimeM = rangeStopTime;
    }

protected:
    CP56Time2a rangeStartTimeM;
    CP56Time2a rangeStopTimeM;
};

}
