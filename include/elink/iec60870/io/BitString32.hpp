/***********************************************************************************
 * \file BitString32.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-25 20:01:13
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

#include "elink/iec60870/details/io/BitString32Imp.hpp"

namespace elink::iec60870
{

class BitString32 final : public details::BitString32Imp<BitString32, TypeID::M_BO_NA_1>
{
public:
    BitString32() = default;

    BitString32(const IOA ioa, const uint32_t value, const Quality quality = Quality::GOOD)
     : BitString32Imp{ioa, value, quality}
    {
    }

    ~BitString32() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM << qualityM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM >> qualityM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return valueM.size() / 8 + sizeof(qualityM);
    }
};

}
