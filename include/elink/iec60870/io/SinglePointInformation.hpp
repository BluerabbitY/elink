/***********************************************************************************
 * \file SinglePointInformation.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief SinglePointInformation (TypeId: M_SP_NA_1)
 * \date 2025-12-16 21:46:53
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

#include "elink/iec60870/details/io/SinglePointInformationImp.hpp"

namespace elink::iec60870 {

class SinglePointInformation final : public details::SinglePointInformationImp<SinglePointInformation, TypeID::M_SP_NA_1> {
public:
    SinglePointInformation() = default;

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    SinglePointInformation(const IOA ioa, const bool value, const Quality quality = Quality::GOOD)
        : SinglePointInformationImp{ioa, value, quality}
    {
    }

    ~SinglePointInformation() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << siqM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> siqM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(siqM);
    }
};

}
