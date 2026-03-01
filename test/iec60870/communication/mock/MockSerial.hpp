/***********************************************************************************
 * \file MockSerial.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-18 01:36:49
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ***********************************************************************************/
#pragma once

#include "elink/common/communication/Type.hpp"
#include "elink/common/communication/Component.hpp"
#include "elink/common/Type.hpp"

namespace mock
{

class Serial
{
public:
    explicit Serial(elink::Component&)
    {
    }

    ~Serial() = default;

    bool open(const elink::SerialPortCFG&)
    {
        callOpen = true;
        return callOpen;
    }

    bool callOpen{false};

    void close()
    {
        callCloseM = true;
    }

    bool callCloseM{false};

    asio::awaitable<std::size_t> recv(const elink::LiteBuffer data, const std::chrono::nanoseconds timeout)
    {
        co_return 1;
    }

    asio::awaitable<std::size_t> send(const elink::LiteBufferView data, const std::chrono::nanoseconds timeout)
    {
        co_return 1;
    }

    void discardInBuffer()
    {
        callDiscardInBufferM = true;
    }

    bool callDiscardInBufferM{false};
};

}
