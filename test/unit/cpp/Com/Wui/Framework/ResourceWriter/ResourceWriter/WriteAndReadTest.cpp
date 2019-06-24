/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <fstream>

#include "../../../../../reference.hpp"

#include "ResourceWriterTestFixture.hpp"

namespace Com::Wui::Framework::ResourceWriter {
    TEST_F(ResourceWriterTest, SmallBinary) {
        {
            Writer::Settings settings{ResourceWriterTest::smallBinaryPath};
            Writer::ResourceMap resourcesToWrite = {
                    {"dummy1", Writer::Resource{ResourceWriterTest::textualResource}}};
            const auto resourceWriter = std::make_unique<Writer::ResourceWriter>(std::move(settings));
            resourceWriter->Write(std::move(resourcesToWrite));
        }

        {
            Writer::Settings settings{ResourceWriterTest::smallBinaryPath};
            Writer::ResourceMap resourcesToWrite = {
                    {"dummy2", Writer::Resource{ResourceWriterTest::binaryResource, Writer::Resource::CompressionType::ZIP}}};
            const auto resourceWriter = std::make_unique<Writer::ResourceWriter>(std::move(settings));
            resourceWriter->Write(std::move(resourcesToWrite));
        }

        {
            Reader::Settings settings{ResourceWriterTest::smallBinaryPath};
            const auto resourceReader = std::make_unique<Reader::ResourceReader>(std::move(settings));
            auto extractedResources = resourceReader->Read(2);

            ASSERT_EQ(extractedResources.size(), static_cast<Reader::ResourceMap::size_type>(2));

            EXPECT_EQ(extractedResources["dummy1"].getName(), "");
            EXPECT_EQ(extractedResources["dummy1"].getCompression(), Reader::Resource::CompressionType::NONE);
            EXPECT_TRUE(extractedResources["dummy1"].getContentPath().empty());
            EXPECT_EQ(extractedResources["dummy1"].getData(), ResourceWriterTest::textualResourceContent);

            EXPECT_EQ(extractedResources["dummy2"].getName(), "");
            EXPECT_EQ(extractedResources["dummy2"].getCompression(), Reader::Resource::CompressionType::ZIP);
            EXPECT_TRUE(extractedResources["dummy2"].getContentPath().empty());
            EXPECT_EQ(extractedResources["dummy2"].getData(), ResourceWriterTest::binaryResourceContent);
        }


        {
            Writer::Settings settings{ResourceWriterTest::smallBinaryPath};
            Writer::ResourceMap resourcesToUpdate = {
                    {"dummy2", Writer::Resource{ResourceWriterTest::textualResource, Writer::Resource::CompressionType::NONE}}};
            const auto resourceWriter = std::make_unique<Writer::ResourceWriter>(std::move(settings));
            resourceWriter->Update(std::move(resourcesToUpdate));
        }

        {
            Reader::Settings settings{ResourceWriterTest::smallBinaryPath};
            const auto resourceReader = std::make_unique<Reader::ResourceReader>(std::move(settings));
            auto extractedResources = resourceReader->Read();

            ASSERT_EQ(extractedResources.size(), static_cast<Reader::ResourceMap::size_type>(2));

            EXPECT_EQ(extractedResources["dummy1"].getName(), "");
            EXPECT_EQ(extractedResources["dummy1"].getCompression(), Reader::Resource::CompressionType::NONE);
            EXPECT_TRUE(extractedResources["dummy1"].getContentPath().empty());
            EXPECT_EQ(extractedResources["dummy1"].getData(), ResourceWriterTest::textualResourceContent);

            EXPECT_EQ(extractedResources["dummy2"].getName(), "");
            EXPECT_EQ(extractedResources["dummy2"].getCompression(), Reader::Resource::CompressionType::NONE);
            EXPECT_TRUE(extractedResources["dummy2"].getContentPath().empty());
            EXPECT_EQ(extractedResources["dummy2"].getData(), ResourceWriterTest::textualResourceContent);
        }
    }

