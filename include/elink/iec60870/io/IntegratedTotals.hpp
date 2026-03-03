/***********************************************************************************
 * \file IntegratedTotals.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-02 21:39:41
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

namespace elink::iec60870
{

class IntegratedTotals final : public details::IntegratedTotalsImp<IntegratedTotals, TypeID::M_IT_NA_1> {
public:
    IntegratedTotals() = default;

    IntegratedTotals(const IOA ioa, const BinaryCounterReading& bcr)
    : IntegratedTotalsImp{ioa, bcr}
    {
    }

    ~IntegratedTotals() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << bcrM.valueM << bcrM.seqM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> bcrM.valueM >> bcrM.seqM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return bcrM.size();
    }
};

}
