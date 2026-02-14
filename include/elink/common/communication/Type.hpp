/***********************************************************************************
 * \file Type.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-10 23:49:06
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#include "elink/common/Type.hpp"

#include "asio/serial_port_base.hpp"
#include "asio/awaitable.hpp"

#include <chrono>

namespace elink {

struct SerialPortCFG {
    using StopBit = asio::serial_port_base::stop_bits::type;
    using Parity = asio::serial_port_base::parity::type;
    using FlowControl = asio::serial_port_base::flow_control;

    std::string interfaceName{};
    uint32_t baudRate{9600};
    uint8_t dataBits{8};
    StopBit stopBits{StopBit::one};
    Parity parity{Parity::none};
    FlowControl flowc{FlowControl::none};
};

template <typename T>
concept SerialPortLike =
    // open
    requires(T t, const SerialPortCFG& cfg)
    {{t.open(cfg)} -> std::same_as<bool>;} &&
    // close
    requires(T t)
    {{t.close()} -> std::same_as<void>;} &&
    // recv
    requires(T t, LiteBuffer buf, const std::chrono::nanoseconds timeout)
    {{t.recv(buf, timeout)} -> std::same_as<asio::awaitable<std::size_t>>;} &&
    // send
    requires(T t, LiteBufferView bufView, const std::chrono::nanoseconds timeout)
    {{t.send(bufView, timeout)} -> std::same_as<asio::awaitable<std::size_t>>;} &&
    // discardInBuffer
    requires(T t) {{t.discardInBuffer()} -> std::same_as<void>;};

}
