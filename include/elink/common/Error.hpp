/***********************************************************************************
 * \file Error.hpp
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
#include <string>

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
};

/**
 * @brief Error information structure
 *
 * Contains detailed error information including the error code,
 * a human-readable message, and the system-specific error code.
 */
struct Error {
    ErrorCode code;                ///< The error code
    std::string message;           ///< Human-readable error message
    int32_t systemErrorCode = 0;   ///< System native error code (e.g., errno, GetLastError())

    /**
     * @brief Default constructor
     */
    Error() : code(ErrorCode::Success), message{}, systemErrorCode(0) {}

    /**
     * @brief Construct an error with code and message
     * @param code The error code
     * @param message The error message
     * @param systemErrorCode Optional system error code
     */
    Error(const ErrorCode code, const std::string &message, const int32_t systemErrorCode = 0)
        : code{code}
        , message{message}
        , systemErrorCode{systemErrorCode}
    {}
};

}
