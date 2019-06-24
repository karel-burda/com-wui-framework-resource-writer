/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_PROTOCOL_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_PROTOCOL_HPP_

#include <cstdint>
#include <vector>

namespace Com::Wui::Framework::ResourceWriter::Core::Protocol::Types {
    using Data = std::vector<char>;

    using Version = std::uint8_t;

    using FileOffset = std::uint64_t;

    using ContentOffset = FileOffset;

    using MagicSequence = char[16];
}

namespace Com::Wui::Framework::ResourceWriter::Core::Protocol::Constants {
    static constexpr Types::Version ProtocolVersion = 2;

    static constexpr size_t HeaderSize = sizeof(Types::Version);

    static constexpr size_t FooterSize = sizeof(Types::ContentOffset) + sizeof(Types::MagicSequence);

    static constexpr Types::MagicSequence MagicSequence = {99,
                                                           127,
                                                           static_cast<char>(-8),
                                                           0,
                                                           1,
                                                           65,
                                                           static_cast<char>(-6),
                                                           static_cast<char>(-87),
                                                           64,
                                                           23,
                                                           static_cast<char>(-124),
                                                           static_cast<char>(-2),
                                                           41,
                                                           static_cast<char>(-57),
                                                           11,
                                                           8};
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_PROTOCOL_HPP_
