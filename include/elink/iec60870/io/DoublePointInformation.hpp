/***********************************************************************************
 * \file DoublePointInformation.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief DoublePointInformation
 * \date 2025-12-24 22:48:33
 * 
 * \copyright Copyright (C) 2025-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "elink/iec60870/details/io/DoublePointInformationImp.hpp"

namespace elink::iec60870
{

class DoublePointInformation final : public details::DoublePointInformationImp<DoublePointInformation, TypeID::M_DP_NA_1>
{
public:
    DoublePointInformation() = default;

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    DoublePointInformation(const IOA ioa, const DValue value, const Quality quality = Quality::GOOD)
        : DoublePointInformationImp{ioa, value, quality}
    {
    }

    ~DoublePointInformation() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << diqM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> diqM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(diqM);
    }
};

}
