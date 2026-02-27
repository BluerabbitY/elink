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
