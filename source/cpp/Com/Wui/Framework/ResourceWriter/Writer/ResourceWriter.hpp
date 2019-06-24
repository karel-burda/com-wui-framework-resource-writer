/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_WRITER_RESOURCEWRITER_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_WRITER_RESOURCEWRITER_HPP_

#include "Resource.hpp"
#include "Settings.hpp"

namespace Com::Wui::Framework::ResourceWriter::Writer {
    class ResourceWriter {
     public:
        explicit ResourceWriter(Settings $settings);

        void Write(ResourceMap $resources);

        void Update(ResourceMap $resources);

        void UpdateOrWrite(ResourceMap $resources);

     private:
        enum class WriteMethod : unsigned char {
            WRITE = 0,
            UPDATE,
            UPDATE_OR_WRITE
        };

        void update(ResourceMap $resources, WriteMethod $method);

        Settings settings;
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_WRITER_RESOURCEWRITER_HPP_
