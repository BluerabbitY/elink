/***********************************************************************************
* \file StepPositionInformation.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-12-31 22:26:05
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

#include "elink/iec60870/details/io/StepPositionInformationImp.hpp"

namespace elink::iec60870 {

class StepPositionInformation final : public details::StepPositionInformationImp<StepPositionInformation, TypeID::M_ST_NA_1> {
public:
    StepPositionInformation() = default;

    // Valid Quality: GOOD, OVERFLOW, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    StepPositionInformation(const IOA ioa, const int value, const bool isTransient, const Quality quality = Quality::GOOD)
        : StepPositionInformationImp{ioa, value, isTransient, quality}
    {
        setValue(value);
        setTransient(isTransient);
    }

    ~StepPositionInformation() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << vtiM << qualityM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> vtiM >> qualityM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(vtiM) + sizeof(qualityM);
    }
};

}
