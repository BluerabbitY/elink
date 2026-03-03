/***********************************************************************************
 * \file IStream.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief input stream
 * \date 2025-12-17 23:07:36
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

#include "elink/common/details/codec/IStream.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"
#include "elink/iec60870/io/InformationObjectAddress.hpp"
#include "elink/iec60870/details/io/BitString32Imp.hpp"

namespace elink::iec60870::details {

class IStream : public elink::details::IStream<IStream> {
public:
    IStream(const uint8_t* buffer, const std::size_t size) : elink::details::IStream<IStream>{buffer, size}
    {
    }

    ~IStream() = default;

    using elink::details::IStream<IStream>::operator>>;

    IStream& operator>>(IOA& ioa)
    {
        int value = 0;
        *this >> LiteBuffer{reinterpret_cast<uint8_t*>(&value), static_cast<std::size_t>(ioa.getLengthOfInformationObjectAddress())};

        if (!hasError())
        {
            ioa.setAddress(value);
        }

        return *this;
    }

    template <typename T>
    IStream& operator>>(T& cpxxtime2a) requires (std::is_same_v<T, CP16Time2a> || std::is_same_v<T, CP24Time2a> ||
                                                 std::is_same_v<T, CP32Time2a> || std::is_same_v<T, CP56Time2a>)
    {
        return *this >> LiteBuffer{const_cast<uint8_t*>(getCPxxTime2aData<T>(cpxxtime2a)), getCPxxTime2aLength<T>(cpxxtime2a)};
    }

    IStream& operator>>(BitString32Value& value)
    {
        uint32_t bs32Value = 0;
        *this >> bs32Value;

        if (!hasError())
        {
            value = bs32Value;
        }

        return *this;
    }
};

}

