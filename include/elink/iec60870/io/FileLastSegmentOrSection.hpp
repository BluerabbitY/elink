/***********************************************************************************
 * \file FileLastSegmentOrSection.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 20:11:59
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

#include "elink/iec60870/details/io/FileLastSegmentOrSectionImp.hpp"

namespace elink::iec60870
{

class FileLastSegmentOrSection final
: public details::FileLastSegmentOrSectionImp<FileLastSegmentOrSection, TypeID::F_LS_NA_1>
{
public:
    FileLastSegmentOrSection() = default;

    FileLastSegmentOrSection(const IOA ioa, const NOF nof, const uint8_t nos, const uint8_t lsq, const uint8_t chs)
    : FileLastSegmentOrSectionImp{ioa, nof, nos, lsq, chs}
    {
    }

    ~FileLastSegmentOrSection() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const FileLastSegmentOrSection& io)
    {
        return stream << io.nofM << io.nameOfSectionM << io.lsqM << io.chsM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, FileLastSegmentOrSection& io)
    {
        return stream >> io.nofM >> io.nameOfSectionM >> io.lsqM >> io.chsM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(nofM) + sizeof(nameOfSectionM) + sizeof(lsqM) + sizeof(chsM);
    }
};

}
