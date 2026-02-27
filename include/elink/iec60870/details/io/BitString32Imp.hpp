/***********************************************************************************
 * \file BitString32Imp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-25 18:42:48
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

#include "InformationObjectSerializable.hpp"
#include "elink/iec60870/io/QualityDescriptor.hpp"

#include <bitset>

namespace elink::iec60870
{

using BitString32Value = std::bitset<32>;

namespace details {

template <typename inherit, TypeID typeID>
class BitString32Imp : public InformationObjectSerializable<inherit, typeID>
{
public:
    BitString32Imp() : valueM{0x00000000}, qualityM{Quality::GOOD}
    {
    }

    BitString32Imp(const IOA ioa, const uint32_t value, const Quality quality)
     : InformationObjectSerializable<inherit, typeID>{ioa}, valueM{value}, qualityM{quality}
    {
    }

    ~BitString32Imp() = default;

    [[nodiscard]] const BitString32Value &getValue() const
    {
        return valueM;
    }

    void setValue(const BitString32Value& value)
    {
        valueM = value;
    }

    [[nodiscard]] bool getValue(const std::size_t pos) const
    {
        return valueM.test(std::clamp<size_t>(pos, 0, 31));
    }

    void setValue(const std::size_t pos, const bool value)
    {
        valueM.set(std::clamp<size_t>(pos, 0, 31), value);
    }

    [[nodiscard]] Quality getQuality() const
    {
        return qualityM;
    }

    void setQuality(const QualityDescriptor quality)
    {
        qualityM = quality;
    }

protected:
    BitString32Value valueM;
    QualityDescriptor qualityM;
};

}
}
