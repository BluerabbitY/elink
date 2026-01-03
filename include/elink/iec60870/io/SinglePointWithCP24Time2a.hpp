/***********************************************************************************
 * \file SinglePointWithCP24Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief SinglePointWithCP24Time2a
 * \date 2025-12-22 23:25:04
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

#include "elink/iec60870/io/SinglePointInformation.hpp"
#include "elink/iec60870/cpxxtime2a/CPxxTime2a.hpp"

namespace elink::iec60870 {

class SinglePointWithCP24Time2a : public InformationObject<SinglePointWithCP24Time2a, TypeID::M_SP_TA_1> {
public:
    SinglePointWithCP24Time2a()
        : siqM{0}, cp24time2aM{CP24Time2a::now()}
    {
    }

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    SinglePointWithCP24Time2a(const IOA ioa, const bool value, const Quality quality = Quality::GOOD, const CP24Time2a& cp24time2a = CP24Time2a::now())
        : InformationObject{ioa}, siqM{0}, cp24time2aM{cp24time2a}
    {
        setValue(value);
        setQuality(quality);
    }

    ~SinglePointWithCP24Time2a() = default;

    [[nodiscard]] bool getValue() const
    {
        return siqM & 0x01;
    }

    void setValue(const bool value)
    {
        siqM = (siqM & 0xfe) | value;
    }

    [[nodiscard]] Quality getQuality() const
    {
        return static_cast<Quality>(siqM & 0xf0);
    }

    void setQuality(const Quality quality)
    {
        siqM = (siqM & 0x0f) | static_cast<uint8_t>(quality);
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

    template <typename OSream>
    void serialize(OSream& stream) const
    {
        stream << siqM;
        stream << cp24time2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> siqM;
        stream >> cp24time2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(siqM) + internal::getCPxxTime2aLength(cp24time2aM);
    }

private:
    uint8_t siqM; // 4 bit quality + 1 bit bool
    CP24Time2a cp24time2aM;
};

}
