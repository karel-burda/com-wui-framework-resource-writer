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

namespace Com::Wui::Framework::ResourceWriter::Writer {
    Settings::Settings(std::string $outputFilePath)
            : outputFilePath(std::move($outputFilePath)) {
    }

    std::string Settings::getOutputFilePath() const {
        return this->outputFilePath;
    }

    std::ostream &operator<<(std::ostream &$stream, const Settings &$params) {
        $stream << "output file path=" << $params.getOutputFilePath();

        return $stream;
    }
}
