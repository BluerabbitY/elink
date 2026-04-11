/***********************************************************************************
 * \file InterrogationCommand.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 16:15:23
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

#include "elink/iec60870/details/io/InterrogationCommandImp.hpp"

namespace elink::iec60870
{

class InterrogationCommand final : public details::InterrogationCommandImp<InterrogationCommand, TypeID::C_IC_NA_1> {
public:
    InterrogationCommand() = default;

    explicit InterrogationCommand(const QualifierOfInterrogation qoi)
    : InterrogationCommandImp{IOA{0}, qoi}
    {
    }

    ~InterrogationCommand() = default;

    void setAddress(IOA) = delete;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << qoiM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> qoiM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(qoiM);
    }
};

}
