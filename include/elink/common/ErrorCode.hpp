/***********************************************************************************
 * \file ErrorCode.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 00:17:46
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

#include <cstdint>

namespace elink
{

/**
 * @brief Unified error codes for the communication library
 *
 * Error codes are categorized by type using numeric ranges:
 * - 0: Success
 */
enum class ErrorCode : uint32_t {
    // Success
    Success = 0,

    Timeout,
};

}
