/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGMANAGER_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGMANAGER_HPP_

#include "Logger.hpp"

namespace Com::Wui::Framework::ResourceWriter::Logger {
    class LogManager {
     public:
        static Logger& getLogger();

        static void setLogger(const Logger &$logger);

     private:
        static Logger logger;
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_LOGGER_LOGMANAGER_HPP_
