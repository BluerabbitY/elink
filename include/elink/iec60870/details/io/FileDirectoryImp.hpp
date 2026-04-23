/***********************************************************************************
 * \file FileDirectoryImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 21:18:45
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

#include "elink/iec60870/details/io/FileImp.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class FileDirectoryImp : public FileImp<inherit, typeID>
{
public:
    FileDirectoryImp()
    : lengthOfFileM{0}, sofM{0}, creationTimeM{}
    {
    }

    FileDirectoryImp(const IOA ioa, const NOF nof, const uint32_t lengthOfFile, const uint8_t sof, const CP56Time2a creationTime)
    : FileImp<inherit, typeID>{ioa, nof}, lengthOfFileM{lengthOfFile}, sofM{sof}, creationTimeM{creationTime}
    {
    }

    ~FileDirectoryImp() = default;

    [[nodiscard]] uint32_t getLengthOfFile() const
    {
        return lengthOfFileM;
    }

    [[nodiscard]] uint8_t getSOF() const
    {
        return sofM;
    }

    [[nodiscard]] int getSTATUS() const
    {
        return sofM & CS101_SOF_STATUS;
    }

    [[nodiscard]] bool getLFD() const
    {
        return sofM & CS101_SOF_LFD;
    }

    [[nodiscard]] bool getFOR() const
    {
        return sofM & CS101_SOF_FOR;
    }

    [[nodiscard]] bool getFA() const
    {
        return sofM & CS101_SOF_FA;
    }

    [[nodiscard]] CP56Time2a getCreationTime() const
    {
        return creationTimeM;
    }

    void setCreationTime(const CP56Time2a& creationTime)
    {
        creationTimeM = creationTime;
    }

protected:
    /** \brief bit mask value for STATUS part of SOF */
    static constexpr uint8_t CS101_SOF_STATUS = 0x1f;

    /** \brief bit mask value for LFD (last file of the directory) flag */
    static constexpr uint8_t CS101_SOF_LFD = 0x20;

    /** \brief bit mask value for FOR (name defines subdirectory) flag */
    static constexpr uint8_t CS101_SOF_FOR = 0x40;

    /** \brief bit mask value for FA (file transfer of this file is active) flag */
    static constexpr uint8_t CS101_SOF_FA = 0x80;

    /* LOF */
    uint32_t lengthOfFileM;
    /* state of file */
    /**
     * \brief Status of file (SOF) definitions - IEC 60870-5-101:2003 7.2.6.38
     */
    uint8_t sofM;
    CP56Time2a creationTimeM;
};

}
