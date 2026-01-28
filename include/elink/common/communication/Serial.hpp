/***********************************************************************************
 * \file Serial.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-11 14:50:16
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

#include "elink/common/communication/Type.hpp"
#include "elink/common/Type.hpp"
#include "elink/common/logging/logger.hpp"
#include "elink/common/communication/Component.hpp"

#include "asio/serial_port.hpp"
#include "asio/steady_timer.hpp"
#include "asio/write.hpp"
#include "asio/read.hpp"
#include "asio/experimental/awaitable_operators.hpp"

namespace elink
{

class Serial
{
public:
    explicit Serial(Component& component)
        :
        serialHandleM{detail::getIOcontext(component)},
        timerRecvM{serialHandleM.get_executor()},
        timerSendM{serialHandleM.get_executor()}
    {
    }

    ~Serial()
    {
        close();
    }

    bool open(const SerialPortCFG& cfg)
    {
        asio::error_code ec;
        std::ignore = serialHandleM.open(cfg.interfaceName, ec);

        if (ec) {
            return false;
        }

        serialHandleM.set_option(asio::serial_port::baud_rate(cfg.baudRate));
        serialHandleM.set_option(asio::serial_port::character_size(cfg.dataBits));
        serialHandleM.set_option(asio::serial_port::stop_bits(cfg.stopBits));
        serialHandleM.set_option(asio::serial_port::parity(cfg.parity));
        serialHandleM.set_option(asio::serial_port::flow_control(cfg.flowc));

        return true;
    }

    void close()
    {
        if (serialHandleM.is_open())
        {
            serialHandleM.close();
        }
    }

    asio::awaitable<std::size_t> recv(const LiteBuffer data, const std::chrono::nanoseconds timeout)
    {
        try
        {
            timerRecvM.expires_after(timeout);

            using namespace asio::experimental::awaitable_operators;
            auto result = co_await (
                asio::async_read(serialHandleM, asio::buffer(data), asio::use_awaitable) ||
                timerRecvM.async_wait(asio::use_awaitable));

            if (result.index() == 0)
            {
                co_return std::get<0>(result);
            }

            co_return 0;
        }
        catch (std::exception& e)
        {
            ELOG("Serial read error: {}", e.what());
            co_return 0;
        }
    }

    asio::awaitable<std::size_t> send(const LiteBufferView data, const std::chrono::nanoseconds timeout)
    {
        try
        {
            timerSendM.expires_after(timeout);

            using namespace asio::experimental::awaitable_operators;
            auto result = co_await (
                asio::async_write(serialHandleM, asio::buffer(data), asio::use_awaitable) ||
                timerSendM.async_wait(asio::use_awaitable));

            if (result.index() == 0)
            {
                co_return std::get<0>(result);
            }

            co_return 0;
        }
        catch (std::exception& e)
        {
            ELOG("Serial write error: {}", e.what());
            co_return 0;
        }
    }

    void discardInBuffer()
    {
#ifdef _WIN32
        PurgeComm(serialHandleM.native_handle(), PURGE_RXCLEAR | PURGE_TXCLEAR);
#else
        ::tcflush(serialHandleM.native_handle(), TCIOFLUSH);
#endif
    }

private:
    asio::serial_port serialHandleM;
    asio::steady_timer timerRecvM;
    asio::steady_timer timerSendM;
};

}
