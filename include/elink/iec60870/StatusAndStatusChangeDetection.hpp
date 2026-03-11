/***********************************************************************************
 * \file StatusAndStatusChangeDetection.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-08 23:17:11
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

#include <bitset>

namespace elink::iec60870
{

class StatusAndStatusChangeDetection {
public:
    StatusAndStatusChangeDetection() = default;

    StatusAndStatusChangeDetection(const uint16_t st, const uint16_t cd)
    : stM{st}, cdM{cd}
    {
    }

    ~StatusAndStatusChangeDetection() = default;

    bool operator==(const StatusAndStatusChangeDetection& other) const
    {
        return stM == other.stM && cdM == other.cdM;
    }

    bool operator!=(const StatusAndStatusChangeDetection& other) const
    {
        return stM != other.stM || cdM != other.cdM;
    }

    [[nodiscard]] uint16_t getST() const
    {
        return stM.to_ulong();
    }

    void setST(const uint16_t value)
    {
        stM = value;
    }

    [[nodiscard]] uint16_t getCD() const
    {
        return cdM.to_ulong();
    }

    void setCDn(const uint16_t value)
    {
        cdM = value;
    }

    [[nodiscard]] bool getST(const int index) const
    {
        if (index >=0 && index < stM.size())
             return stM.test(index);
        else
             return false;
    }

    void setST(const int index, const bool status)
    {
        if (index >=0 && index < stM.size())
            stM.set(index, status);
    }

    [[nodiscard]] bool getCD(const int index) const
    {
        if (index >=0 && index < cdM.size())
             return cdM.test(index);
        else
             return false;
    }

    void setCD(const int index, const bool status)
    {
        if (index >=0 && index < cdM.size())
            cdM.set(index, status);
    }

protected:
    friend class PackedSinglePointWithSCD;

    [[nodiscard]] std::size_t size() const
    {
        return (stM.size() + cdM.size()) / 8;
    }

private:
    std::bitset<16> stM;
    std::bitset<16> cdM;
};

}
