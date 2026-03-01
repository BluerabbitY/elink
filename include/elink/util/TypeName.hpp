/***********************************************************************************
 * \file TypeName.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 22:59:58
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

#include <string_view>

namespace elink::util
{

template <typename T>
constexpr std::string_view type_name() {
#if defined(__clang__)
    constexpr std::string_view p = __PRETTY_FUNCTION__;
    constexpr std::string_view prefix = "T = ";
    constexpr std::string_view suffix = "]";
#elif defined(__GNUC__)
    constexpr std::string_view p = __PRETTY_FUNCTION__;
    constexpr std::string_view prefix = "with T = ";
    constexpr std::string_view suffix = "; std::string_view";
#elif defined(_MSC_VER)
    constexpr std::string_view p = __FUNCSIG__;
    constexpr std::string_view prefix = "type_name<";
    constexpr std::string_view suffix = ">(void)";
#endif

    constexpr auto start = p.find(prefix) + prefix.size();
    constexpr auto end = p.find(suffix, start);

    if constexpr (constexpr auto pos = p.rfind("::", end);pos != std::string_view::npos && pos >= start) {
        return p.substr(pos + 2, end - (pos + 2));
    } else {
        return p.substr(start, end - start);
    }
}

}
