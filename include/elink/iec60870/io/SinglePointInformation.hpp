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
#include "elink/iec60870/io/QualityDescriptor.hpp"

namespace elink::iec60870 {

class SinglePointInformation : public InformationObject<SinglePointInformation, TypeID::M_SP_NA_1> {
public:
    SinglePointInformation()
        : siqM{0}
    {
    }

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    SinglePointInformation(const IOA ioa, const bool value, const Quality quality = Quality::GOOD)
        : InformationObject{ioa}, siqM{0}
    {
        setValue(value);
        setQuality(quality);
    }

    ~SinglePointInformation() = default;

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

protected:
    friend class InformationObject;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << siqM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> siqM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(siqM);
    }

private:
    /** 4 bit quality + 1 bit bool */
    uint8_t siqM;
};

}
