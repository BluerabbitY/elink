/***********************************************************************************
 * \file SinglePointInformationImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-22 23:37:06
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

#include "elink/iec60870/io/InformationObject.hpp"
#include "elink/iec60870/io/QualityDescriptor.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class SinglePointInformationImp : public InformationObject<inherit, typeID> {
public:
    SinglePointInformationImp()
        : siqM{0}
    {
    }

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    SinglePointInformationImp(const IOA ioa, const bool value, const Quality quality)
        : InformationObject<inherit, typeID>{ioa}, siqM{0}
    {
        setValue(value);
        setQuality(quality);
    }

    ~SinglePointInformationImp() = default;

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
    /** 4 bit quality + 1 bit bool */
    uint8_t siqM;
};

}
