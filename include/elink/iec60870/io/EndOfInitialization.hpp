/***********************************************************************************
 * \file EndOfInitialization.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 11:00:27
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

#include "elink/iec60870/details/io/EndOfInitializationImp.hpp"

namespace elink::iec60870
{

class EndOfInitialization final : public details::EndOfInitializationImp<EndOfInitialization, TypeID::M_EI_NA_1>
{
public:
    EndOfInitialization() = default;

    explicit EndOfInitialization(const CauseOfInitialization coi)
    : EndOfInitializationImp{coi}
    {
    }

    ~EndOfInitialization() = default;

    void setAddress(IOA) = delete;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << coiM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> coiM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(coiM);
    }
};

}
