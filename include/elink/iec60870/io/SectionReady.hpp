/***********************************************************************************
 * \file SectionReady.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-22 23:51:12
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

#include "elink/iec60870/details/io/SectionReadyImp.hpp"

namespace elink::iec60870
{

class SectionReady final : public details::SectionReadyImp<SectionReady, TypeID::F_SR_NA_1>
{
public:
    SectionReady() = default;

    SectionReady(const IOA ioa,
                 const NOF nof,
                 const uint8_t nos,
                 const uint32_t lengthOfSection,
                 const bool isReady,
                 const uint8_t value)
    : SectionReadyImp{ioa, nof, nos, lengthOfSection, isReady, value}
    {
    }

    ~SectionReady() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << nofM << nameOfSectionM << lengthOfSectionM << srqM.valueM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> nofM >> nameOfSectionM >> lengthOfSectionM >> srqM.valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(nofM) + sizeof(nameOfSectionM) + sizeof(lengthOfSectionM) + sizeof(srqM.valueM);
    }
};

}
