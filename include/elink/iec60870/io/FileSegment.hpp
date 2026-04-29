/***********************************************************************************
 * \file FileSegment.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 21:00:01
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

#include "elink/iec60870/details/io/FileSegmentImp.hpp"

namespace elink::iec60870
{

class FileSegment final : public details::FileSegmentImp<FileSegment, TypeID::F_SG_NA_1>
{
public:
    FileSegment() = default;

    FileSegment(const IOA ioa, const NOF nof, const uint8_t nos, const LiteBufferView data)
    : FileSegmentImp{ioa, nof, nos, data}
    {
    }

    ~FileSegment() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const FileSegment& io)
    {
        return stream << io.nofM << io.nameOfSectionM << io.losM << LiteBufferView{io.dataM.data(), io.losM};
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, FileSegment& io)
    {
        return stream >> io.nofM >> io.nameOfSectionM >> io.losM >> LiteBuffer{io.dataM.data(), io.losM};
    }

    [[nodiscard]] std::size_t payloadLength() const
    {
        return sizeof(nofM) + sizeof(nameOfSectionM) + sizeof(losM) + losM;
    }
};

}
