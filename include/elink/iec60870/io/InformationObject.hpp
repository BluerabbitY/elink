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

namespace elink::iec60870 {

class InformationObject {
protected:
    explicit InformationObject(const IOA ioa, const TypeID typeID) : ioaM{ioa}, typeIDM{typeID}
    {
    }

    explicit InformationObject(const TypeID typeID) : typeIDM{typeID}
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

    using OriginPtr = std::shared_ptr<InformationObject>;

protected:
    InformationObjectAddress ioaM;
    const InformationObjectTypeID typeIDM;
};

}
