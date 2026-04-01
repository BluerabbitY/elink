/***********************************************************************************
 * \file PollEntry.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 11:45:32
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

#include "elink/common/NativeHandle.hpp"

#include <vector>

namespace elink::details
{

struct PollEntry
{
    NativeHandle handle;
    bool ready = false;
};

using PollEntrys = std::vector<PollEntry>;

}
