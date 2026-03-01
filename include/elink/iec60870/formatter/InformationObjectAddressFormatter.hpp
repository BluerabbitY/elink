/***********************************************************************************
 * \file InformationObjectAddressFormatter.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-08 23:28:21
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

#include "elink/iec60870/io/InformationObjectAddress.hpp"

#include <format>

namespace std
{

template <>
struct formatter<elink::iec60870::IOA> : formatter<int> {
    using formatter<int>::parse;

    template <class FormatContext>
    auto format(const elink::iec60870::IOA& ioa, FormatContext& ctx) const
    {
        return formatter<int>::format(ioa.address(), ctx);
    }
};

}
