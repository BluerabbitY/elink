/***********************************************************************************
 * \file Test_RelocatedLog.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-10 01:26:48
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#include "elink/common/logging/logger.hpp"

#include <gtest/gtest.h>

class LogTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        elink::Log::setLogOutputHanlder([&](const elink::LogLevel level, const std::string_view file, const int line, const std::string& threadName, const std::string& content){
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
    EXPECT_EQ(buffer.line, 56);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a test log: 12345");
}

TEST_F(LogTest, Print)
{
    int count = 0;

    DLOG("This is a debug test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::DBG);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 69);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a debug test log: 1");

    ILOG("This is a information test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::INF);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 76);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a information test log: 2");

    WLOG("This is a warn test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::WRN);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 83);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a warn test log: 3");

    ELOG("This is a error test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::ERR);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 90);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a error test log: 4");

    CLOG("This is a critical test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::CRI);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 97);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a critical test log: 5");

    FLOG("This is a fatal test log: {}", ++count);
    EXPECT_EQ(buffer.level, elink::LogLevel::FAT);
    EXPECT_EQ(buffer.file, "Test_RelocatedLog.cpp");
    EXPECT_EQ(buffer.line, 104);
    EXPECT_EQ(buffer.threadName, "LogTest");
    EXPECT_EQ(buffer.content, "This is a fatal test log: 6");
}

TEST_F(LogTest, Enabled)
{
    elink::Log::enableLogOutput(false);

    DLOG("This log should not be captured");
    EXPECT_EQ(buffer.level, elink::LogLevel::DBG);
    EXPECT_EQ(buffer.file, "");
    EXPECT_EQ(buffer.line, 0);
    EXPECT_EQ(buffer.threadName, "");
    EXPECT_EQ(buffer.content, "");
}
