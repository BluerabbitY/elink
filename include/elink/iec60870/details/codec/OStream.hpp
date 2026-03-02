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
#include "elink/iec60870/BinaryCounterReading.hpp"

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
        if (hasErrorM)
            return *this;

        if (const auto size = ioa.getLengthOfInformationObjectAddress(); writePosM + size <= sizeM)
        {
            auto value = ioa.address();
            std::copy_n(reinterpret_cast<uint8_t*>(&value), size, bufferM + writePosM);
            writePosM += size;
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    template <typename T>
    OStream& operator<<(const T& cpxxtime2a) requires (std::is_same_v<T, CP16Time2a> || std::is_same_v<T, CP24Time2a> ||
                                                       std::is_same_v<T, CP32Time2a> || std::is_same_v<T, CP56Time2a>)
    {
        if (hasErrorM)
            return *this;

        if (const auto size = getCPxxTime2aLength<T>(cpxxtime2a); writePosM + size <= sizeM)
        {
            std::copy_n(getCPxxTime2aData<T>(cpxxtime2a), size, bufferM + writePosM);
            writePosM += size;
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    OStream& operator<<(const BitString32Value& value)
    {
        if (hasErrorM)
            return *this;

        if (writePosM + sizeof(uint32_t) <= sizeM)
        {
            uint32_t bs32Value = value.to_ulong();
            const auto ita = reinterpret_cast<uint8_t*>(&bs32Value);

            if constexpr (std::endian::native == std::endian::little)
            {
                std::copy_n(ita, sizeof(bs32Value), bufferM + writePosM);
            }
            else
            {
                std::reverse_copy(ita, ita + sizeof(bs32Value), bufferM + writePosM);
            }

            writePosM += sizeof(bs32Value);
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    OStream& operator<<(const BinaryCounterReading& value)
    {
        if (hasErrorM)
            return *this;

        if (writePosM + sizeof(uint32_t) <= sizeM)
        {
            *this << value.valueM << value.seqM;
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }
};

}
