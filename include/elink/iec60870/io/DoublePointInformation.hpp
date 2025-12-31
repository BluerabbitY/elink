/***********************************************************************************
 * \file DoublePointInformation.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief DoublePointInformation
 * \date 2025-12-24 22:48:33
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

namespace elink::iec60870
{

class DoublePointInformation : public InformationObject<DoublePointInformation, TypeID::M_DP_NA_1>
{
public:
    // clang-format off
    enum QualityDescriptor : uint8_t {
        GOOD        = 0x00,
        BLOCKED     = 0x10,
        SUBSTITUTED = 0x20,
        NON_TOPICAL = 0x40,
        INVALID     = 0x80,
    };

    enum DoublePointValue{
        INTERMEDIATE = 0,
        OFF = 1,
        ON = 2,
        INDETERMINATE = 3
     };
    // clang-format on

    DoublePointInformation(const IOA ioa, const DoublePointValue value, const QualityDescriptor quality = GOOD)
        : InformationObject{ioa}, diqM{0}
    {
        setValue(value);
        setQuality(quality);
    }

    ~DoublePointInformation() = default;

    [[nodiscard]] DoublePointValue getValue() const
    {
        return static_cast<DoublePointValue>(diqM & 0x03);
    }

    void setValue(const DoublePointValue value)
    {
        diqM = (diqM & 0xfc) | value;
    }

    [[nodiscard]] QualityDescriptor getQuality() const
    {
        return static_cast<QualityDescriptor>(diqM & 0xf0);
    }

    void setQuality(const QualityDescriptor value)
    {
        diqM = (diqM & 0x0f) | static_cast<uint8_t>(value);
    }

protected:
    friend class InformationObject;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << diqM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> diqM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(diqM);
    }

private:
    uint8_t diqM;
};

using DQuality = DoublePointInformation::QualityDescriptor;

using DValue = DoublePointInformation::DoublePointValue;

constexpr DQuality operator|(const DQuality left, const DQuality right) noexcept
{
    using U = std::underlying_type_t<DQuality>;
    return static_cast<DQuality>(static_cast<U>(left) | static_cast<U>(right));
}

inline bool operator&(const DQuality left, const DQuality right) noexcept
{
    using U = std::underlying_type_t<DQuality>;
    return (static_cast<U>(left) & static_cast<U>(right)) != 0;
}

} // namespace 
