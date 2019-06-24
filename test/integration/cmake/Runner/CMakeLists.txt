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

project(IntegrationTestRunner LANGUAGES NONE)

set(_resource-writer-path
        ${CMAKE_BINARY_DIR}/test/integration/cpp/ResourceWriterExecutable/IntegrationTestResourceWriterExecutable${CMAKE_EXECUTABLE_SUFFIX})
set(_resource-reader-path
        ${CMAKE_BINARY_DIR}/test/integration/cpp/ResourceReaderExecutable/IntegrationTestResourceReaderExecutable${CMAKE_EXECUTABLE_SUFFIX})
set(_sample-executable-path
        ${CMAKE_BINARY_DIR}/test/integration/cpp/SampleExecutable/IntegrationTestSampleExecutable${CMAKE_EXECUTABLE_SUFFIX})
find_program(_git-executable-path git)

set(_command_copy_sample_executable ${CMAKE_COMMAND} -E copy ${_sample-executable-path} ${_sample-executable-path}-for-testing)
set(_command_copy_reader_executable ${CMAKE_COMMAND} -E copy ${_resource-reader-path} ${_resource-reader-path}-for-testing)
set(_command_copy_git_executable ${CMAKE_COMMAND} -E copy ${_git-executable-path} ${CMAKE_CURRENT_BINARY_DIR}/git-for-testing)
set(_command_echo_test ${CMAKE_COMMAND} -E cmake_echo_color --blue)
set(_command_echo_action ${CMAKE_COMMAND} -E cmake_echo_color --yellow)

set(_resources_path ${CMAKE_CURRENT_LIST_DIR}/../../../resource)

add_custom_target(IntegrationTestWriteTextual
                  COMMAND ${_command_echo_test} "Running IntegrationTestWriteTextual test"

                  COMMAND ${_command_echo_action} "Preparation..."
                  COMMAND ${_command_copy_sample_executable}
                  COMMAND ${CMAKE_COMMAND} -E remove -f dummy_extracted.json

                  COMMAND ${_command_echo_action} "Writing resources"
                  COMMAND ${_resource-writer-path} ${_sample-executable-path}-for-testing
                                                   .RESOURCES/1 ${_resources_path}/dummy.json

                  COMMAND ${_command_echo_action} "Checking whether binary is valid (executing it)"
                  COMMAND ${_sample-executable-path}-for-testing

                  COMMAND ${_command_echo_action} "Reading resources"
                  COMMAND ${_resource-reader-path} ${_sample-executable-path}-for-testing
                                                   .RESOURCES/1 dummy_extracted.json

                  COMMAND ${_command_echo_action} "Comparing extracted files"
                  COMMAND ${CMAKE_COMMAND} -E compare_files ${_resources_path}/dummy.json dummy_extracted.json
                  VERBATIM)

add_custom_target(IntegrationTestWriteBinary
                  COMMAND ${_command_echo_test} "Running IntegrationTestWriteBinary test"

                  COMMAND ${_command_echo_action} "Preparation..."
                  COMMAND ${_command_copy_sample_executable}
                  COMMAND ${CMAKE_COMMAND} -E remove -f dummy_extracted.bin

                  COMMAND ${_command_echo_action} "Writing resources"
                  COMMAND ${_resource-writer-path} ${_sample-executable-path}-for-testing
                                                   .RESOURCES/2 ${_resources_path}/dummy.bin

                  COMMAND ${_command_echo_action} "Checking whether binary is valid (executing it)"
                  COMMAND ${_sample-executable-path}-for-testing

                  COMMAND ${_command_echo_action} "Reading resources"
                  COMMAND ${_resource-reader-path} ${_sample-executable-path}-for-testing
                                                   .RESOURCES/2 dummy_extracted.bin

                  COMMAND ${_command_echo_action} "Comparing extracted files"
                  COMMAND ${CMAKE_COMMAND} -E compare_files ${_resources_path}/dummy.bin dummy_extracted.bin
                  VERBATIM)

set(_args ${_sample-executable-path}-for-testing)
# Windows cannot handle more arguments
if (WIN32)
    set(_range 16)
    set(_resource_name_binary "resource-binary-15")
    set(_resource_name_textual "resource-textual-16")
else ()
    set(_range 128)
    set(_resource_name_binary "resource-binary-127")
    set(_resource_name_textual "resource-textual-129")
