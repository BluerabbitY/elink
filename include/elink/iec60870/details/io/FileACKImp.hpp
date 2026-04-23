/***********************************************************************************
 * \file FileACKImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 20:16:54
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
class FileACKImp : public FileSectionImp<inherit, typeID>
{
public:
    FileACKImp()
    : afqM{0}
    {
    }

    FileACKImp(const IOA ioa, const NOF nof, const uint8_t nos, const uint8_t afq)
    : FileSectionImp<inherit, typeID>{ioa, nof, nos}, afqM{afq}
    {
    }

    ~FileACKImp() = default;

    [[nodiscard]] uint8_t getAFQ() const
    {
        return afqM;
    }

    void setAFQ(const uint8_t afq)
    {
        afqM = afq;
    }

protected:
    /* AFQ (acknowledge file or section qualifier) */
    uint8_t afqM;
};

}
