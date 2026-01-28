/***********************************************************************************
 * \file elink.h
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2025-11-26 00:27:22
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

#include "elink/config.h"

#include "elink/common/logging/logger.hpp"
#include "elink/common/thread/Thread.hpp"

#include "elink/iec60870/details/codec/IOStream.h"

#include "elink/iec60870/io/IO.h"

#include "elink/iec60870/CPxxTime2a.hpp"

#include "elink/iec60870/formatter/Formatter.h"

#include "elink/iec60870/communication/link_layer/SerialFT12MessageTransceiver.hpp"
