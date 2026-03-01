/***********************************************************************************
 * \file QualityDescriptor.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief information object quality descriptor
 * \date 2026-01-02 20:40:47
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

#include <cstdint>
#include <type_traits>

namespace elink::iec60870 {

// clang-format off
enum class QualityDescriptor : uint8_t {
    GOOD        = 0x00,         /**< Everything good */
    // full name
    SPILL       = 0x01,         /**< 1 = Overflow, 0 = No overflow */
    BLOCKED     = 0x10,         /**< 1 = Blocked, 0 = Not blocked */
    SUBSTITUTED = 0x20,         /**< 1 = Substituted, 0 = Not substituted */
    NON_TOPICAL = 0x40,         /**< 1 = Not topical, 0 = Topical */
    INVALID     = 0x80,         /**< 1= Invalid, 0 = Valid */
    // short name
    OV          = SPILL,        /**< 1 = Overflow, 0 = No overflow */
    BL          = BLOCKED,      /**< 1 = Blocked, 0 = Not blocked */
    SB          = SUBSTITUTED,  /**< 1 = Substituted, 0 = Not substituted */
    NT          = NON_TOPICAL,  /**< 1 = Not topical, 0 = Topical */
    IV          = INVALID,      /**< 1= Invalid, 0 = Valid */
};
// clang-format on

using Quality = QualityDescriptor;

constexpr Quality operator|(const Quality left, const Quality right) noexcept
{
    using U = std::underlying_type_t<Quality>;
    return static_cast<Quality>(static_cast<U>(left) | static_cast<U>(right));
}

inline bool operator&(const Quality left, const Quality right) noexcept
{
    using U = std::underlying_type_t<Quality>;
    return (static_cast<U>(left) & static_cast<U>(right)) != 0;
}

}
