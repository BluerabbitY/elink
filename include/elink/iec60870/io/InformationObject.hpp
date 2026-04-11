/***********************************************************************************
 * \file InformationObject.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2025-11-26 00:28:02
 * 
 * \copyright Copyright (C) 2025-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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

    [[nodiscard]] IOA getAddress() const
    {
        return ioaM;
    }

    void setAddress(const IOA ioa)
    {
        ioaM = ioa;
    }

    void resetAddressLengthStrategy(const IOAByteLength strategy)
    {
        ioaM.resize(strategy);
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
