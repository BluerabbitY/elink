/***********************************************************************************
 * \file FileSegmentImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-23 20:46:15
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
#include "elink/common/Type.hpp"

namespace elink::iec60870
{

using FileSegmentBuffer = Buffer<256>;

namespace details
{

template <typename inherit, TypeID typeID>
class FileSegmentImp : public FileSectionImp<inherit, typeID>
{
public:
    FileSegmentImp()
    : losM{0}, dataM{}
    {
    }

    FileSegmentImp(const IOA ioa, const NOF nof, const uint8_t nos, const LiteBufferView data)
    : FileSectionImp<inherit, typeID>{ioa, nof, nos}, losM{0}, dataM{}
    {
        setData(data);
    }

    ~FileSegmentImp() = default;

    [[nodiscard]] LiteBufferView getData() const
    {
        return {dataM.data(), losM};
    }

    void setData(const LiteBufferView data)
    {
        std::copy_n(data.data(), data.size(), dataM.begin());
        losM = static_cast<uint8_t>(data.size());
    }

protected:
    /* length of segment */
    uint8_t losM;
    /* user data buffer - file payload */
    FileSegmentBuffer dataM;
};

}
}
