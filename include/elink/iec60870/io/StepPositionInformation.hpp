/***********************************************************************************
* \file StepPositionInformation.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-12-31 22:26:05
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

#include "elink/iec60870/io/InformationObject.hpp"
#include "elink/iec60870/io/QualityDescriptor.hpp"

namespace elink::iec60870 {

class StepPositionInformation : public InformationObject<StepPositionInformation, TypeID::M_ST_NA_1> {
public:
    StepPositionInformation()
        : vtiM{0}, qualityM{static_cast<uint8_t>(Quality::GOOD)}
    {
    }

    // Valid Quality: GOOD, OVERFLOW, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    StepPositionInformation(const IOA ioa, const int value, const bool isTransient, const Quality quality = Quality::GOOD)
        : InformationObject{ioa}, vtiM{0}, qualityM{static_cast<uint8_t>(quality)}
    {
        setValue(value);
        setTransient(isTransient);
    }

    ~StepPositionInformation() = default;

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

protected:
    friend class InformationObject;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << vtiM;
        stream << qualityM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> vtiM;
        stream >> qualityM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(vtiM) + sizeof(qualityM);
    }

private:
    static constexpr int upLimit = 63;
    static constexpr int lowLimit = -64;
    static constexpr int offset = 128;

    uint8_t vtiM;
    uint8_t qualityM;
};

}
