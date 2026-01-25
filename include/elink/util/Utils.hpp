/***********************************************************************************
 * \file Utils.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-26 00:06:46
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

#include <cassert>

#ifndef ELINK_ASSERT
#define ELINK_ASSERT(x) assert(x)
#endif

#ifndef ELINK_STATIC_ASSERT
#define ELINK_STATIC_ASSERT(x, ...) static_assert(x __VA_OPT__(,) __VA_ARGS__)
#endif

namespace elink::util
{

}
