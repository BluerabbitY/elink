/***********************************************************************************
 * \file BinaryCounterReading.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-02 19:54:04
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

#include <cstddef>
#include <cstdint>

namespace elink::iec60870
{

class BinaryCounterReading
{
public:
    BinaryCounterReading()
    : valueM{}, seqM{}
    {
    }

    BinaryCounterReading(const int32_t value,
                         const int seqNumber,
                         const bool hasCarry,
                         const bool isAdjusted,
                         const bool isInvalid)
    : valueM{value}, seqM{}
    {
        setSequenceNumber(seqNumber);
        setCarry(hasCarry);
        setAdjusted(isAdjusted);
        setInvalid(isInvalid);
    }

    ~BinaryCounterReading() = default;

    BinaryCounterReading(const BinaryCounterReading&) = default;

    BinaryCounterReading(BinaryCounterReading&&) = default;

    bool operator==(const BinaryCounterReading &other) const
    {
        return (valueM == other.valueM) && (seqM == other.seqM);
    }

    bool operator!=(const BinaryCounterReading &other) const
    {
        return (valueM != other.valueM) || (seqM != other.seqM);
    }

    [[nodiscard]] int32_t getValue() const
    {
        return valueM;
    }

    void setValue(const int32_t value)
    {
        valueM = value;
    }

    [[nodiscard]] uint8_t getSequenceNumber() const
    {
        return (seqM & 0x1f);
    }

    void setSequenceNumber(const uint8_t seq)
    {
        seqM = (0xe0 & seq) | (0x1f & seq);
    }

    [[nodiscard]] bool hasCarry() const
    {
        return (seqM & 0x20);
    }

    void setCarry(const bool value)
    {
        value ? (seqM |= 0x20) : (seqM &= 0xdf);
    }

    [[nodiscard]] bool isAdjusted() const
    {
        return (seqM & 0x40);
    }

    void setAdjusted(const bool value)
    {
        value ? (seqM |= 0x40) : (seqM &= 0xbf);
    }

    [[nodiscard]] bool isInvalid() const
    {
        return (seqM & 0x80);
    }

    void setInvalid(const bool value)
    {
        value ? (seqM |= 0x80) : (seqM &= 0x7f);
    }

protected:
    friend class IntegratedTotals;
    friend class IntegratedTotalsWithCP24Time2a;

    [[nodiscard]] constexpr std::size_t size() const
    {
        return sizeof(valueM) + sizeof(seqM);
    }

private:
    int32_t valueM;
    uint8_t seqM;
};

}
