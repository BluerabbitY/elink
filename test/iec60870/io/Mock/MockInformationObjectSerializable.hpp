/***********************************************************************************
 * \file MockInformationObjectSerializable.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-26 19:59:46
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

#include "elink/iec60870/details/io/InformationObjectSerializable.hpp"

namespace mock
{

class MockInformationObjectSerializable : public elink::iec60870::details::InformationObjectSerializable<MockInformationObjectSerializable, elink::iec60870::TypeID::M_SP_NA_1>
{
public:
    MockInformationObjectSerializable() = default;

    explicit MockInformationObjectSerializable(const elink::iec60870::IOA ioa)
        : InformationObjectSerializable{ioa}
    {
    }

    ~MockInformationObjectSerializable() = default;
};

}
