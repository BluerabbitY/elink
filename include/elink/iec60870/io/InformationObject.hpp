/***********************************************************************************
 * \file InformationObject.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2025-11-26 00:28:02
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

#include "elink/iec60870/io/InformationObjectAddress.hpp"
#include "elink/iec60870/io/InformationObjectTypeID.h"

#include <memory>

#define ELINK_IO_OBJECT friend class InformationObject

namespace elink::iec60870 {

template <typename inherit, TypeID typeID>
class InformationObject {
protected:
    explicit InformationObject(const IOA ioa) : ioaM{ioa}, typeIDM{typeID}
    {
    }

    InformationObject() : typeIDM{typeID}
    {
    }

public:
    ~InformationObject() = default;

    [[nodiscard]] IOA getInformationObjectAddress() const
    {
        return ioaM;
    }

    void setInformationObjectAddress(const IOA ioa)
    {
        ioaM = ioa;
    }

    [[nodiscard]] constexpr TypeID getTypeID() const
    {
        return typeIDM;
    }

    template <typename OStream>
    bool serialize(OStream& stream, const bool isSequence) const
    {
        if (!isSequence)
        {
            stream << ioaM;
        }

        static_cast<inherit const*>(this)->serialize(stream);

        if (stream.hasError())
        {
            stream.acknowledgeError();
            return false;
        }

        return true;
    }

    template <typename IStream>
    bool deserialize(IStream& stream, const bool isSequence)
    {
        if (!isSequence)
        {
            stream >> ioaM;
        }

        static_cast<inherit*>(this)->deserialize(stream);

        if (stream.hasError())
        {
            stream.acknowledgeError();
            return false;
        }

        return true;
    }

    [[nodiscard]] std::size_t size() const
    {
        return ioaM.getLengthOfInformationObjectAddress() + static_cast<const inherit*>(this)->payloadLength();
    }

    using OriginType = InformationObject;

    using Ptr = std::shared_ptr<inherit>;

    using OriginPtr = std::shared_ptr<OriginType>;

private:
    InformationObjectAddress ioaM;
    const InformationObjectTypeID typeIDM;
};

}
