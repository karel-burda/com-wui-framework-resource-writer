/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGGER_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGGER_HPP_

#include <functional>
#include <iostream>

namespace Com::Wui::Framework::ResourceWriter::Logger {
    class Logger {
     public:
        using LogCallback = std::function<void(std::string &&$message)>;

        Logger() = default;

        Logger(LogCallback $errorCallback, LogCallback $infoCallback, LogCallback $debugCallback);

        void Error(std::string &&$message) const;

        void Info(std::string &&$message) const;

        void Debug(std::string &&$message) const;

     private:
        void invokeCallback(const LogCallback &$callback, std::string &&$message) const;

        LogCallback error = nullptr;
        LogCallback info = nullptr;
        LogCallback debug = nullptr;
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGGER_HPP_
