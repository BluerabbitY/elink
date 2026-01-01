/***********************************************************************************
 * \file QualityDescriptor.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief information object quality descriptor
 * \date 2026-01-02 20:40:47
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

#include <cstdint>
#include <type_traits>

namespace elink::iec60870 {

// clang-format off
enum class QualityDescriptor : uint8_t {
    GOOD        = 0x00,
    OVERFLOW    = 0x01,
    BLOCKED     = 0x10,
    SUBSTITUTED = 0x20,
    NON_TOPICAL = 0x40,
    INVALID     = 0x80,
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
