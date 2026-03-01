/***********************************************************************************
 * \file NormalizedValueUtil.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-02-28 21:59:49
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "elink/common/Type.hpp"

#include <algorithm>

namespace elink::iec60870
{

using NormalizedValue = float;

using NormalizationFactor = float;

using ScaledValue = int16_t;

using ScaledFactor = float;

using OriginalPhyValue = float;

namespace details
{

using NormalizedValueBuffer = int16_t;

inline NormalizedValue scaledToNormalized(const ScaledValue scaledValue)
{
    return static_cast<float>(scaledValue) / 32768.f;
}

inline ScaledValue normalizedToScaled(const NormalizedValue normalizedValue)
{
    const float scaledValue = std::clamp<float>(normalizedValue, -1.0f, (32767.f / 32768.f)) * 32768.f;
    return static_cast<int16_t>(scaledValue < 0 ? scaledValue - 0.5f : scaledValue + 0.5f);
}

}
}
