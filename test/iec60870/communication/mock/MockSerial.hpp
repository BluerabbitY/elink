/***********************************************************************************
 * \file MockSerial.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-18 01:36:49
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
