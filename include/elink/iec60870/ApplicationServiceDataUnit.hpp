/***********************************************************************************
 * \file ApplicationServiceDataUnit.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief Application Service Data Unit
 * \date 2026-01-29 23:36:11
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

#include "elink/common/details/codec/IStream.hpp"
#include "elink/iec60870/details/ApplicationServiceDataUnitImp.hpp"

namespace elink::iec60870
{

namespace cs101
{
using ApplicationServiceDataUnit = details::ApplicationServiceDataUnitImp<details::CS101_MAXUMUM_LENGTH_OF_ASDU>;
using ASDU = ApplicationServiceDataUnit;
}

namespace cs104
{
using ApplicationServiceDataUnit = details::ApplicationServiceDataUnitImp<details::CS104_MAXUMUM_LENGTH_OF_ASDU>;
using ASDU = ApplicationServiceDataUnit;
}

}
