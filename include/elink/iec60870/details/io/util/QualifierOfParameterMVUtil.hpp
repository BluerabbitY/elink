/***********************************************************************************
 * \file QualifierOfParameterMVUtil.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-19 13:06:02
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

#include "elink/iec60870/io/QualifierOfParameterMV.hpp"

namespace elink::iec60870::details
{

class QualifierOfParameterMVUtil
{
public:
    QualifierOfParameterMVUtil()
    : qpmM{QPM::NOT_USED}
    {
    }

    explicit QualifierOfParameterMVUtil(const QualifierOfParameterMV qpm)
    : qpmM{qpm}
    {
    }

    ~QualifierOfParameterMVUtil() = default;

    void setQPM(const QualifierOfParameterMV qpm)
    {
        qpmM = qpm;
    }

    [[nodiscard]] QualifierOfParameterMV getQPM() const
    {
        return qpmM;
    }

protected:
    QualifierOfParameterMV qpmM;
};

using QPMUtil = QualifierOfParameterMVUtil;

}
