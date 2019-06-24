/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_UTILS_BYTEUTILS_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_UTILS_BYTEUTILS_HPP_

#include <climits>
#include <cstdint>
#include <vector>

#include "../Core/Protocol.hpp"

namespace Com::Wui::Framework::ResourceWriter::Utils::ByteUtils {
    template <typename T>
    T GetNumberFromByteArrayLE(const Core::Protocol::Types::Data &$data) {
        if ($data.size() != sizeof(T)) {
            throw std::runtime_error{"Expecting " + std::to_string(sizeof(T)) + " byte collection"};
        }

        T number = 0;

        for (size_t i = 0; i < $data.size(); ++i) {
            number |= (static_cast<unsigned char>($data[i]) << i*CHAR_BIT);
        }

        return number;
    }
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_UTILS_BYTEUTILS_HPP_
