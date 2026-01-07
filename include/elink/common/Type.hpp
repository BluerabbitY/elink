/***********************************************************************************
 * \file Type.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-07 20:05:37
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

#include <span>

namespace elink
{

using LiteBufferView = std::span<const uint8_t>;

using LiteBuffer = std::span<uint8_t>;

using MessageBufferView = std::span<const uint8_t>;

using MessageBuffer = std::span<uint8_t>;

}
