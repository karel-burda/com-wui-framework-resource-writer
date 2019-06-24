/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <cstdint>
#include <iostream>

#include "Assertions.hpp"

static void DumpInfo(const char *$path) {
    std::clog << "Full path: " << $path << std::endl;
}

int main(int /*$argc*/, const char **$argv)
{
    DumpInfo($argv[0]);

    Assertions::Test();

    return EXIT_SUCCESS;
}
