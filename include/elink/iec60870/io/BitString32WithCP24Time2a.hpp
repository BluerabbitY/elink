/***********************************************************************************
 * \file Bitstring32WithCP24Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-25 21:51:11
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
#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace elink::iec60870
{

class BitString32WithCP24Time2a final : public details::BitString32Imp<BitString32WithCP24Time2a, TypeID::M_BO_TA_1>, public details::CPxxTime2aUtil<CP24Time2a>
{
public:
    BitString32WithCP24Time2a() = default;

    BitString32WithCP24Time2a(const IOA ioa, const uint32_t value, const QualityDescriptor quality = Quality::GOOD, const CP24Time2a& cp24time2a = CP24Time2a::now())
     : BitString32Imp{ioa, value, quality}, CPxxTime2aUtil{cp24time2a}
    {
    }

    ~BitString32WithCP24Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << valueM << qualityM << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM >> qualityM >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return valueM.size() / 8 + sizeof(qualityM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}