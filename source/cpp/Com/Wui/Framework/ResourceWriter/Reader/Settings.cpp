/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <algorithm>
#include <iterator>
#include <ostream>

#include "Settings.hpp"

namespace Com::Wui::Framework::ResourceWriter::Reader {
    Settings::Settings(std::string $inputFilePath)
            : inputFilePath(std::move($inputFilePath)) {
    }

    std::string Settings::getInputFilePath() const {
        return this->inputFilePath;
    }

    std::ostream &operator<<(std::ostream &$stream, const Settings &$params) {
        $stream << "input file path=" << $params.getInputFilePath();

        return $stream;
    }
}
