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
#include <exception>
#include <iostream>
#include <memory>

#include <ResourceWriter.hpp>

// Usage: resource-writer <output-file> <resource-name> <resource-content-path> [<resource-name> <resource-content-path> ...]
int main(int $argc, const char **$argv) {
    try {
        namespace Writer = Com::Wui::Framework::ResourceWriter::Writer;

        const auto writer = std::make_unique<Writer::ResourceWriter>(Writer::Settings{$argc, $argv});

        writer->Write();

        return EXIT_SUCCESS;
    } catch (const std::exception &error) {
        std::cerr << "Intercepted error: " << error.what() << std::endl;
    }

    return EXIT_FAILURE;
}
