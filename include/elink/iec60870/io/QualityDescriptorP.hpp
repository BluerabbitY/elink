/***********************************************************************************
 * \file QualityDescriptorP.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-03 23:13:53
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

namespace elink::iec60870
{

// clang-format off
/**
 * \brief QDP - Quality descriptor for events of protection equipment according to IEC 60870-5-101:2003 7.2.6.4
 */
enum class QualityDescriptorP : uint8_t {
    GOOD                 = 0x00,  /**< Everything good */
    // full name
    ELAPSED_TIME_INVALID = 0x08, /**< 1 = Elapsed time invalid, 0 = Elapsed time valid */
    BLOCKED              = 0x10, /**< 1 = Blocked, 0 = Not blocked */
    SUBSTITUTED          = 0x20, /**< 1 = Substituted, 0 = Not substituted */
    NON_TOPICAL          = 0x40, /**< 1 = Not topical, 0 = Topical */
    INVALID              = 0x80, /**< 1 = Invalid, 0 = Valid */
    // short name
    EI                   = ELAPSED_TIME_INVALID, /**< 1 = Elapsed time invalid, 0 = Elapsed time valid */
    BL                   = BLOCKED,              /**< 1 = Blocked, 0 = Not blocked */
    SB                   = SUBSTITUTED,          /**< 1 = Substituted, 0 = Not substituted */
    NT                   = NON_TOPICAL,          /**< 1 = Not topical, 0 = Topical */
    IV                   = INVALID,              /**< 1= Invalid, 0 = Valid */
};
// clang-format on

using QualityP = QualityDescriptorP;

constexpr QualityP operator|(const QualityP left, const QualityP right) noexcept
{
    using U = std::underlying_type_t<QualityP>;
    return static_cast<QualityP>(static_cast<U>(left) | static_cast<U>(right));
}

inline bool operator&(const QualityP left, const QualityP right) noexcept
{
    using U = std::underlying_type_t<QualityP>;
    return (static_cast<U>(left) & static_cast<U>(right)) != 0;
}

}
