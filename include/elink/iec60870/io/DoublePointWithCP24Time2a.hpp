/***********************************************************************************
* \file DoublePointWithCP24Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-12-31 13:42:05
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

#include "elink/iec60870/io/DoublePointInformation.hpp"
#include "elink/iec60870/details/CPxxTime2aUtil.hpp"

namespace elink::iec60870 {

class DoublePointWithCP24Time2a final : public details::DoublePointInformationImp<DoublePointWithCP24Time2a, TypeID::M_DP_TA_1>, public details::CPxxTime2aUtil<CP24Time2a>
{
public:
    DoublePointWithCP24Time2a() = default;

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    DoublePointWithCP24Time2a(const IOA ioa, const DValue value, const Quality quality = Quality::GOOD, const CP24Time2a& cp24time2a = CP24Time2a::now())
        : DoublePointInformationImp{ioa, value, quality}, CPxxTime2aUtil{cp24time2a}
    {
    }

    ~DoublePointWithCP24Time2a() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << diqM;
        stream << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> diqM;
        stream >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(diqM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
