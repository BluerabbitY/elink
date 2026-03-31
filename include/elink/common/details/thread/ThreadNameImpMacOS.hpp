/***********************************************************************************
 * \file ThreadNameImpMacOS.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-01 00:00:07
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

#include <pthread.h>
#include <string>

namespace elink::details
{

class ThreadNameImp
{
public:
    static void setThreadName(const std::string& limitedThreadName)
    {
        pthread_setname_np(limitedThreadName.c_str());
    }

private:
    ThreadNameImp() = default;
    ~ThreadNameImp() = default;
};

}
