/***********************************************************************************
 * \file SectionReadyImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-22 00:05:35
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

namespace elink::iec60870
{

class SectionReadyQualifier
{
public:
    SectionReadyQualifier()
    : valueM{0}
    {
    }

    SectionReadyQualifier(const bool isReady, const uint8_t value)
    : valueM{0}
    {
        setReady(isReady);
        setValue(value);
    }

    [[nodiscard]] bool isReady() const
    {
        return (valueM & 0x80) == 0x00;
    }

    void setReady(const bool isReady)
    {
        valueM = isReady ? (valueM & 0x7F) : (valueM | 0x80);
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
    friend class SectionReady;

private:
    uint8_t valueM;
};

using SRQ = SectionReadyQualifier;

namespace details
{

template <typename inherit, TypeID typeID>
class SectionReadyImp : public FileSectionImp<inherit, typeID>
{
public:
    SectionReadyImp()
    : lengthOfSectionM{0}
    {
    }

    SectionReadyImp(const IOA ioa,
                    const NOF nof,
                    const uint8_t nos,
                    const uint32_t lengthOfSection,
                    const bool isReady,
                    const uint8_t value)
    : FileSectionImp<inherit, typeID>{ioa, nof, nos}, lengthOfSectionM{lengthOfSection}, srqM{isReady, value}
    {
    }

    ~SectionReadyImp() = default;

    [[nodiscard]] uint32_t getLengthOfSection() const
    {
        return lengthOfSectionM;
    }

    void setLengthOfSection(const uint32_t lengthOfSection)
    {
        lengthOfSectionM = lengthOfSection;
    }

    [[nodiscard]] SectionReadyQualifier getSRQ() const
    {
        return srqM;
    }

    void setSRQ(const SectionReadyQualifier srq)
    {
        srqM = srq;
    }

protected:
    uint32_t lengthOfSectionM;
    /* section ready qualifier */
    SectionReadyQualifier srqM;
};

}
}
