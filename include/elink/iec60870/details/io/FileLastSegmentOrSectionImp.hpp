/***********************************************************************************
 * \file FileLastSegmentOrSectionImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 20:05:45
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

#include "elink/iec60870/details/io/FileSectionImp.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class FileLastSegmentOrSectionImp : public FileSectionImp<inherit, typeID>
{
public:
    FileLastSegmentOrSectionImp()
    : lsqM{0}, chsM{0}
    {
    }

    FileLastSegmentOrSectionImp(const IOA ioa, const NOF nof, const uint8_t nos, const uint8_t lsq, const uint8_t chs)
    : FileSectionImp<inherit, typeID>{ioa, nof, nos}, lsqM{lsq}, chsM{chs}
    {
    }

    ~FileLastSegmentOrSectionImp() = default;

    [[nodiscard]] uint8_t getLSQ() const
    {
        return lsqM;
    }

    void setLSQ(const uint8_t lsq)
    {
        lsqM = lsq;
    }

    [[nodiscard]] uint8_t getCHS() const
    {
        return chsM;
    }

    void setCHS(const uint8_t chs)
    {
        chsM = chs;
    }

protected:
    /* last section or segment qualifier */
    uint8_t lsqM;
    /* checksum of section or segment */
    uint8_t chsM;
};

}
