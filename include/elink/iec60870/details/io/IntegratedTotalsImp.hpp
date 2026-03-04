/***********************************************************************************
 * \file IntegratedTotalsImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-02 19:51:20
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "InformationObjectSerializable.hpp"
#include "elink/iec60870/BinaryCounterReading.hpp"

namespace elink::iec60870::details
{

template <typename inherit, TypeID typeID>
class IntegratedTotalsImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    IntegratedTotalsImp() = default;

    /**
     * \brief Create a new instance of IntegratedTotals information object
     *
     * For message type: M_IT_NA_1 (15)
     *
     * \param ioa Information object address
     * \param bcr binary counter reading value and state
     *
     */
    IntegratedTotalsImp(const IOA ioa, const BinaryCounterReading& bcr)
    : InformationObjectSerializable<inherit, typeID>{ioa}, bcrM{bcr}
    {
    }

    ~IntegratedTotalsImp() = default;

    [[nodiscard]] const BinaryCounterReading &getBCR() const
    {
        return bcrM;
    }

    void setBCR(const BinaryCounterReading& bcr)
    {
        bcrM = bcr;
    }

protected:
    BinaryCounterReading bcrM;
};

}
