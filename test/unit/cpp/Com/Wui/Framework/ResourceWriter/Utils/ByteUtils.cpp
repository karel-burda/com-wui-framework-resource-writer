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

namespace Com::Wui::Framework::ResourceWriter::Utils {
    class ByteUtilsTest : public ::testing::Test {
     private:
        void SetUp() override {
            Logger::LogManager::setLogger(Logger::LoggerDevNull{});
        }
    };

    TEST_F(ByteUtilsTest, Invalid) {
        EXPECT_THROW(ByteUtils::GetNumberFromByteArrayLE<unsigned char>({}), std::runtime_error);
        EXPECT_THROW(ByteUtils::GetNumberFromByteArrayLE<std::int8_t>({1, 0}), std::runtime_error);
        EXPECT_THROW(ByteUtils::GetNumberFromByteArrayLE<std::uint64_t>({0, 1, 0, 1, 0}), std::runtime_error);
    }

    TEST_F(ByteUtilsTest, Basic) {
        EXPECT_EQ(ByteUtils::GetNumberFromByteArrayLE<std::uint32_t>({0, 0, 0, 0}), static_cast<std::uint32_t>(0));
        EXPECT_EQ(ByteUtils::GetNumberFromByteArrayLE<std::uint32_t>({1, 0, 0, 0}), static_cast<std::uint32_t>(1));
        EXPECT_EQ(ByteUtils::GetNumberFromByteArrayLE<std::uint32_t>({0, 1, 0, 0}), static_cast<std::uint32_t>(256));
        EXPECT_EQ(ByteUtils::GetNumberFromByteArrayLE<std::uint16_t>({64, 1}), static_cast<std::uint16_t>(320));
    }
}
