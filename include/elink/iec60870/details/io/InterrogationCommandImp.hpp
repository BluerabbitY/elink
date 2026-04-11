/***********************************************************************************
 * \file InterrogationCommandImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-11 15:43:37
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

#include "elink/iec60870/details/io/InformationObjectSerializable.hpp"

namespace elink::iec60870
{

/**
 * \brief Qualifier of interrogation (QOI) according to IEC 60870-5-101:2003 7.2.6.22
 */
enum class QualifierOfInterrogation : uint8_t
{
    STATION  = 20,
    GROUP_01 = 21,
    GROUP_02 = 22,
    GROUP_03 = 23,
    GROUP_04 = 24,
    GROUP_05 = 25,
    GROUP_06 = 26,
    GROUP_07 = 27,
    GROUP_08 = 28,
    GROUP_09 = 29,
    GROUP_10 = 30,
    GROUP_11 = 31,
    GROUP_12 = 32,
    GROUP_13 = 33,
    GROUP_14 = 34,
    GROUP_15 = 35,
    GROUP_16 = 36,
};

using QOI = QualifierOfInterrogation;

namespace details
{

template <typename inherit, TypeID typeID>
class InterrogationCommandImp : public InformationObjectSerializable<inherit, typeID> {
public:
    InterrogationCommandImp()
    : qoiM{QOI::STATION}
    {
    }

    InterrogationCommandImp(const IOA ioa, const QualifierOfInterrogation qoi)
    : InformationObjectSerializable<inherit, typeID>{ioa}, qoiM{qoi}
    {
    }

    ~InterrogationCommandImp() = default;

    [[nodiscard]] QualifierOfInterrogation getQOI() const
    {
        return qoiM;
    }

    void setQOI(const QualifierOfInterrogation qoi)
    {
        qoiM = qoi;
    }

protected:
    QualifierOfInterrogation qoiM;
};

}
}
