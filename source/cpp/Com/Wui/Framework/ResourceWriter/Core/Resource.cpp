/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <ostream>

#include "../Logger/LogManager.hpp"
#include "../Utils/ByteUtils.hpp"

#include "Resource.hpp"

#include "Detail/BinaryReader.hpp"

namespace Com::Wui::Framework::ResourceWriter::Core {
    Resource::Resource(std::string $contentPath, CompressionType $compression)
        : contentPath(std::move($contentPath)),
          compression($compression) {
        if (!this->contentPath.empty()) {
            Detail::BinaryReader reader{this->contentPath};

            this->data = reader.getContents();
        }
    }

    bool Resource::operator==(const Resource &$other) const {
        return $other.getName() == this->getName();
    }

    bool Resource::isEmpty() const {
        return this->name.empty() && this->data.empty();
    }

    std::string Resource::getName() const {
        return this->name;
    }

    std::string &&Resource::moveName() {
        return std::move(this->name);
    }

    std::string Resource::getContentPath() const {
        return this->contentPath;
    }

    Resource::CompressionType Resource::getCompression() const {
        return this->compression;
    }

    Resource::ResourceData Resource::getData() const {
        return this->data;
    }

    void Resource::setName(const std::string &$name) {
        this->name = $name;
    }

    void Resource::setName(Core::Protocol::Types::Data $bytes) {
        auto bytes = std::move($bytes);

        this->name.assign(std::cbegin(bytes), std::cend(bytes));
    }

    std::ostream &operator<<(std::ostream &$stream, const Resource &$resource) {
        $stream << "name=" << $resource.name;

        if (!$resource.contentPath.empty()) {
            $stream << ", content path=" << $resource.contentPath;
        }

        if (!$resource.data.empty()) {
            $stream << ", content size=" << $resource.data.size();
        }

        return $stream;
    }

    std::ofstream &operator<<(std::ofstream &$stream, Resource &&$resource) {
        Logger::LogManager::getLogger().Info("Writing resource " + $resource.getName());

        const auto nameSize = static_cast<Resource::ResourceNameSize>($resource.name.size());
        const auto compressionSize = sizeof(Resource::CompressionType);
        const auto dataSize = static_cast<Resource::ResourceDataSize>($resource.data.size());

        $resource.Write($stream, &nameSize, sizeof(nameSize));
        $resource.Write($stream, $resource.name.c_str(), nameSize);

        $resource.Write($stream, &$resource.compression, compressionSize);

        $resource.Write($stream, &dataSize, sizeof(dataSize));
        $resource.Write($stream, $resource.data.data(), dataSize);

        return $stream;
    }

    std::ifstream &operator>>(std::ifstream &$stream, Resource &$resource) {
        Logger::LogManager::getLogger().Debug("Reading and parsing resource");

        Resource::ResourceNameSize nameSize = 0;
        $resource.Read($stream, &nameSize, sizeof(nameSize));
        Logger::LogManager::getLogger().Debug("Size of name: " + std::to_string(nameSize));

        Core::Protocol::Types::Data resourceNameBuffer(nameSize, 0);
        $resource.Read($stream, resourceNameBuffer.data(), resourceNameBuffer.size());

        Resource::CompressionType compression = Resource::CompressionType::NONE;
        $resource.Read($stream, &compression, sizeof(compression));
        Logger::LogManager::getLogger().Debug("Compression type: " + std::to_string(static_cast<unsigned char>(compression)));

        Core::Protocol::Types::Data resourceDataLengthBuffer(sizeof(Resource::ResourceDataSize), 0);
        $resource.Read($stream, resourceDataLengthBuffer.data(), resourceDataLengthBuffer.size());
        Logger::LogManager::getLogger().Debug("Data length: " + std::to_string(resourceDataLengthBuffer.size()));

        const auto resourceDataSize = Utils::ByteUtils::GetNumberFromByteArrayLE<Resource::ResourceDataSize>(
                resourceDataLengthBuffer);
        Core::Protocol::Types::Data resourceData(resourceDataSize, 0);
        $resource.Read($stream, resourceData.data(), resourceData.size());
        Logger::LogManager::getLogger().Debug("Data size: " + std::to_string(resourceDataSize));

        $resource.setName(std::move(resourceNameBuffer));
        $resource.compression = compression;
        $resource.data = std::move(resourceData);

        return $stream;
    }
}
