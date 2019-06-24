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
    TEST(LogManager, LoggerDevNull) {
        LogManager::setLogger(LoggerDevNull{});

        ::testing::internal::CaptureStdout();
        ::testing::internal::CaptureStderr();
        LogManager::getLogger().Error("Error");
        LogManager::getLogger().Info("Info");
        LogManager::getLogger().Debug("Debug");
        EXPECT_TRUE(testing::internal::GetCapturedStdout().empty());
        EXPECT_TRUE(testing::internal::GetCapturedStderr().empty());
    }

    TEST(LogManager, LoggerConsole) {
        LogManager::setLogger(LoggerConsole{});

        std::string sourceMessage = "This is message from unit test (COUT)";
        const std::string expectedMessage = sourceMessage + "\n";
        ::testing::internal::CaptureStdout();
        LogManager::getLogger().Info(std::move(sourceMessage));
        EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), expectedMessage.c_str());
    }
}
