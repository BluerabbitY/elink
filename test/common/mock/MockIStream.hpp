/***********************************************************************************
 * \file MockIStream.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-28 18:47:02
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

#include "elink/common/details/codec/IStream.hpp"

namespace mock
{

class IStream : public elink::details::IStream<IStream> {
public:
    IStream(const uint8_t* buffer, const std::size_t size) : elink::details::IStream<IStream>{buffer, size}
    {
    }

    ~IStream() = default;

    using elink::details::IStream<IStream>::operator>>;
};

}
