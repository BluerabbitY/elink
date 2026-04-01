/***********************************************************************************
 * \file Result.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 00:22:03
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

#include "elink/common/ErrorCode.hpp"

#include <string>

namespace elink
{

template <typename T>
struct Result
{
    ErrorCode code;                ///< The error code
    std::string message;           ///< Human-readable error message
    int32_t systemErrorCode = 0;   ///< System native error code (e.g., errno, GetLastError())
    T value;

    bool isOk() const { return code == ErrorCode::Success; }
    bool isErr() const { return code != ErrorCode::Success; }
};

template <>
struct Result<void>
{
    ErrorCode code;                ///< The error code
    std::string message;           ///< Human-readable error message
    int32_t systemErrorCode = 0;   ///< System native error code (e.g., errno, GetLastError())

    bool isOk() const { return code == ErrorCode::Success; }
    bool isErr() const { return code != ErrorCode::Success; }
};

}
