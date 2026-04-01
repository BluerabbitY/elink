/***********************************************************************************
 * \file PlatformPollConcept.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 11:20:01
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
#include "elink/common/details/poll/PollEntry.hpp"
#include "elink/common/Result.hpp"

#include <concepts>

namespace elink::details
{

template<typename T>
concept PlatformPollConcept = requires(PollEntries& entries, const std::chrono::milliseconds timeout)
{
    {T::poll(entries, timeout)} -> std::convertible_to<Result<int>>;
};

}
