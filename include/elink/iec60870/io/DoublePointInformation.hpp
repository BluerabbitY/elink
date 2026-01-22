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

#include "elink/iec60870/io/details/DoublePointInformationImp.hpp"

namespace elink::iec60870
{

using DValue = details::DoublePointValue;

class DoublePointInformation : public details::DoublePointInformationImp<DoublePointInformation, TypeID::M_DP_NA_1>
{
public:
    DoublePointInformation() = default;

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    DoublePointInformation(const IOA ioa, const DValue value, const Quality quality = Quality::GOOD)
        : DoublePointInformationImp{ioa, value, quality}
    {
    }

    ~DoublePointInformation() = default;

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
};

}
