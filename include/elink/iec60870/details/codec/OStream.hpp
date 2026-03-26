/***********************************************************************************
 * \file OStream.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief output stream
 * \date 2025-12-14 00:24:29
 * 
 * \copyright Copyright (C) 2025-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "elink/common/details/codec/OStream.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"
#include "elink/iec60870/io/InformationObjectAddress.hpp"
#include "elink/iec60870/details/io/BitString32Imp.hpp"

namespace elink::iec60870::details {

class OStream : public elink::details::OStream<OStream> {
public:
    OStream(uint8_t* buffer, const std::size_t size) : elink::details::OStream<OStream>{buffer, size}
    {
    }

    ~OStream() = default;

    using elink::details::OStream<OStream>::operator<<;

    OStream& operator<<(const IOA ioa)
    {
        const std::size_t size = ioa.length();
        auto value = ioa.address();
        return *this << LiteBufferView{reinterpret_cast<uint8_t*>(&value), size};
    }

    template <typename T>
    OStream& operator<<(const T& cpxxtime2a) requires (std::is_same_v<T, CP16Time2a> || std::is_same_v<T, CP24Time2a> ||
                                                       std::is_same_v<T, CP32Time2a> || std::is_same_v<T, CP56Time2a>)
    {
        return *this << LiteBufferView{getCPxxTime2aData<T>(cpxxtime2a), getCPxxTime2aLength<T>(cpxxtime2a)};
    }

    OStream& operator<<(const BitString32Value& value)
    {
        return *this << static_cast<uint32_t>(value.to_ulong());
    }
};

}
