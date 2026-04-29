/***********************************************************************************
 * \file IntegratedTotalsWithCP56Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-14 09:41:33
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

#include "elink/iec60870/details/io/IntegratedTotalsImp.hpp"
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class IntegratedTotalsWithCP56Time2a final
    : public details::IntegratedTotalsImp<IntegratedTotalsWithCP56Time2a, TypeID::M_IT_TB_1>
    , public details::CPxxTime2aUtil<CP56Time2a>
{
public:
    IntegratedTotalsWithCP56Time2a() = default;

    IntegratedTotalsWithCP56Time2a(const IOA ioa,
                                   const BinaryCounterReading& bcr,
                                   const CP56Time2a cp56time2a = CP56Time2a::now())
    : IntegratedTotalsImp{ioa, bcr}, CPxxTime2aUtil{cp56time2a}
    {
    }

    ~IntegratedTotalsWithCP56Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const IntegratedTotalsWithCP56Time2a& io)
    {
        return stream << io.bcrM.valueM << io.bcrM.seqM << io.cpxxtime2aM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, IntegratedTotalsWithCP56Time2a& io)
    {
        return stream >> io.bcrM.valueM >> io.bcrM.seqM >> io.cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return bcrM.size() + sizeof(cpxxtime2aM);
    }
};

}
