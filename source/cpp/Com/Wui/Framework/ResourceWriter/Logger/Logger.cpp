/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include "Logger.hpp"

namespace Com::Wui::Framework::ResourceWriter::Logger {
    Logger::Logger(LogCallback $errorCallback, LogCallback $infoCallback, LogCallback $debugCallback)
            : error(std::move($errorCallback)),
              info(std::move($infoCallback)),
              debug(std::move($debugCallback)) {
    }

    void Logger::Error(std::string &&$message) const {
        this->invokeCallback(this->error, std::move($message));
    }

    void Logger::Info(std::string &&$message) const {
        this->invokeCallback(this->info, std::move($message));
    }

    void Logger::Debug(std::string &&$message) const {
        this->invokeCallback(this->debug, std::move($message));
    }

    void Logger::invokeCallback(const LogCallback &$callback, std::string &&$message) const {
        if ($callback != nullptr) {
            $callback(std::move($message));
        }
    }
}
