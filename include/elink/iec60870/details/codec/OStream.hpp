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

#include "elink/common/details/codec/OStream.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"
#include "elink/iec60870/io/InformationObjectAddress.hpp"

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
};

}
