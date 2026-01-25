/***********************************************************************************
 * \file InformationObjectUtil.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-25 01:19:34
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

#include "elink/util/Utils.hpp"
#include "elink/iec60870/io/InformationObject.hpp"

#include <type_traits>

namespace elink::iec60870
{

template <typename T>
T& io_cast(InformationObject& io)
{
    ELINK_ASSERT(T::IDENT_T == io.getTypeID());
    ELINK_STATIC_ASSERT(std::is_base_of_v<InformationObject, T>, "Derived must inherit from InformationObject");
    return static_cast<T&>(io);
}

}
