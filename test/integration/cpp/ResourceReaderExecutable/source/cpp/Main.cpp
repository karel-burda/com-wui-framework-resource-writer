/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <cstdlib>
#include <iostream>
#include <exception>
#include <memory>

#include <ResourceReader.hpp>

// Usage: resource-reader <input-file> <resource-name> <resource-content-path>
int main(int argc, const char **argv) {
    try {
        namespace Reader = Com::Wui::Framework::ResourceWriter::Reader;

        const auto reader = std::make_unique<Reader::ResourceReader>(Reader::Settings{argc, argv});

        reader->Read();

        return EXIT_SUCCESS;
    }
    catch (const std::exception &error) {
        std::cerr << "Intercepted error: " << error.what() << std::endl;
    }

    return EXIT_FAILURE;
}
