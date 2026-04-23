/***********************************************************************************
 * \file FileImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 14:56:24
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

#include "elink/iec60870/details/io/InformationObjectSerializable.hpp"

namespace elink::iec60870
{

using NameOfFile = uint16_t;
using NOF = NameOfFile;

namespace details
{

template <typename inherit, TypeID typeID>
class FileImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    FileImp()
    : nofM{}
    {
    }

    explicit FileImp(IOA ioa, const NameOfFile nof)
    : InformationObjectSerializable<inherit, typeID>{ioa}, nofM{nof}
    {
    }

    ~FileImp() = default;

    [[nodiscard]] NameOfFile getNOF() const
    {
        return nofM;
    }

    void setNOF(const NameOfFile nof)
    {
        nofM = nof;
    }

protected:
    /* name of file */
    NameOfFile nofM;
};

}
}
