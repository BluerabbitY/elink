/***********************************************************************************
 * \file SinglePointInformation.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief SinglePointInformation (TypeId: M_SP_NA_1)
 * \date 2025-12-16 21:46:53
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

#include "elink/iec60870/io/InformationObject.hpp"
#include "elink/iec60870/io/InformationObjectTypeID.h"

namespace elink::iec60870 {

class SinglePointInformation : public InformationObject<SinglePointInformation, TypeID::M_SP_NA_1> {
public:
    // clang-format off
    enum QualityDescriptor : uint8_t {
        GOOD        = 0x00,
        BLOCKED     = 0x10,
        SUBSTITUTED = 0x20,
        NON_TOPICAL = 0x40,
        INVALID     = 0x80,
    };
    // clang-format on

    SinglePointInformation(const IOA ioa, const bool value, const QualityDescriptor quality = GOOD)
        : InformationObject{ioa}, valueM{0}
    {
        setValue(value);
        setQuality(quality);
    }

    ~SinglePointInformation() = default;

    void setValue(const bool value)
    {
        value ? (valueM |= 0x01) : (valueM &= 0xfe);
    }

    [[nodiscard]] bool getValue() const
    {
        return valueM & 0x01;
    }

    void setQuality(const QualityDescriptor quality)
    {
        valueM |= (quality & 0xf0);
    }

    [[nodiscard]] QualityDescriptor getQuality() const
    {
        return static_cast<QualityDescriptor>(valueM & 0xf0);
    }

protected:
    friend class InformationObject;

    template <typename OSream>
    void serialize(OSream& stream) const
    {
        stream << valueM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> valueM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(valueM);
    }

private:
    /** 4 bit quality + 1 bit bool */
    uint8_t valueM;
};

using SIP = SinglePointInformation::QualityDescriptor;

constexpr SIP operator|(const SIP left, const SIP right) noexcept
{
    using U = std::underlying_type_t<SIP>;
    return static_cast<SIP>(static_cast<U>(left) | static_cast<U>(right));
}

inline bool operator&(const SIP left, const SIP right) noexcept
{
    using U = std::underlying_type_t<SIP>;
    return (static_cast<U>(left) & static_cast<U>(right)) != 0;
}

}
