/***********************************************************************************
 * \file IO.h
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief all information objects
 * \date 2025-12-22 23:56:03
 * 
 * \copyright Copyright (C) 2025-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "elink/iec60870/io/InformationObjectTypeID.h"
#include "elink/iec60870/io/InformationObjectAddress.hpp"

#include "elink/iec60870/io/InformationObject.hpp"
#include "elink/iec60870/io/SinglePointInformation.hpp"
#include "elink/iec60870/io/SinglePointWithCP24Time2a.hpp"
#include "elink/iec60870/io/DoublePointInformation.hpp"
#include "elink/iec60870/io/DoublePointWithCP24Time2a.hpp"
#include "elink/iec60870/io/StepPositionInformation.hpp"
#include "elink/iec60870/io/StepPositionWithCP24Time2a.hpp"
#include "elink/iec60870/io/BitString32.hpp"
#include "elink/iec60870/io/BitString32WithCP24Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueNormalized.hpp"
#include "elink/iec60870/io/MeasuredValueNormalizedWithCP24Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueScaled.hpp"
#include "elink/iec60870/io/MeasuredValueScaledWithCP24Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueShort.hpp"
#include "elink/iec60870/io/MeasuredValueShortWithCP24Time2a.hpp"
#include "elink/iec60870/io/IntegratedTotals.hpp"
#include "elink/iec60870/io/IntegratedTotalsWithCP24Time2a.hpp"
#include "elink/iec60870/io/EventOfProtectionEquipment.hpp"
#include "elink/iec60870/io/PackedStartEventsOfProtectionEquipment.hpp"
#include "elink/iec60870/io/PackedOutputCircuitInfo.hpp"
#include "elink/iec60870/io/PackedSinglePointWithSCD.hpp"
#include "elink/iec60870/io/MeasuredValueNormalizedWithoutQuality.hpp"
#include "elink/iec60870/io/SinglePointWithCP56Time2a.hpp"
#include "elink/iec60870/io/DoublePointWithCP56Time2a.hpp"
#include "elink/iec60870/io/StepPositionWithCP56Time2a.hpp"
#include "elink/iec60870/io/BitString32WithCP56Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueNormalizedWithCP56Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueScaledWithCP56Time2a.hpp"
#include "elink/iec60870/io/MeasuredValueShortWithCP56Time2a.hpp"
#include "elink/iec60870/io/IntegratedTotalsWithCP56Time2a.hpp"
#include "elink/iec60870/io/EventOfProtectionEquipmentWithCP56Time2a.hpp"
#include "elink/iec60870/io/PackedStartEventsOfProtectionEquipmentWithCP56Time2a.hpp"
#include "elink/iec60870/io/PackedOutputCircuitInfoWithCP56Time2a.hpp"
#include "elink/iec60870/io/SingleCommand.hpp"
#include "elink/iec60870/io/DoubleCommand.hpp"
#include "elink/iec60870/io/StepCommand.hpp"
#include "elink/iec60870/io/SetpointCommandNormalized.hpp"
#include "elink/iec60870/io/SetpointCommandScaled.hpp"
#include "elink/iec60870/io/SetpointCommandShort.hpp"
#include "elink/iec60870/io/BitString32Command.hpp"
#include "elink/iec60870/io/SingleCommandWithCP56Time2a.hpp"
#include "elink/iec60870/io/DoubleCommandWithCP56Time2a.hpp"
#include "elink/iec60870/io/StepCommandWithCP56Time2a.hpp"
#include "elink/iec60870/io/SetpointCommandNormalizedWithCP56Time2a.hpp"

#include "elink/iec60870/formatter/InformationObjectFormatter.hpp"
