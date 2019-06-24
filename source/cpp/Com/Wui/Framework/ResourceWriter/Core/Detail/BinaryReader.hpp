/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_DETAIL_BINARYREADER_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_DETAIL_BINARYREADER_HPP_

#include <fstream>
#include <string>

#include "../../Core/Protocol.hpp"

namespace Com::Wui::Framework::ResourceWriter::Core::Detail {
    class BinaryReader {
     public:
        explicit BinaryReader(std::string $path);

        Core::Protocol::Types::Data getContents();

     private:
        std::ifstream stream;
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_DETAIL_BINARYREADER_HPP_