endif()
foreach(i RANGE ${_range})
    list(APPEND _args resource-textual-${i} ${_resources_path}/dummy.json resource-binary-${i} ${_resources_path}/dummy.bin)
endforeach()
add_custom_target(IntegrationTestWriteMultiple
                  COMMAND ${_command_echo_test} "Running IntegrationTestWriteMultiple test"

                  COMMAND ${_command_echo_action} "Preparation..."
                  COMMAND ${_command_copy_sample_executable}
                  COMMAND ${CMAKE_COMMAND} -E remove -f dummy_extracted.json
                                                        dummy_extracted.bin

                  COMMAND ${_command_echo_action} "Writing resources"
                  COMMAND ${_resource-writer-path} ${_args}

                  COMMAND ${_command_echo_action} "Checking whether binary is valid (executing it)"
                  COMMAND ${_sample-executable-path}-for-testing

                  COMMAND ${_command_echo_action} "Reading resources"
                  COMMAND ${_resource-reader-path} ${_sample-executable-path}-for-testing ${_resource_name_binary} dummy_extracted.bin
                  COMMAND ${_resource-reader-path} ${_sample-executable-path}-for-testing ${_resource_name_textual} dummy_extracted.json

                  COMMAND ${_command_echo_action} "Comparing extracted files"
                  COMMAND ${CMAKE_COMMAND} -E compare_files ${_resources_path}/dummy.bin dummy_extracted.bin
                  COMMAND ${CMAKE_COMMAND} -E compare_files ${_resources_path}/dummy.json dummy_extracted.json
                  VERBATIM)

add_custom_target(IntegrationTestWriteTextualSelfExtraction
                  COMMAND ${_command_echo_test} "Running IntegrationTestWriteTextualSelfExtraction test"

                  COMMAND ${_command_echo_action} "Preparation..."
                  COMMAND ${_command_copy_reader_executable}
                  COMMAND ${CMAKE_COMMAND} -E remove -f dummy_extracted.json

                  COMMAND ${_command_echo_action} "Writing resources"
                  COMMAND ${_resource-writer-path} ${_resource-reader-path}-for-testing .RESOURCES/3 ${_resources_path}/dummy.json

                  COMMAND ${_command_echo_action} "Reading resources (selfextraction)"
                  COMMAND ${_resource-reader-path} ${_resource-reader-path}-for-testing .RESOURCES/3 dummy_extracted.json

                  COMMAND ${_command_echo_action} "Comparing extracted files"
                  COMMAND ${CMAKE_COMMAND} -E compare_files ${_resources_path}/dummy.json dummy_extracted.json
                  VERBATIM)

if (WIN32)
    add_custom_target(IntegrationTestWriteResourceWriterIntoGitBinary
                      COMMAND ${_command_echo_test} "Running IntegrationTestWriteResourceWriterIntoGitBinary test"
                      COMMAND ${_command_echo_action} "Skipping this test, because git is not executable on its own on Windows"
                      VERBATIM)
else ()
    add_custom_target(IntegrationTestWriteResourceWriterIntoGitBinary
                      COMMAND ${_command_echo_test} "Running IntegrationTestWriteResourceWriterIntoGitBinary test"

                      COMMAND ${_command_echo_action} "Preparation..."
                      COMMAND ${_command_copy_git_executable}
                      COMMAND ${CMAKE_COMMAND} -E remove -f resource-writer_extracted

                      COMMAND ${_command_echo_action} "Writing resources"
                      COMMAND ${_resource-writer-path} ${CMAKE_CURRENT_BINARY_DIR}/git-for-testing
                                                       resource-writer ${_resource-writer-path}

                      COMMAND ${_command_echo_action} "Checking whether binary is valid (executing it)"
                      COMMAND ${CMAKE_CURRENT_BINARY_DIR}/git-for-testing --version

                      COMMAND ${_command_echo_action} "Reading resources"
                      COMMAND ${_resource-reader-path} ${CMAKE_CURRENT_BINARY_DIR}/git-for-testing
                                                       resource-writer resource-writer_extracted

                      COMMAND ${_command_echo_action} "Comparing extracted files"
                      COMMAND ${CMAKE_COMMAND} -E compare_files ${_resource-writer-path} resource-writer_extracted
                      VERBATIM)
endif ()
