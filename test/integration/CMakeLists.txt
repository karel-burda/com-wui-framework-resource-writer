# * ********************************************************************************************************* *
# *
# * Copyright (c) 2019 NXP
# *
# * SPDX-License-Identifier: BSD-3-Clause
# * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
# * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
# *
# * ********************************************************************************************************* *

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(IntegrationTests LANGUAGES NONE)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cpp/ResourceReaderExecutable)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cpp/ResourceWriterExecutable)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cpp/SampleExecutable)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cmake/Runner)
