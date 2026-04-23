/***********************************************************************************
 * \file FileSectionImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 00:03:06
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

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class FileSectionImp : public FileImp<inherit, typeID>
{
public:
    FileSectionImp()
    : nameOfSectionM{0}
    {
    }

    FileSectionImp(const IOA ioa, const NOF nof, const uint8_t nos)
    : FileImp<inherit, typeID>{ioa, nof}, nameOfSectionM{nos}
    {
    }

    ~FileSectionImp() = default;

    [[nodiscard]] uint8_t getNameOfSection() const
    {
        return nameOfSectionM;
    }

    void setNameOfSection(const uint8_t nameOfSection)
    {
        nameOfSectionM = nameOfSection;
    }

protected:
    uint8_t nameOfSectionM;
};

}
