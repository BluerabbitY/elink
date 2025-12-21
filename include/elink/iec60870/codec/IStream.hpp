/***********************************************************************************
 * \file IStream.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief input stream
 * \date 2025-12-17 23:07:36
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

class IStream {
public:
    IStream(const uint8_t* buffer, const std::size_t size) : bufferM{buffer}, sizeM{size}, readPosM{0}, hasErrorM{false}
    {
        assert(buffer);
    }

    ~IStream() = default;

    template <typename T>
    std::enable_if_t<std::is_arithmetic_v<T>, IStream&> operator>>(T& value)
    {
        if (hasErrorM)
            return *this;

        if (readPosM + sizeof(T) <= sizeM)
        {
            std::copy_n(bufferM + readPosM, sizeof(T), reinterpret_cast<uint8_t*>(&value));
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
            std::copy_n(bufferM + readPosM, sizeof(OriginT), reinterpret_cast<uint8_t*>(&value));
            readPosM += sizeof(OriginT);
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    IStream& operator>>(IOA& ioa)
    {
        if (hasErrorM)
            return *this;

        if (const auto size = ioa.getLengthOfInformationObjectAddress(); readPosM + size <= sizeM)
        {
            int value = 0;
            std::copy_n(bufferM + readPosM, size, reinterpret_cast<uint8_t*>(&value));
            ioa.setAddress(value);
            readPosM += size;
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    template <typename T>
    IStream& operator>>(T& cpxxtime2a) requires (std::is_same_v<T, CP16Time2a> || std::is_same_v<T, CP24Time2a> ||
                                                 std::is_same_v<T, CP32Time2a> || std::is_same_v<T, CP56Time2a>)
    {
        if (hasErrorM)
            return *this;

        if (const auto size = getCPxxTime2aLength<T>(cpxxtime2a); readPosM + size <= sizeM)
        {
            std::copy_n(bufferM + readPosM, size, const_cast<uint8_t*>(getCPxxTime2aData<T>(cpxxtime2a)));
            readPosM += size;
        }
        else
        {
            hasErrorM = true;
        }

        return *this;
    }

    template <typename T>
    IStream& operator>>(std::span<T>& data)
    {
        static_assert(std::is_same_v<const uint8_t, T> || std::is_same_v<uint8_t, T>,
                      "Only uint8_t or const uint8_t are supported");

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

    [[nodiscard]] std::size_t readBytes() const
    {
        return readPosM;
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
    const uint8_t* bufferM;
    const std::size_t sizeM;
    std::size_t readPosM;
    bool hasErrorM;
};

}

