/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_SETTINGS_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_SETTINGS_HPP_

#include <iosfwd>
#include <string>

namespace Com::Wui::Framework::ResourceWriter::Reader {
    class Settings {
     public:
        explicit Settings(std::string $inputFilePath);

        std::string getInputFilePath() const;

     private:
        std::string inputFilePath;
        std::string resourceOutputPath;
    };

    std::ostream &operator<<(std::ostream &$stream, const Settings &$parser);
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_SETTINGS_HPP_
