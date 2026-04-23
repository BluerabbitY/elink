/***********************************************************************************
 * \file FileACK.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 20:20:20
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

#include "elink/iec60870/details/io/FileACKImp.hpp"

namespace elink::iec60870
{

class FileACK final : public details::FileACKImp<FileACK, TypeID::F_AF_NA_1>
{
public:
    FileACK() = default;

    ~FileACK() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << nofM << nameOfSectionM << afqM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> nofM >> nameOfSectionM >> afqM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(nofM) + sizeof(nameOfSectionM) + sizeof(afqM);
    }
};

}
