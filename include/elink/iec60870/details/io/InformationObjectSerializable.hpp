/***********************************************************************************
 * \file InformationObjectSerializable.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-26 00:22:52
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
#include "elink/iec60870/io/InformationObjectTypeID.h"

#include <memory>

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class InformationObjectSerializable : public InformationObject {
protected:
    explicit InformationObjectSerializable(const IOA ioa) : InformationObject{ioa, typeID}
    {
    }

    InformationObjectSerializable() : InformationObject{typeID}
    {
    }

public:
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

    using Ptr = std::shared_ptr<inherit>;

    using SerializePtr = std::shared_ptr<InformationObjectSerializable>;

    static constexpr TypeID IDENT_T = typeID;
};

}

#ifndef ELINK_IO_OBJECT
#define ELINK_IO_OBJECT friend class InformationObjectSerializable
#else
#error "ELINK_IO_OBJECT already defined"
#endif
