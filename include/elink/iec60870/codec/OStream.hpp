/***********************************************************************************
 * \file OStream.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief output stream
 * \date 2025-12-14 00:24:29
 * 
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <span>
#include <cstddef>

#include "elink/iec60870/io/InformationObjectAddress.hpp"
#include "elink/iec60870/cpxxtime2a/CPxxTime2a.hpp"

namespace elink::iec60870::internal {

class OStream {
public:
    OStream(uint8_t* buffer, const std::size_t size) : bufferM{buffer}, sizeM{size}, writePosM{0}, hasErrorM{false}
    {
        assert(buffer);
    }

    ~OStream() = default;

    template <typename T>
    std::enable_if_t<std::is_arithmetic_v<T>, OStream&> operator<<(T value)
    {
        if (hasErrorM)
            return *this;

        if (writePosM + sizeof(T) <= sizeM)
        {
            std::copy_n(reinterpret_cast<uint8_t*>(&value), sizeof(T), bufferM + writePosM);
            writePosM += sizeof(T);
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    template <typename T, typename OriginT = std::underlying_type_t<T> >
    std::enable_if_t<std::is_enum_v<T>, OStream&> operator<<(T value)
    {
        if (hasErrorM)
            return *this;

        if (writePosM + sizeof(OriginT) <= sizeM)
        {
            std::copy_n(reinterpret_cast<uint8_t*>(&value), sizeof(OriginT), bufferM + writePosM);
            writePosM += sizeof(OriginT);
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

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

    template <typename T>
    OStream& operator<<(std::span<T> data)
    {
        static_assert(std::is_same_v<const uint8_t, T> || std::is_same_v<uint8_t, T>,
                      "Only uint8_t or const uint8_t are supported");

        if (hasErrorM && data.empty() && data.data() == nullptr)
            return *this;

        if (writePosM + data.size() <= sizeM)
        {
            std::copy_n(data.data(), data.size(), bufferM + writePosM);
            writePosM += data.size();
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    [[nodiscard]] std::size_t writenBytes() const
    {
        return writePosM;
    }

    void erase()
    {
        writePosM = 0;
    }

    [[nodiscard]] bool hasError() const
    {
        return hasErrorM;
    }

    void acknowledgeError()
    {
        hasErrorM = false;
    }

private:
    uint8_t* bufferM;
    const std::size_t sizeM;
    std::size_t writePosM;
    bool hasErrorM;
};

}
