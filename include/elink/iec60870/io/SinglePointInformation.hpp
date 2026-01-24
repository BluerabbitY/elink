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

#include "elink/iec60870/io/details/SinglePointInformationImp.hpp"

namespace elink::iec60870 {

class SinglePointInformation : public details::SinglePointInformationImp<SinglePointInformation, TypeID::M_SP_NA_1> {
public:
    SinglePointInformation() = default;

    // Valid Quality: GOOD, BLOCKED, SUBSTITUTED, NON_TOPICAL, INVALID
    SinglePointInformation(const IOA ioa, const bool value, const Quality quality = Quality::GOOD)
        : SinglePointInformationImp{ioa, value, quality}
    {
    }

    ~SinglePointInformation() = default;

protected:
    ELINK_IO_OBJECT;

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
};

}
