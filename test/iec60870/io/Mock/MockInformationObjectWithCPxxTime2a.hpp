/***********************************************************************************
 * \file MockInformationObjectWithCPxxTime2a.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 20:35:51
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

#include "elink/iec60870/details/cpxxtime2a/CPxxTime2aUtil.hpp"

namespace mock
{

template<typename T>
class MockInformationObjectWithCPxxTime2a : public elink::iec60870::details::CPxxTime2aUtil<T>
{
public:
    MockInformationObjectWithCPxxTime2a() = default;

    explicit MockInformationObjectWithCPxxTime2a(const T& cpxxtime2a)
    : elink::iec60870::details::CPxxTime2aUtil<T>{cpxxtime2a}
    {
    }

    ~MockInformationObjectWithCPxxTime2a() = default;
};

}
