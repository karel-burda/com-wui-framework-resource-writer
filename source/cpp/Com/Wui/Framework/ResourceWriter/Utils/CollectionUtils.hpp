/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_UTILS_COLLECTIONUTILS_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_UTILS_COLLECTIONUTILS_HPP_

#include <iterator>
#include <unordered_map>

namespace Com::Wui::Framework::ResourceWriter::Utils::CollectionUtils {
    template <typename ... Args>
    void ConcatenateHashMaps(std::unordered_map<Args ...> &$base, std::unordered_map<Args ...> &$toBeAppended) {
        $base.insert(std::make_move_iterator(std::begin($toBeAppended)), std::make_move_iterator(std::end($toBeAppended)));

        // delete also keys of the second map
        $toBeAppended.clear();
        $toBeAppended.reserve(0);
    }
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_UTILS_COLLECTIONUTILS_HPP_
