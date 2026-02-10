/***********************************************************************************
 * \file ApplicationServiceDataUnit.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief Application Service Data Unit
 * \date 2026-01-29 23:36:11
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
#include "elink/iec60870/details/ApplicationServiceDataUnitImp.hpp"

namespace elink::iec60870
{

namespace cs101
{
using ApplicationServiceDataUnit = details::ApplicationServiceDataUnitImp<details::CS101_MAXUMUM_LENGTH_OF_ASDU>;
using ASDU = ApplicationServiceDataUnit;
}

namespace cs104
{
using ApplicationServiceDataUnit = details::ApplicationServiceDataUnitImp<details::CS104_MAXUMUM_LENGTH_OF_ASDU>;
using ASDU = ApplicationServiceDataUnit;
}

}