    TEST_F(ResourceWriterTest, BigBinary) {
        {
            Writer::Settings settings{ResourceWriterTest::bigBinaryPath};
            Writer::ResourceMap resourcesToUpdate = {
                    {"foo", Writer::Resource{ResourceWriterTest::textualResource, Writer::Resource::CompressionType::ZIP}}};
            const auto resourceWriter = std::make_unique<Writer::ResourceWriter>(std::move(settings));
            resourceWriter->UpdateOrWrite(std::move(resourcesToUpdate));
        }

        {
            Reader::Settings settings{ResourceWriterTest::bigBinaryPath};
            const auto resourceReader = std::make_unique<Reader::ResourceReader>(std::move(settings));
            auto extractedResources = resourceReader->Read(1);

            EXPECT_EQ(extractedResources["foo"].getName(), "");
            EXPECT_EQ(extractedResources["foo"].getCompression(), Reader::Resource::CompressionType::ZIP);
            EXPECT_TRUE(extractedResources["foo"].getContentPath().empty());
            EXPECT_EQ(extractedResources["foo"].getData(), ResourceWriterTest::textualResourceContent);
        }

        {
            Writer::Settings settings{ResourceWriterTest::bigBinaryPath};
            Writer::ResourceMap resourcesToWrite;
            resourcesToWrite.reserve(ResourceWriterTest::numberOfResources);
            for (size_t i = 0; i < ResourceWriterTest::numberOfResources; ++i) {
                resourcesToWrite.emplace(std::make_pair("textual-" + std::to_string(i),
                                                        Writer::Resource{ResourceWriterTest::textualResource,
                                                                         Writer::Resource::CompressionType::ZIP}));
                resourcesToWrite.emplace(std::make_pair("binary-" + std::to_string(i),
                                                        Writer::Resource{ResourceWriterTest::binaryResource}));
            }
            const auto resourceWriter = std::make_unique<Writer::ResourceWriter>(std::move(settings));
            resourceWriter->Write(std::move(resourcesToWrite));
        }

        {
            Writer::Settings settings{ResourceWriterTest::bigBinaryPath};
            Writer::ResourceMap resourcesToWrite = {{"dummy1", Writer::Resource{ResourceWriterTest::textualResource}}};
            const auto resourceWriter = std::make_unique<Writer::ResourceWriter>(std::move(settings));
            resourceWriter->Write(std::move(resourcesToWrite));
        }

        {
            Reader::Settings settings{ResourceWriterTest::bigBinaryPath};
            Reader::ResourceMap resourcesToRead;
            const auto resourceReader = std::make_unique<Reader::ResourceReader>(std::move(settings));
            auto extractedResources = resourceReader->Read();

            ASSERT_EQ(extractedResources.size(), static_cast<Reader::ResourceMap::size_type>(514));

            EXPECT_EQ(extractedResources["textual-0"].getName(), "");
            EXPECT_EQ(extractedResources["textual-0"].getCompression(), Reader::Resource::CompressionType::ZIP);
            EXPECT_TRUE(extractedResources["textual-0"].getContentPath().empty());
            EXPECT_EQ(extractedResources["textual-0"].getData(), ResourceWriterTest::textualResourceContent);

            EXPECT_EQ(extractedResources["textual-254"].getName(), "");
            EXPECT_EQ(extractedResources["textual-254"].getCompression(), Reader::Resource::CompressionType::ZIP);
            EXPECT_TRUE(extractedResources["textual-254"].getContentPath().empty());
            EXPECT_EQ(extractedResources["textual-254"].getData(), ResourceWriterTest::textualResourceContent);

            EXPECT_EQ(extractedResources["binary-255"].getName(), "");
            EXPECT_EQ(extractedResources["binary-255"].getCompression(), Reader::Resource::CompressionType::NONE);
            EXPECT_TRUE(extractedResources["binary-255"].getContentPath().empty());
            EXPECT_EQ(extractedResources["binary-255"].getData(), ResourceWriterTest::binaryResourceContent);

            EXPECT_EQ(extractedResources["dummy1"].getName(), "");
            EXPECT_EQ(extractedResources["dummy1"].getCompression(), Reader::Resource::CompressionType::NONE);
            EXPECT_TRUE(extractedResources["dummy1"].getContentPath().empty());
            EXPECT_EQ(extractedResources["dummy1"].getData(), ResourceWriterTest::textualResourceContent);
        }

        {
            Writer::Settings settings{ResourceWriterTest::bigBinaryPath};
            Writer::ResourceMap resourcesToUpdate = {
                    {"binary-255", Writer::Resource{ResourceWriterTest::textualResource, Writer::Resource::CompressionType::ZIP}},
                    {"boo", Writer::Resource{ResourceWriterTest::textualResource, Writer::Resource::CompressionType::ZIP}}};
            const auto resourceWriter = std::make_unique<Writer::ResourceWriter>(std::move(settings));
            resourceWriter->UpdateOrWrite(std::move(resourcesToUpdate));
        }

        {
            Reader::Settings settings{ResourceWriterTest::bigBinaryPath};
            const auto resourceReader = std::make_unique<Reader::ResourceReader>(std::move(settings));
            auto extractedResources = resourceReader->Read();

            EXPECT_EQ(extractedResources["binary-255"].getName(), "");
            EXPECT_EQ(extractedResources["binary-255"].getCompression(), Reader::Resource::CompressionType::ZIP);
            EXPECT_TRUE(extractedResources["binary-255"].getContentPath().empty());
            EXPECT_EQ(extractedResources["binary-255"].getData(), ResourceWriterTest::textualResourceContent);

            EXPECT_EQ(extractedResources["boo"].getName(), "");
            EXPECT_EQ(extractedResources["boo"].getCompression(), Reader::Resource::CompressionType::ZIP);
            EXPECT_TRUE(extractedResources["boo"].getContentPath().empty());
            EXPECT_EQ(extractedResources["boo"].getData(), ResourceWriterTest::textualResourceContent);
        }
    }
}
