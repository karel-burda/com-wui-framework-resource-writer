/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_RESOURCEWRITER_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_RESOURCEWRITER_HPP_

/** @file ResourceWriter.hpp
 * Common header for the library include, with compiler warnings suppression included.
 * This header is intended mainly for inclusion within the not "pure" WUI C++ projects (e.g. in the nodejsre).
 */

#if __cplusplus < 201703L
#   ifdef __clang__
#       pragma clang diagnostic push
#       pragma clang diagnostic ignored "-Wc++17-extensions"
#   endif
#endif

#include "Writer/ResourceWriter.hpp"
#include "Reader/ResourceReader.hpp"
#include "Logger/LoggerConsole.hpp"
#include "Logger/LoggerDevNull.hpp"
#include "Logger/LogManager.hpp"

#if __cplusplus < 201703L
#   ifdef __clang__
#       pragma clang diagnostic pop
#   endif
#endif

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_RESOURCEWRITER_HPP_
