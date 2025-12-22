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
    SinglePointWithCP24Time2a(const IOA ioa, const bool value, const SIP quality, const CP24Time2a& cp24time2a)
        : InformationObject{ioa}, valueM{0}, cp24time2aM{cp24time2a}
    {
        setValue(value);
        setQuality(quality);
    }

    ~SinglePointWithCP24Time2a() = default;

    void setValue(const bool value)
    {
        value ? (valueM |= 0x01) : (valueM &= 0xfe);
    }

    [[nodiscard]] bool getValue() const
    {
        return valueM & 0x01;
    }

    void setQuality(const SIP quality)
    {
        valueM |= (quality & 0xf0);
    }

    [[nodiscard]] uint8_t getQuality() const
    {
        return valueM & 0xf0;
    }

    void setTimestamp(const CP24Time2a& cp24time2a)
    {
        cp24time2aM = cp24time2a;
    }

    [[nodiscard]] CP24Time2a& getTimestamp()
    {
        return cp24time2aM;
    }

protected:
    friend class InformationObject;

    template <typename OSream>
    void serialize(OSream& stream) const
    {
        stream << valueM;
        stream << cp24time2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM;
        stream >> cp24time2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM) + internal::getCPxxTime2aLength(cp24time2aM);
    }

private:
    uint8_t valueM; // 4 bit quality + 1 bit bool
    CP24Time2a cp24time2aM;
};

}
