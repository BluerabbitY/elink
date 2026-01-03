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

#include <algorithm>

#include "elink/iec60870/io/StepPositionInformation.hpp"
#include "elink/iec60870/cpxxtime2a/CPxxTime2a.hpp"

namespace elink::iec60870 {

class StepPositionWithCP24Time2a : public InformationObject<StepPositionWithCP24Time2a, TypeID::M_ST_TA_1> {
public:
    StepPositionWithCP24Time2a()
        : vtiM{0}, qualityM{static_cast<uint8_t>(Quality::GOOD)}, cp24time2aM{CP24Time2a::now()}
    {
    }

    // Valid Quality: GOOD, OVERFLOW, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    StepPositionWithCP24Time2a(const IOA ioa, const int value, const bool isTransient, const Quality quality = Quality::GOOD, const CP24Time2a& cp24time2a = CP24Time2a::now())
        : InformationObject{ioa}, vtiM{0}, qualityM{static_cast<uint8_t>(quality)}, cp24time2aM{cp24time2a}
    {
        setValue(value);
        setTransient(isTransient);
    }

    ~StepPositionWithCP24Time2a() = default;

    [[nodiscard]] int getValue() const
    {
        int value = vtiM & 0x7f;

        if (value > upLimit)
            value -= offset;

        return value;
    }

    void setValue(const int value)
    {
        vtiM = std::clamp(value, lowLimit, upLimit);

        if (vtiM < 0)
            vtiM += offset;
    }

    [[nodiscard]] bool isTransient() const
    {
        return (vtiM & 0x80) == 0x80;
    }

    void setTransient(const bool isTransient)
    {
        isTransient ? vtiM |= 0x80 : vtiM &= 0x7f;
    }

    [[nodiscard]] Quality getQuality() const
    {
        return static_cast<Quality>(qualityM);
    }

    void setQuality(const Quality quality)
    {
        qualityM = static_cast<uint8_t>(quality) & 0xf1;
    }

    [[nodiscard]] CP24Time2a& getTimestamp()
    {
        return cp24time2aM;
    }

    void setTimestamp(const CP24Time2a& cp24time2a = CP24Time2a::now())
    {
        cp24time2aM = cp24time2a;
    }

protected:
    friend class InformationObject;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << vtiM;
        stream << qualityM;
        stream << cp24time2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> vtiM;
        stream >> qualityM;
        stream >> cp24time2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(vtiM) + sizeof(qualityM) + internal::getCPxxTime2aLength(cp24time2aM);
    }

private:
    static constexpr int upLimit = 63;
    static constexpr int lowLimit = -64;
    static constexpr int offset = 128;

    uint8_t vtiM;
    uint8_t qualityM;
    CP24Time2a cp24time2aM;
};

}
