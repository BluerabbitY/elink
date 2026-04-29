/***********************************************************************************
 * \file FileCallOrSelect.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 19:59:55
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

#include "elink/iec60870/details/io/FileCallOrSelectImp.hpp"

namespace elink::iec60870
{

class FileCallOrSelect final : public details::FileCallOrSelectImp<FileCallOrSelect, TypeID::F_SC_NA_1>
{
public:
    FileCallOrSelect() = default;

    FileCallOrSelect(const IOA ioa, const NOF nof, const uint8_t nos, const uint8_t scq)
    : FileCallOrSelectImp{ioa, nof, nos, scq}
    {
    }

    ~FileCallOrSelect() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const FileCallOrSelect& io)
    {
        return stream << io.nofM << io.nameOfSectionM << io.scqM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, FileCallOrSelect& io)
    {
        return stream >> io.nofM >> io.nameOfSectionM >> io.scqM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(nofM) + sizeof(nameOfSectionM) + sizeof(scqM);
    }
};

}
