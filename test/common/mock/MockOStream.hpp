/***********************************************************************************
 * \file MockOStream.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-28 18:15:45
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

#include "elink/common/codec/OStreamCommon.hpp"

namespace mock
{

class OStream : public elink::details::OStreamCommon<OStream> {
public:
    OStream(uint8_t* buffer, const std::size_t size) : OStreamCommon{buffer, size}
    {
    }

    ~OStream() = default;

    using OStreamCommon::operator<<;
};

}
