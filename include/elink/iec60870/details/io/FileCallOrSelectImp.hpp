/***********************************************************************************
 * \file FileCallOrSelectImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 19:55:20
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
class FileCallOrSelectImp : public FileSectionImp<inherit, typeID>
{
public:
    FileCallOrSelectImp()
    : scqM{0}
    {
    }

    FileCallOrSelectImp(const IOA ioa, const NOF nof, const uint8_t nos, const uint8_t scq)
    : FileSectionImp<inherit, typeID>{ioa, nof, nos}, scqM{scq}
    {
    }

    ~FileCallOrSelectImp() = default;

    [[nodiscard]] uint8_t getSCQ() const
    {
        return scqM;
    }

    void setSCQ(const uint8_t scq)
    {
        scqM = scq;
    }

protected:
    /* select and call qualifier */
    uint8_t scqM;
};

}
