/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <stdexcept>

#include "BinaryReader.hpp"

namespace Com::Wui::Framework::ResourceWriter::Core::Detail {
    BinaryReader::BinaryReader(std::string $path) {
        this->stream.open($path.c_str(), std::ios::in | std::ios::binary);

        if (!this->stream.is_open()) {
            throw std::runtime_error{"File " + $path + " cannot be opened for reading"};
        }
    }

    Core::Protocol::Types::Data BinaryReader::getContents() {
        return Core::Protocol::Types::Data{(std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>()};
    }
}
