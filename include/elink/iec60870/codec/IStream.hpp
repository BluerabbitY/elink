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

#include "../../common/codec/IStreamCommon.hpp"
#include "elink/iec60870/cpxxtime2a/CPxxTime2a.hpp"
#include "elink/iec60870/io/InformationObjectAddress.hpp"

namespace elink::iec60870::internal {

class IStream : public common::internal::IStreamCommon {
public:
    IStream(const uint8_t* buffer, const std::size_t size) : IStreamCommon{buffer, size}
    {
    }

    ~IStream() = default;

    using IStreamCommon::operator>>;

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
};

}

