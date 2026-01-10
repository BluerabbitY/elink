/***********************************************************************************
 * \file Type.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-07 20:05:37
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

#include <span>
#include <cstdint>

#define E_UNUSED(x) (void)(x)

namespace elink
{

using LiteBufferView = std::span<const uint8_t>;

using LiteBuffer = std::span<uint8_t>;

using MessageBufferView = std::span<const uint8_t>;

using MessageBuffer = std::span<uint8_t>;

enum class MessageDir : uint8_t {
    MSG_RECV,
    MSG_SEND,
};

template <typename T>
concept RawMessageHandlerConcept = requires(T handler, MessageBufferView msg, MessageDir dir) {
    { handler(msg, dir) } -> std::same_as<void>;
};

enum LogLevel {
    DBG,
    INF,
    WRN,
    ERR,
    CRI,
    FAT,
};

namespace internal
{

template <typename T>
concept TXMessageHandlerConcept = requires(T handler, MessageBufferView msg) {
    { handler(msg) } -> std::same_as<void>;
};

}

}
