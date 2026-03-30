/***********************************************************************************
 * \file Type.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-07 20:05:37
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

#include <array>
#include <span>
#include <cstdint>
#include <functional>

#define E_UNUSED(x) (void)(x)

#define E_INTERRUPTABLE_BEGIN do {
#define E_INTERRUPTABLE_END } while(false)
#define E_INTERRUPT break

namespace elink
{

template <std::size_t N>
using Buffer = std::array<uint8_t, N>;

using LiteBufferView = std::span<const uint8_t>;

using LiteBuffer = std::span<uint8_t>;

using MessageBufferView = std::span<const uint8_t>;

using MessageBuffer = std::span<uint8_t>;

enum class MessageDir : uint8_t {
    MSG_DIR_RECV,
    MSG_DIR_SEND,
};

template <typename T>
concept RawMessageHandlerConcept = requires(T handler, MessageBufferView msg, MessageDir dir) {
    { handler(msg, dir) } -> std::same_as<void>;
};

using RawMessageHandler = std::function<void(MessageBufferView, MessageDir)>;

namespace internal
{

template <typename T>
concept TXMessageHandlerConcept = requires(T handler, MessageBufferView msg) {
    { handler(msg) } -> std::same_as<void>;
};

}

}
