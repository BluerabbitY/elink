/***********************************************************************************
 * \file Test_RelocatedLog.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-10 01:26:48
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ***********************************************************************************/
#include "elink/common/LogRedirect.hpp"

#include <gtest/gtest.h>

class LogTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        elink::LogRedirect::setLogOutputHanlder([&](const elink::LogLevel level, const std::string_view file, const int line, const std::string& threadName, const std::string& content){
            logHandler(level, file, line, threadName, content);
        });

        elink::details::ThreadName::setThreadName("LogTest");
    }

    void TearDown() override
    {
    }

    struct OutputBuffer {
        elink::LogLevel level;
        std::string_view file;
        int line;
        std::string threadName;
        std::string content;
    };

    void logHandler(const elink::LogLevel level, const std::string_view file, const int line, const std::string& threadName, const std::string& content)
    {
        buffer.level = level;
        buffer.file = file;
        buffer.line = line;
        buffer.threadName = threadName;
        buffer.content = content;
    };

    OutputBuffer buffer{};
};

TEST_F(LogTest, RelocatedLog)
{
    DLOG("This is a test log: {}", 12345);

    EXPECT_EQ(buffer.level, elink::LogLevel::DBG);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 71);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a test log: 12345");
}

TEST_F(LogTest, Print)
{
    int count = 0;

    DLOG("This is a debug test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::DBG);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 84);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a debug test log: 1");

    ILOG("This is a information test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::INF);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 91);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a information test log: 2");

    WLOG("This is a warn test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::WRN);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 98);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a warn test log: 3");

    ELOG("This is a error test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::ERR);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 105);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a error test log: 4");

    CLOG("This is a critical test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::CRI);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 112);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a critical test log: 5");

    FLOG("This is a fatal test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::FAT);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 119);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a fatal test log: 6");
}

TEST_F(LogTest, Enabled)
{
    elink::LogRedirect::enableLogOutput(false);

    DLOG("This log should not be captured");
    EXPECT_EQ(buffer.level, elink::LogLevel::DBG);
    EXPECT_EQ(buffer.file, "");
    EXPECT_EQ(buffer.line, 0);
    EXPECT_EQ(buffer.threadName, "");
    EXPECT_EQ(buffer.content, "");
}
