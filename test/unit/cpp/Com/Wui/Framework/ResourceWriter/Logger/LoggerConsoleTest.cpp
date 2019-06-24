/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include "../../../../../reference.hpp"

namespace Com::Wui::Framework::ResourceWriter::Logger {
    class LoggerConsoleTest : public ::testing::Test {
     protected:
        LoggerConsole logger;
    };

    TEST_F(LoggerConsoleTest, Error) {
        std::string sourceMessage = "This is message from unit test (CERR)";
        const std::string expectedMessage = sourceMessage + "\n";
        ::testing::internal::CaptureStderr();
        this->logger.Error(std::move(sourceMessage));
        EXPECT_STREQ(testing::internal::GetCapturedStderr().c_str(), expectedMessage.c_str());
    }

    TEST_F(LoggerConsoleTest, Info) {
        std::string sourceMessage = "This is message from unit test (COUT)";
        const std::string expectedMessage = sourceMessage + "\n";
        ::testing::internal::CaptureStdout();
        this->logger.Info(std::move(sourceMessage));
        EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), expectedMessage.c_str());
    }

    TEST_F(LoggerConsoleTest, Debug) {
        std::string sourceMessage = "This is message from unit test (COUT)";
        const std::string expectedMessage = sourceMessage + "\n";
        ::testing::internal::CaptureStdout();
        this->logger.Debug(std::move(sourceMessage));
        EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), expectedMessage.c_str());
    }
}
