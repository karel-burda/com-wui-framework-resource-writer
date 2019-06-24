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
    TEST(Logger, Basic) {
        std::vector<std::string> errorMessages;
        std::vector<std::string> infoMessages;

        auto errorCallback = [&errorMessages](std::string &&$message) {
            errorMessages.emplace_back(std::move($message));
        };

        auto infoCallback = [&infoMessages](std::string &&$message) {
            infoMessages.emplace_back(std::move($message));
        };

        // deliberately ignoring debug callback
        Logger logger{std::move(errorCallback), std::move(infoCallback), nullptr};

        ASSERT_TRUE(errorMessages.empty());
        ASSERT_TRUE(infoMessages.empty());

        {
            logger.Error("Aa");

            ASSERT_EQ(errorMessages.size(), static_cast<decltype(errorMessages)::size_type>(1));
            EXPECT_EQ(errorMessages.front(), "Aa");

            logger.Error("");

            ASSERT_EQ(errorMessages.size(), static_cast<decltype(errorMessages)::size_type>(2));
            EXPECT_EQ(errorMessages.back(), "");
        }

        {
            logger.Info("boo=" + std::to_string(-99));
            logger.Info("foo");

            ASSERT_EQ(infoMessages.size(), static_cast<decltype(infoMessages)::size_type>(2));
            EXPECT_EQ(infoMessages.front(), "boo=-99");
            EXPECT_EQ(infoMessages.back(), "foo");
        }

        {
            logger.Debug("This should not be printed anywhere");
        }
    }
}
