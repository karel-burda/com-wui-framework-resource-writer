/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGGERCONSOLE_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGGERCONSOLE_HPP_

#include "Logger.hpp"

namespace Com::Wui::Framework::ResourceWriter::Logger {
    class LoggerConsole : public Logger {
     public:
        LoggerConsole();
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGGERCONSOLE_HPP_
