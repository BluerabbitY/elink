/***********************************************************************************
 * \file CPXXTime2A.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2025-12-20 10:12:15
 * 
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#include "details/cpxxtime2a/CPxxTime2aImp.hpp"

namespace elink::iec60870 {

using CP16Time2a = details::CPxxTime2aImp<details::CP16Time2aTag>;
using CP24Time2a = details::CPxxTime2aImp<details::CP24Time2aTag>;
using CP32Time2a = details::CPxxTime2aImp<details::CP32Time2aTag>;
using CP56Time2a = details::CPxxTime2aImp<details::CP56Time2aTag>;

}
