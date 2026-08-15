/***********************************************************************************
 * \file Utils.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-26 00:06:46
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

#include <cassert>
#include <type_traits>

#ifndef ELINK_ASSERT
#define ELINK_ASSERT(x) assert(x)
#endif

#ifndef ELINK_STATIC_ASSERT
#define ELINK_STATIC_ASSERT(x, ...) static_assert(x __VA_OPT__(,) __VA_ARGS__)
#endif

namespace elink::util
{

template<typename T>
concept IsEnumClass = std::is_enum_v<T> && !std::is_convertible_v<T, int>;

template<typename T>
constexpr bool is_single_bit(T value) noexcept
{
    auto u = static_cast<std::underlying_type_t<T>>(value);
    return u != 0 && (u & (u - 1)) == 0;
}

}
