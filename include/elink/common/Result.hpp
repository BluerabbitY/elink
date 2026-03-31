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

#include "elink/common/Error.hpp"

#include <variant>
#include <utility>

namespace elink
{

/**
 * @brief Result type template (similar to Rust's Result<T, E>)
 *
 * Represents either a successful value of type T or an Error.
 * Uses std::variant internally for type-safe storage.
 *
 * @tparam T The type of the success value
 */
template<typename T>
class Result {
public:
    /**
     * @brief Create a successful result with a value
     * @param value The success value
     * @return Result containing the success value
     */
    static Result ok(T value) {
        return Result(std::move(value));
    }

    /**
     * @brief Create a failed result with an error
     * @param error The error information
     * @return Result containing the error
     */
    static Result err(Error error) {
        return Result(std::move(error));
    }

    /**
     * @brief Check if the result is successful
     * @return true if the result contains a value, false if it contains an error
     */
    bool isOk() const {
        return std::holds_alternative<T>(dataM);
    }

    /**
     * @brief Check if the result is an error
     * @return true if the result contains an error, false if it contains a value
     */
    bool isErr() const {
        return !isOk();
    }

    /**
     * @brief Get the success value (non-const)
     * @return Reference to the success value
     * @note Behavior is undefined if isErr() is true
     */
    T& value() {
        return std::get<T>(dataM);
    }

    /**
     * @brief Get the success value (const)
     * @return Const reference to the success value
     * @note Behavior is undefined if isErr() is true
     */
    const T& value() const {
        return std::get<T>(dataM);
    }

    /**
     * @brief Get the error (non-const)
     * @return Reference to the error
     * @note Behavior is undefined if isOk() is true
     */
    Error& error() {
        return std::get<Error>(dataM);
    }

    /**
     * @brief Get the error (const)
     * @return Const reference to the error
     * @note Behavior is undefined if isOk() is true
     */
    const Error& error() const {
        return std::get<Error>(dataM);
    }

private:
    explicit Result(T value) : dataM(std::move(value)) {}
    explicit Result(Error error) : dataM(std::move(error)) {}

    std::variant<T, Error> dataM;
};

/**
 * @brief Result type specialization for void
 *
 * Represents either success (with no value) or an Error.
 * Used for operations that don't return a value on success.
 */
template<>
class Result<void> {
public:
    /**
     * @brief Create a successful result (no value)
     * @return Result indicating success
     */
    static Result ok() {
        return Result(true);
    }

    /**
     * @brief Create a failed result with an error
     * @param error The error information
     * @return Result containing the error
     */
    static Result err(Error error) {
        return Result(std::move(error));
    }

    /**
     * @brief Check if the result is successful
     * @return true if the operation succeeded, false if it failed
     */
    bool isOk() const {
        return successM;
    }

    /**
     * @brief Check if the result is an error
     * @return true if the operation failed, false if it succeeded
     */
    bool isErr() const {
        return !successM;
    }

    /**
     * @brief Get the error (non-const)
     * @return Reference to the error
     * @note Behavior is undefined if isOk() is true
     */
    Error& error() {
        return errorM;
    }

    /**
     * @brief Get the error (const)
     * @return Const reference to the error
     * @note Behavior is undefined if isOk() is true
     */
    const Error& error() const {
        return errorM;
    }

private:
    explicit Result(bool) : successM(true), errorM{} {}
    explicit Result(Error errorP) : successM(false), errorM(std::move(errorP)) {}

    bool successM;
    Error errorM;
};

}
