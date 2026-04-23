/***********************************************************************************
 * \file FileReady.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-21 23:56:06
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

#include "elink/iec60870/details/io/FileReadyImp.hpp"

namespace elink::iec60870
{

class FileReady final : public details::FileReadyImp<FileReady, TypeID::F_FR_NA_1>
{
public:
    FileReady() = default;

    FileReady(const IOA ioa, const NOF nof, const uint32_t lengthOfFile, const bool positive, const uint8_t value)
    : FileReadyImp{ioa, nof, lengthOfFile, positive, value}
    {
    }

    ~FileReady() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << nofM << lengthOfFileM << frqM.valueM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> nofM >> lengthOfFileM >> frqM.valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(nofM) + sizeof(lengthOfFileM) + sizeof(frqM.valueM);
    }
};

}
