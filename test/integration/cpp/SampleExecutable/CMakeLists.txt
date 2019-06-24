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

project(IntegrationTestSampleExecutable LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
                   PUBLIC
                       ${CMAKE_CURRENT_LIST_DIR}/source/cpp/Assertions.cpp
                       ${CMAKE_CURRENT_LIST_DIR}/source/cpp/Main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../../../source/cpp/Com/Wui/Framework/ResourceWriter/Writer)

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/../../../../build/compiled/lib/libResourceWriter.a)
