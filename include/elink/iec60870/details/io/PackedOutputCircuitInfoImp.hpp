/***********************************************************************************
 * \file PackedOutputCircuitInfoImp.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-07 16:58:51
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
#include "elink/iec60870/io/QualityDescriptorP.hpp"
#include "elink/iec60870/CPxxTime2a.hpp"

namespace elink::iec60870 {

/**
 * \brief Output circuit information (OCI) of protection equipment according to IEC 60870-5-101:2003 7.2.6.12
 */
enum class OutputCircuitInfo : uint8_t {
    OUTPUT_CI_GC  = 0x01, /* General command to output circuit */
    OUTPUT_CI_CL1 = 0x02, /* Command to output circuit phase L1 */
    OUTPUT_CI_CL2 = 0x04, /* Command to output circuit phase L2 */
    OUTPUT_CI_CL3 = 0x08, /* Command to output circuit phase L3 */
};

namespace details
{

template <typename inherit, TypeID typeID>
class PackedOutputCircuitInfoImp : public InformationObjectSerializable<inherit, typeID>
{
public:
    PackedOutputCircuitInfoImp()
    : ociM{OutputCircuitInfo::OUTPUT_CI_GC}, qdpM{QualityP::GOOD}, operatingTimeM{}
    {
    }

    PackedOutputCircuitInfoImp(const IOA ioa, const OutputCircuitInfo oci, const QualityP qdp, const CP16Time2a operatingTime)
    : InformationObjectSerializable<inherit, typeID>{ioa}, ociM{oci}, qdpM{qdp}, operatingTimeM{operatingTime}
    {
    }

    ~PackedOutputCircuitInfoImp() = default;

    [[nodiscard]] OutputCircuitInfo getOCI() const
    {
        return ociM;
    }

    void setOCI(const OutputCircuitInfo oci)
    {
        ociM = oci;
    }

    [[nodiscard]] QualityP getQuality() const
    {
        return qdpM;
    }

    void setQuality(const QualityP quality)
    {
        qdpM = quality;
    }

    [[nodiscard]] CP16Time2a getOperatingTime() const
    {
        return operatingTimeM;
    }

    void setOperatingTime(const CP16Time2a cp16time2a)
    {
        operatingTimeM = cp16time2a;
    }

protected:
    OutputCircuitInfo ociM;
    QualityP qdpM;
    CP16Time2a operatingTimeM;
};

}
}
