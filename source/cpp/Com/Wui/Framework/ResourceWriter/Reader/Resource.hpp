/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_RESOURCE_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_RESOURCE_HPP_

#include <unordered_map>

#include "../Core/Resource.hpp"

namespace Com::Wui::Framework::ResourceWriter::Reader {
    using Resource = Core::Resource;

    using ResourceMap = std::unordered_map<std::string, Resource>;
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_RESOURCE_HPP_
