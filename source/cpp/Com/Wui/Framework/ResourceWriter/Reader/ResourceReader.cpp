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
#include <cstdint>
#include <stdexcept>

#include "../Logger/LogManager.hpp"

#include "FileReader.hpp"
#include "ResourceReader.hpp"

namespace Com::Wui::Framework::ResourceWriter::Reader {
    ResourceReader::ResourceReader(Settings $settings)
            : settings(std::move($settings)) {
    }

    ResourceMap ResourceReader::Read(const size_t $numberOfBuckets) {
        ResourceMap resourcesToReturn{$numberOfBuckets};

        FileReader reader{this->settings.getInputFilePath(), true};
        reader.ReadResources([&resourcesToReturn](Core::Resource &&$foundResource) {
            auto extractedResource = std::move($foundResource);

            Logger::LogManager::getLogger().Info("Inspecting resource " + extractedResource.getName());

            resourcesToReturn.emplace(std::make_pair(extractedResource.moveName(), std::move(extractedResource)));
        });

        return resourcesToReturn;
    }
}
