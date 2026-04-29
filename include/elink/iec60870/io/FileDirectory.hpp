/***********************************************************************************
 * \file FileDirectory.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 23:19:19
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

#include "elink/iec60870/details/io/FileDirectoryImp.hpp"

namespace elink::iec60870
{

class FileDirectory final : public details::FileDirectoryImp<FileDirectory, TypeID::F_DR_TA_1>
{
public:
    FileDirectory() = default;

    FileDirectory(const IOA ioa, const NOF nof, const uint32_t lengthOfFile, const uint8_t sof, const CP56Time2a creationTime)
    : FileDirectoryImp{ioa, nof, lengthOfFile, sof, creationTime}
    {
    }

    ~FileDirectory() = default;

protected:
    ELINK_IO_OBJECT;

    friend elink::details::OStream& operator<<(elink::details::OStream& stream, const FileDirectory& io)
    {
        return stream << io.nofM << io.lengthOfFileM << io.sofM << io.creationTimeM;
    }

    friend elink::details::IStream& operator>>(elink::details::IStream& stream, FileDirectory& io)
    {
        return stream >> io.nofM >> io.lengthOfFileM >> io.sofM >> io.creationTimeM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(nofM) + sizeof(lengthOfFileM) + sizeof(sofM) + sizeof(creationTimeM);
    }
};

}
