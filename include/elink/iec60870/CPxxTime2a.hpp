/***********************************************************************************
 * \file CPXXTime2A.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2025-12-20 10:12:15
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

#include "details/cpxxtime2a/CPxxTime2aImp.hpp"

namespace elink::iec60870 {

using CP16Time2a = details::CPxxTime2aImp<details::CP16Time2aTag>;
using CP24Time2a = details::CPxxTime2aImp<details::CP24Time2aTag>;
using CP32Time2a = details::CPxxTime2aImp<details::CP32Time2aTag>;
using CP56Time2a = details::CPxxTime2aImp<details::CP56Time2aTag>;

}
