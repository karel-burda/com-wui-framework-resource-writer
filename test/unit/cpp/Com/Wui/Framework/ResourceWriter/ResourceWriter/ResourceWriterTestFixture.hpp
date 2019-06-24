/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_TEST_RESOURCEWRITERTESTFIXTURE_HPP_  // NOLINT
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_TEST_RESOURCEWRITERTESTFIXTURE_HPP_

#include <cstdio>
#include <memory>
#include <fstream>
#include <vector>

#include "../../../../../reference.hpp"

namespace Com::Wui::Framework::ResourceWriter {
    class ResourceWriterTest : public ::testing::Test {
     protected:
        static constexpr size_t numberOfResources = 256;
        static constexpr const char *smallBinaryPath = "small_binary";
        static constexpr const char *bigBinaryPath = "big_binary";

        static constexpr const char *textualResource = "../../test/resource/textual_lf.txt";
        Core::Resource::ResourceData textualResourceContent = {0};

        static constexpr const char *binaryResource = "../../test/resource/dummy.bin";
        Core::Resource::ResourceData binaryResourceContent = {0};

     private:
        void SetUp() override {
            // to enable console logs: Logger::LogManager::setLogger(Logger::LoggerConsole{});
            Logger::LogManager::setLogger(Logger::LoggerDevNull{});

            this->createBinaries();

            this->readTestResources();
        }

        void TearDown() override {
            this->checkBinaries();

            std::remove(ResourceWriterTest::smallBinaryPath);
            std::remove(ResourceWriterTest::bigBinaryPath);
        }

        void createBinaries() {
            this->createBinary(ResourceWriterTest::smallBinaryPath, 1);
            this->createBinary(ResourceWriterTest::bigBinaryPath, 1024 * 1024);
        }

        void createBinary(const std::string &$filePath, const size_t $size) {
            std::ofstream binaryStream{$filePath, std::ios::out | std::ios::binary};

            if (!binaryStream.is_open()) {
                throw std::runtime_error{"Failed to open " + $filePath + " for writing"};
            }

            std::vector<char> bytesToWrite($size, 1);
            if (!binaryStream.write(&bytesToWrite[0], bytesToWrite.size())) {
                throw std::runtime_error{"Failed to write " + std::to_string($size) + " bytes"};
            }
        }

        void checkBinaries() {
            this->checkBinary(ResourceWriterTest::smallBinaryPath, 1);
            this->checkBinary(ResourceWriterTest::bigBinaryPath, 1024 * 1024);
        }

        void checkBinary(const std::string &$filePath, const size_t $bytesToRead) {
            std::ifstream binaryStream{$filePath, std::ios::in | std::ios::binary};

            if (!binaryStream.is_open()) {
                throw std::runtime_error{"Failed to open " + $filePath + " for reading"};
            }

            std::vector<char> bytesToRead($bytesToRead, 0);
            if (!binaryStream.read(&bytesToRead[0], bytesToRead.size())) {
                throw std::runtime_error{"Failed to read " + std::to_string($bytesToRead) + " bytes"};
            }

            for (size_t i = 0; i < bytesToRead.size(); ++i) {
                if (bytesToRead[i] != 1) {
                    throw std::runtime_error{"Binary at path " + $filePath + " has incorrect content on byte " + std::to_string(i)};
                }
            }
        }

        void readTestResources() {
            {
                std::ifstream textualResourceStream{textualResource, std::ios::in};

                if (!textualResourceStream.is_open()) {
                    throw std::runtime_error{"Failed to read textual resource"};
                }

                ResourceWriterTest::textualResourceContent = decltype(ResourceWriterTest::textualResourceContent)
                        {(std::istreambuf_iterator<char>(textualResourceStream)), std::istreambuf_iterator<char>()};
            }

            {
                std::ifstream binaryResourceStream{binaryResource, std::ios::in | std::ios::binary};

                if (!binaryResourceStream.is_open()) {
                    throw std::runtime_error{"Failed to read binary resource"};
                }

                ResourceWriterTest::binaryResourceContent = decltype(ResourceWriterTest::binaryResourceContent)
                        {(std::istreambuf_iterator<char>(binaryResourceStream)), std::istreambuf_iterator<char>()};
            }
        }
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_TEST_RESOURCEWRITERTESTFIXTURE_HPP_  NOLINT
