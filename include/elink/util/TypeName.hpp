/***********************************************************************************
 * \file TypeName.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 22:59:58
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
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
