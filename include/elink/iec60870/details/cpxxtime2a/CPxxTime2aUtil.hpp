/***********************************************************************************
 * \file cpxxtime2aUtil.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-22 19:11:30
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

#include "elink/iec60870/CPxxTime2a.hpp"

namespace elink::iec60870::details
{

template <typename Timestamp> requires (std::is_same_v<Timestamp, CP16Time2a> ||
                                        std::is_same_v<Timestamp, CP24Time2a> ||
                                        std::is_same_v<Timestamp, CP32Time2a> ||
                                        std::is_same_v<Timestamp, CP56Time2a>)
class CPxxTime2aUtil
{
public:
    CPxxTime2aUtil() requires (std::is_same_v<Timestamp, CP24Time2a> ||
                               std::is_same_v<Timestamp, CP32Time2a> ||
                               std::is_same_v<Timestamp, CP56Time2a>)
    : cpxxtime2aM{Timestamp::now()}
    {
    }

    CPxxTime2aUtil() requires (std::is_same_v<Timestamp, CP16Time2a>)
    : cpxxtime2aM{}
    {
    }

    explicit CPxxTime2aUtil(const Timestamp& cpxxtime2a) : cpxxtime2aM{cpxxtime2a} {};

    [[nodiscard]] Timestamp& getTimestamp()
    {
        return cpxxtime2aM;
    }

    void setTimestamp(const Timestamp& cpxxtime2a = Timestamp::now())
    {
        cpxxtime2aM = cpxxtime2a;
    }

protected:
    Timestamp cpxxtime2aM;
};

}
