/***********************************************************************************
 * \file FileReadyImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 15:19:27
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
#include "elink/iec60870/details/io/util/LengthInt.hpp"

namespace elink::iec60870
{

class FileReadyQualifier
{
public:
    FileReadyQualifier()
    : valueM{0}
    {
    }

    FileReadyQualifier(const bool positive, const uint8_t value)
    : valueM{0}
    {
        setPositive(positive);
        setValue(value);
    }

    [[nodiscard]] bool isPositive() const
    {
        return valueM & 0x80;
    }

    void setPositive(const bool positive)
    {
        valueM = positive ? (valueM | 0x80) : (valueM & 0x7F);
    }

    [[nodiscard]] uint8_t getValue() const
    {
        return valueM & 0x7F;
    }

    void setValue(const uint8_t value)
    {
        valueM = value & 0x7F | (valueM & 0x80);
    }

protected:
    friend class FileReady;

private:
    uint8_t valueM;
};

using FRQ = FileReadyQualifier;

namespace details
{

template <typename inherit, TypeID typeID>
class FileReadyImp : public FileImp<inherit, typeID>
{
public:
    FileReadyImp()
    : lengthOfFileM{0}
    {
    }

    FileReadyImp(const IOA ioa, const NOF nof, const uint32_t lengthOfFile, const bool positive, const uint8_t value)
        : FileImp<inherit, typeID>{ioa, nof}, lengthOfFileM{lengthOfFile}, frqM{positive, value}
    {
    }

    ~FileReadyImp() = default;

    [[nodiscard]] uint32_t getLengthOfFile() const
    {
        return lengthOfFileM.getValue();
    }

    void setLengthOfFile(const uint32_t lengthOfFile)
    {
        lengthOfFileM.setValue(std::clamp<uint32_t>(lengthOfFile, 0, 16777215));
    }

    [[nodiscard]] FileReadyQualifier getFRQ() const
    {
        return frqM;
    }

    void setFRQ(const FileReadyQualifier frq)
    {
        frqM = frq;
    }

protected:
    LengthInt lengthOfFileM;
    /* file ready qualifier */
    FileReadyQualifier frqM;
};

}
}
