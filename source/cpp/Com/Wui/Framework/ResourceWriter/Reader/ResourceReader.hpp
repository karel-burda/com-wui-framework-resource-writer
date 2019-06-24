/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_RESOURCEREADER_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_RESOURCEREADER_HPP_

#include "Resource.hpp"
#include "Settings.hpp"

namespace Com::Wui::Framework::ResourceWriter::Reader {
    class ResourceReader {
     public:
        explicit ResourceReader(Settings $settings);

        ResourceMap Read(size_t $numberOfBuckets = 0);

     private:
        Settings settings;
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_READER_RESOURCEREADER_HPP_
