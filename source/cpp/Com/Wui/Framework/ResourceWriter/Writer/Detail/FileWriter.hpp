/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_WRITER_DETAIL_FILEWRITER_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_WRITER_DETAIL_FILEWRITER_HPP_

#include <cstdint>
#include <fstream>

#include "../../Core/Protocol.hpp"
#include "../../Core/Resource.hpp"

namespace Com::Wui::Framework::ResourceWriter::Writer::Detail {
    class FileWriter {
     public:
        explicit FileWriter(const std::string &$path, Core::Protocol::Types::ContentOffset $contentOffset);

        void Write(Core::Resource &&$resource);

        void WriteProtocolVersion();

        void Close();

     private:
        void writeOffset();

        void writeMagicSequence();

        std::ofstream stream;
        Core::Protocol::Types::ContentOffset contentOffset = 0;
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_WRITER_DETAIL_FILEWRITER_HPP_
