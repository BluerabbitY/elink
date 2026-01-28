/***********************************************************************************
* \file StepPositionInformation.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-12-31 22:26:05
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

#include "elink/iec60870/io/details/StepPositionInformationImp.hpp"

namespace elink::iec60870 {

class StepPositionInformation final : public details::StepPositionInformationImp<StepPositionInformation, TypeID::M_ST_NA_1> {
public:
    StepPositionInformation() = default;

    // Valid Quality: GOOD, OVERFLOW, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    StepPositionInformation(const IOA ioa, const int value, const bool isTransient, const Quality quality = Quality::GOOD)
        : StepPositionInformationImp{ioa, value, isTransient, quality}
    {
        setValue(value);
        setTransient(isTransient);
    }

    ~StepPositionInformation() = default;

protected:
    ELINK_IO_OBJECT;

    template <typename OStream>
    void serialize(OStream& stream) const
    {
        stream << vtiM << qualityM;
    }

    template <typename IStream>
    void deserialize(IStream& stream)
    {
        stream >> vtiM >> qualityM;
    }

    [[nodiscard]] constexpr std::size_t payloadLength() const
    {
        return sizeof(vtiM) + sizeof(qualityM);
    }
};

}
