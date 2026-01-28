/***********************************************************************************
 * \file OStream.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2026-01-02 23:26:57
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

#include "elink/common/Type.hpp"

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <cstddef>

namespace elink::details {

template <typename inherit>
class OStream {
public:
    OStream(uint8_t* buffer, const std::size_t size) : bufferM{buffer}, sizeM{size}, writePosM{0}, hasErrorM{false}
    {
        assert(buffer);
    }

    ~OStream() = default;

    template <typename T>
    std::enable_if_t<std::is_arithmetic_v<T>, inherit&> operator<<(T value)
    {
        if (hasErrorM)
            return static_cast<inherit&>(*this);

        if (writePosM + sizeof(T) <= sizeM)
        {
            std::copy_n(reinterpret_cast<uint8_t*>(&value), sizeof(T), bufferM + writePosM);
            writePosM += sizeof(T);
        }
        else
        {
            hasErrorM = true;
        }

        return static_cast<inherit&>(*this);
    }

    template <typename T, typename OriginT = std::underlying_type_t<T> >
    std::enable_if_t<std::is_enum_v<T>, inherit&> operator<<(T value)
    {
        if (hasErrorM)
            return static_cast<inherit&>(*this);

        if (writePosM + sizeof(OriginT) <= sizeM)
        {
            std::copy_n(reinterpret_cast<uint8_t*>(&value), sizeof(OriginT), bufferM + writePosM);
            writePosM += sizeof(OriginT);
        }
        else
        {
            hasErrorM = true;
        }

        return static_cast<inherit&>(*this);
    }

    inherit& operator<<(const LiteBufferView data)
    {
        if (hasErrorM && data.empty() && data.data() == nullptr)
            return static_cast<inherit&>(*this);

        if (writePosM + data.size() <= sizeM)
        {
            std::copy_n(data.data(), data.size(), bufferM + writePosM);
            writePosM += data.size();
        }
        else
        {
            hasErrorM = true;
        }

        return static_cast<inherit&>(*this);
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

protected:
    uint8_t* bufferM;
    const std::size_t sizeM;
    std::size_t writePosM;
    bool hasErrorM;
};

}
