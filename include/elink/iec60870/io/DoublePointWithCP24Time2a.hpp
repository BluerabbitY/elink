/***********************************************************************************
* \file DoublePointWithCP24Time2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-12-31 13:42:05
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

#include "elink/iec60870/io/DoublePointInformation.hpp"
#include "elink/iec60870/cpxxtime2a/CPxxTime2a.hpp"

namespace elink::iec60870 {

class DoublePointWithCP24Time2a : public InformationObject<DoublePointWithCP24Time2a, TypeID::M_DP_TA_1>
{
public:
    DoublePointWithCP24Time2a()
        : diqM{0}, cp24time2aM{CP24Time2a::now()}
    {
    }

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    DoublePointWithCP24Time2a(const IOA ioa, const DValue value, const Quality quality = Quality::GOOD, const CP24Time2a& cp24time2a = CP24Time2a::now())
        : InformationObject{ioa}, diqM{0}, cp24time2aM{cp24time2a}
    {
        setValue(value);
        setQuality(quality);
    }

    ~DoublePointWithCP24Time2a() = default;

    [[nodiscard]] DValue getValue() const
    {
        return static_cast<DValue>(diqM & 0x03);
    }

    void setValue(const DValue value)
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
        stream << diqM;
        stream << cp24time2aM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> diqM;
        stream >> cp24time2aM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(diqM) + internal::getCPxxTime2aLength(cp24time2aM);
    }

private:
    uint8_t diqM;
    CP24Time2a cp24time2aM;
};

}
