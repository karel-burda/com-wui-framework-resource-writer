/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_FILEREADER_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_FILEREADER_HPP_

#include <cstdint>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <string>

#include "../Core/Protocol.hpp"
#include "../Core/Resource.hpp"

namespace Com::Wui::Framework::ResourceWriter::Reader {
    struct ProtocolError : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    struct MagicSequenceError : ProtocolError {
        using ProtocolError::ProtocolError;
    };

    struct ContentOffsetError : ProtocolError {
        using ProtocolError::ProtocolError;
    };

    class FileReader {
     public:
        using ResourceInspectCallback = std::function<void(Core::Resource &&$resource)>;

        FileReader(const std::string &$path, bool $magicSequenceRequired);

        void ReadResources(ResourceInspectCallback &&$resourceFoundCallback);

        bool isVanillaFile() const;

        Core::Protocol::Types::ContentOffset getContentOffset() const;

        Core::Protocol::Types::FileOffset getContentEnd() const;

        void Close();

     private:
        void readProtocolVersion();

        void readMagicSequence();

        void readContentOffset();

        std::ifstream stream;
        Core::Protocol::Types::ContentOffset contentOffset = 0;
        Core::Protocol::Types::ContentOffset contentEnd = 0;
        std::uint64_t fileSize = 0;
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_FILEREADER_HPP_
