/***********************************************************************************
 * \file IStream.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-02 23:13:01
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

#include "elink/common/Type.hpp"
#include "elink/util/Utils.hpp"

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <cstddef>
#include <bitset>

namespace elink::details {

class IStream {
public:
    IStream(const uint8_t* buffer, const std::size_t size) : bufferM{buffer}, sizeM{size}, readPosM{0}, hasErrorM{false}
    {
        ELINK_ASSERT(buffer);
    }

    ~IStream() = default;

    template <typename T>
    std::enable_if_t<std::is_arithmetic_v<T>, IStream&> operator>>(T& value)
    {
        if (hasErrorM)
            return *this;

        if (readPosM + sizeof(T) <= sizeM)
        {
            if constexpr (sizeof(T) == 1 || std::endian::native == std::endian::little)
            {
                std::copy_n(bufferM + readPosM, sizeof(T), reinterpret_cast<uint8_t*>(&value));
            }
            else
            {
                std::reverse_copy(bufferM + readPosM, bufferM + readPosM + sizeof(T), reinterpret_cast<uint8_t*>(&value));
            }

            readPosM += sizeof(T);
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    template <typename T, typename OriginT = std::underlying_type_t<T> >
    std::enable_if_t<std::is_enum_v<T>, IStream&> operator>>(T& value)
    {
        if (hasErrorM)
            return *this;

        if (readPosM + sizeof(OriginT) <= sizeM)
        {
            if constexpr (sizeof(T) == 1 || std::endian::native == std::endian::little)
            {
                std::copy_n(bufferM + readPosM, sizeof(OriginT), reinterpret_cast<uint8_t*>(&value));
            }
            else
            {
                std::reverse_copy(bufferM + readPosM, bufferM + readPosM + sizeof(OriginT), reinterpret_cast<uint8_t*>(&value));
            }

            readPosM += sizeof(OriginT);
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    IStream& operator>>(LiteBuffer data)
    {
        if (hasErrorM && data.empty() && data.data() == nullptr)
            return *this;

        if (readPosM + data.size() <= sizeM)
        {
            std::copy_n(bufferM + readPosM, data.size(), data.begin());
            readPosM += data.size();
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    IStream& operator>>(std::bitset<32>& value)
    {
        uint32_t bs32Value = 0;
        *this >> bs32Value;

        if (!hasError())
        {
            value = bs32Value;
        }

        return *this;
    }

    IStream& operator>>(std::bitset<16>& value)
    {
        uint16_t bs16Value = 0;
        *this >> bs16Value;

        if (!hasError())
        {
            value = bs16Value;
        }

        return *this;
    }

    [[nodiscard]] const uint8_t* data() const
    {
        return bufferM;
    }

    [[nodiscard]] std::size_t size() const
    {
        return readPosM;
    }

    [[nodiscard]] std::size_t capacity() const
    {
        return sizeM;
    }

    void resetLength(const std::size_t size)
    {
        if (size <= sizeM)
        {
            readPosM = size;
        }
    }

    [[nodiscard]] bool hasError() const
    {
        return hasErrorM;
    }

    void acknowledgeError()
    {
        hasErrorM = false;
    }

protected:
    const uint8_t* bufferM;
    const std::size_t sizeM;
    std::size_t readPosM;
    bool hasErrorM;
};

}
