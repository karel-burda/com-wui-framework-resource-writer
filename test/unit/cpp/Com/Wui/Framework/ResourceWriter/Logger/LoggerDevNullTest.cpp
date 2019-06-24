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
    class LoggerDevNullTest : public ::testing::Test {
     protected:
        LoggerDevNull logger;
    };

    TEST_F(LoggerDevNullTest, Error) {
        ::testing::internal::CaptureStderr();
        this->logger.Error("Error");

        EXPECT_TRUE(testing::internal::GetCapturedStderr().empty());
    }

    TEST_F(LoggerDevNullTest, Info) {
        ::testing::internal::CaptureStdout();
        this->logger.Info("Info");

        EXPECT_TRUE(testing::internal::GetCapturedStdout().empty());
    }

    TEST_F(LoggerDevNullTest, Debug) {
        ::testing::internal::CaptureStdout();
        this->logger.Debug("Debug");

        EXPECT_TRUE(testing::internal::GetCapturedStdout().empty());
    }
}
