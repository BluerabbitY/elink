/***********************************************************************************
 * \file DoublePointInformationImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-22 23:51:24
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

namespace elink::iec60870
{

namespace details
{

// clang-format off
enum DoublePointValue {
    INTERMEDIATE  = 0,
    OFF           = 1,
    ON            = 2,
    INDETERMINATE = 3,
 };
// clang-format on

template <typename inherit, TypeID typeID>
class DoublePointInformationImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    DoublePointInformationImp()
        : diqM{0}
    {
    }

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    DoublePointInformationImp(const IOA ioa, const DoublePointValue value, const Quality quality)
        : InformationObjectSerializable<inherit, typeID>{ioa}, diqM{0}
    {
        setValue(value);
        setQuality(quality);
    }

    ~DoublePointInformationImp() = default;

    [[nodiscard]] DoublePointValue getValue() const
    {
        return static_cast<DoublePointValue>(diqM & 0x03);
    }

    void setValue(const DoublePointValue value)
    {
        diqM = (diqM & 0xfc) | value;
    }

    [[nodiscard]] Quality getQuality() const
    {
        return static_cast<Quality>(diqM & 0xf0);
    }

    void setQuality(const Quality value)
    {
        diqM = (diqM & 0x0f) | static_cast<uint8_t>(value);
    }

protected:
    uint8_t diqM;
};

}

using DValue = details::DoublePointValue;

}
