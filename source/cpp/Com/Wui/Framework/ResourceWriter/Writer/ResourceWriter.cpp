/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <utility>

#include "../Logger/LogManager.hpp"
#include "../Reader/FileReader.hpp"
#include "../Reader/ResourceReader.hpp"
#include "../Utils/CollectionUtils.hpp"
#include "../Utils/FileUtils.hpp"

#include "ResourceWriter.hpp"

#include "Detail/FileWriter.hpp"

namespace Com::Wui::Framework::ResourceWriter::Writer {
    ResourceWriter::ResourceWriter(Settings $settings)
            : settings(std::move($settings)) {
    }

    void ResourceWriter::Write(ResourceMap $resources) {
        auto resourcesToWrite = std::move($resources);

        if (!resourcesToWrite.empty()) {
            Logger::LogManager::getLogger().Info("Writing " + std::to_string(resourcesToWrite.size()) + " resources");

            Reader::FileReader fileReader{this->settings.getOutputFilePath(), false};
            fileReader.Close();

            if (!fileReader.isVanillaFile()) {
                Logger::LogManager::getLogger().Debug("Will truncate the file");

                Utils::FileUtils::truncateFile(this->settings.getOutputFilePath(), fileReader.getContentEnd());
            }

            Detail::FileWriter fileWriter{this->settings.getOutputFilePath(), fileReader.getContentOffset()};

            if (fileReader.isVanillaFile()) {
                fileWriter.WriteProtocolVersion();
            }

            std::for_each(std::begin(resourcesToWrite), std::end(resourcesToWrite), [&fileWriter](auto &resource) {
                resource.second.setName(resource.first);

                fileWriter.Write(std::move(resource.second));
            });

            fileWriter.Close();
        }
    }

    void ResourceWriter::Update(ResourceMap $resources) {
        this->update(std::move($resources), WriteMethod::UPDATE);
    }

    void ResourceWriter::UpdateOrWrite(ResourceMap $resources) {
        this->update(std::move($resources), WriteMethod::UPDATE_OR_WRITE);
    }

    void ResourceWriter::update(ResourceMap $resources, const WriteMethod $method) {
        auto resourcesToUpdate = std::move($resources);

        if (!resourcesToUpdate.empty()) {
            Logger::LogManager::getLogger().Info("Updating " + std::to_string(resourcesToUpdate.size()) + " resources");

            Reader::Settings settings{this->settings.getOutputFilePath()};
            Reader::ResourceReader resourceReader{std::move(settings)};

            ResourceMap existingResources;
            decltype(existingResources) additionalResourcesToWrite;

            // Might happen that the file is untouched by the resource-writer
            try {
                existingResources = resourceReader.Read();
            } catch (const Reader::ProtocolError &) {
                if ($method != WriteMethod::UPDATE_OR_WRITE) {
                    throw;
                }
            }

            Logger::LogManager::getLogger().Debug("Found " + std::to_string(existingResources.size()) + " existing resources");

            std::for_each(std::begin(resourcesToUpdate), std::end(resourcesToUpdate), [&existingResources](auto &resource) {
                auto existingResource = std::find(std::begin(existingResources), std::end(existingResources), resource);
                if (existingResource != std::end(existingResources)) {
                    Logger::LogManager::getLogger().Info("Updating resource " + existingResource->second.getName());
                    existingResource->second = std::move(resource.second);
                }
            });

            if ($method == WriteMethod::UPDATE_OR_WRITE) {
                Logger::LogManager::getLogger().Debug("Preparing rest of resources to write");

                std::for_each(std::begin(resourcesToUpdate), std::end(resourcesToUpdate), [&additionalResourcesToWrite](auto &&resource) {
                    if (!resource.second.isEmpty()) {
                        additionalResourcesToWrite.emplace(std::make_pair(std::move(resource.first), std::move(resource.second)));
                    }
                });
            }

            Utils::CollectionUtils::ConcatenateHashMaps(existingResources, additionalResourcesToWrite);

            // TODO(nxf45876): This was already done by the ResourceReader during reading of resources, optimize
            Reader::FileReader fileReader{this->settings.getOutputFilePath(), false};
            fileReader.Close();

            Utils::FileUtils::truncateFile(this->settings.getOutputFilePath(), fileReader.getContentOffset());

            this->Write(std::move(existingResources));
        }
    }
}
