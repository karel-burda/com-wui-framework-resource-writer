/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#elif _WIN32
#include <io.h>
#else
#error "Platform not implemented"
#endif

#include <stdexcept>

#include "FileUtils.hpp"

namespace Com::Wui::Framework::ResourceWriter::Utils::FileUtils {
    void truncateFile(const std::string &$path, const size_t $size) {
        FILE *file = fopen($path.c_str(), "r+");
        if (file == nullptr) {
            throw std::runtime_error{"Failed to open a file " + $path};
        }

        const auto fd = fileno(file);
#if defined(__unix__) || defined(__APPLE__)
        if (ftruncate(fd, $size) != 0) {
#elif _WIN32
        if (_chsize(fd, static_cast<long>($size)) != 0) {
#endif
            fclose(file);
            throw std::runtime_error{"Failed to truncate a file " + $path + " to size " + std::to_string($size)};
        }

        fclose(file);
    }
}
