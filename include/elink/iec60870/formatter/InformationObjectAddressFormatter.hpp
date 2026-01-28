/***********************************************************************************
 * \file InformationObjectAddressFormatter.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 23:28:21
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

#include "elink/iec60870/io/InformationObjectAddress.hpp"

#include <format>

namespace std
{

template <>
struct formatter<elink::iec60870::IOA> : formatter<int> {
    using formatter<int>::parse;

    template <class FormatContext>
    auto format(const elink::iec60870::IOA& ioa, FormatContext& ctx) const
    {
        return formatter<int>::format(ioa.address(), ctx);
    }
};

}
