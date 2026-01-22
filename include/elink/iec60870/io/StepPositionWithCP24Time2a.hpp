/***********************************************************************************
 * \file StepPositionWithCP24Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2026-01-03 11:12:32
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

#include "elink/iec60870/io/StepPositionInformation.hpp"
#include "elink/iec60870/details/CPxxTime2aUtil.hpp"

namespace elink::iec60870 {

class StepPositionWithCP24Time2a : public details::StepPositionInformationImp<StepPositionWithCP24Time2a, TypeID::M_ST_TA_1>, public details::CPxxTime2aUtil<CP24Time2a>
{
public:
    StepPositionWithCP24Time2a() = default;

    // Valid Quality: GOOD, OVERFLOW, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    StepPositionWithCP24Time2a(const IOA ioa, const int value, const bool isTransient, const Quality quality = Quality::GOOD, const CP24Time2a& cp24time2a = CP24Time2a::now())
        : StepPositionInformationImp{ioa, value, isTransient, quality}, CPxxTime2aUtil{cp24time2a}
    {
        setValue(value);
        setTransient(isTransient);
    }

    ~StepPositionWithCP24Time2a() = default;

protected:
    friend class InformationObject;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << vtiM;
        stream << qualityM;
        stream << cpxxtime2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> vtiM;
        stream >> qualityM;
        stream >> cpxxtime2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(vtiM) + sizeof(qualityM) + details::getCPxxTime2aLength(cpxxtime2aM);
    }
};

}
