/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <iostream>

#include "LoggerConsole.hpp"

namespace Com::Wui::Framework::ResourceWriter::Logger {
    LoggerConsole::LoggerConsole()
            : Logger([](std::string &&$message) {
                         std::cerr << $message << std::endl;
                     },
                     [](std::string &&$message) {
                        std::cout << $message << std::endl;
                     },
                     [](std::string &&$message) {
                         std::cout << $message << std::endl;
                     }) {
    }
}
