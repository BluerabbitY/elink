/***********************************************************************************
 * \file ThreadNameImpWindows.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-03-31 22:24:02
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

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <processthreadsapi.h>
#include <string>

namespace elink::details
{

class ThreadNameImp
{
public:
    static void setThreadName(const std::string& limitedThreadName)
    {
        using SetThreadDescriptionFunc = HRESULT (WINAPI *)(HANDLE, PCWSTR);
        const HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll");
        if (!hKernel32)
            return;

        if (const auto pSetThreadDescription = reinterpret_cast<SetThreadDescriptionFunc>(GetProcAddress(hKernel32, "SetThreadDescription")))
        {
            const std::wstring winThreadName{limitedThreadName.begin(), limitedThreadName.end()};
            std::ignore = pSetThreadDescription(GetCurrentThread(), winThreadName.c_str());
            // if (SUCCEEDED(hr)) {}
        }
    }

private:
    ThreadNameImp() = default;
    ~ThreadNameImp() = default;
};

}
