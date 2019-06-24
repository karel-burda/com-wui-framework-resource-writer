/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include "LoggerDevNull.hpp"
#include "LogManager.hpp"

namespace Com::Wui::Framework::ResourceWriter::Logger {
    Logger LogManager::logger = LoggerDevNull{};

    Logger& LogManager::getLogger() {
        return LogManager::logger;
    }

    void LogManager::setLogger(const Logger &$logger) {
        LogManager::logger = $logger;
    }
}
