/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <cstring>
#include <stdexcept>

#include "../Core/Protocol.hpp"
#include "../Logger/LogManager.hpp"
#include "../Utils/ByteUtils.hpp"

#include "FileReader.hpp"

namespace Com::Wui::Framework::ResourceWriter::Reader {
    FileReader::FileReader(const std::string &$path, const bool $magicSequenceRequired) {
        Logger::LogManager::getLogger().Info("Reading file " + $path);

        this->stream = std::ifstream($path, std::ios::in | std::ios::binary | std::ios::ate);

        if (!this->stream.is_open()) {
            throw std::runtime_error{"Could not open file " + $path + " for reading"};
        }

        this->fileSize = this->contentOffset = this->contentEnd = static_cast<decltype(this->fileSize)>(this->stream.tellg());
        Logger::LogManager::getLogger().Debug("Detected file size: " + std::to_string(this->fileSize));

        try {
            this->readMagicSequence();
            this->readContentOffset();
        } catch (const ProtocolError &error) {
            if ($magicSequenceRequired) {
                Logger::LogManager::getLogger().Debug("Magic sequence is mandatory, re-throwing exception");
                throw;
            }
        }
    }

    void FileReader::ReadResources(ResourceInspectCallback &&$resourceFoundCallback) {
        if ($resourceFoundCallback == nullptr) {
            throw std::runtime_error{"Resource inspect callback cannot be null"};
        }

        this->readProtocolVersion();

        while (this->stream.good()) {
            if (static_cast<size_t>(this->stream.tellg()) >= (this->fileSize - Core::Protocol::Constants::FooterSize)) {
                break;
            }

            Core::Resource resource;
            this->stream >> resource;

            $resourceFoundCallback(std::move(resource));
        }
    }

    bool FileReader::isVanillaFile() const {
        return this->contentOffset == this->contentEnd;
    }

    Core::Protocol::Types::ContentOffset FileReader::getContentOffset() const {
        return this->contentOffset;
    }

    Core::Protocol::Types::FileOffset FileReader::getContentEnd() const {
        return this->contentEnd;
    }

    void FileReader::Close() {
        this->stream.close();
    }

    void FileReader::readProtocolVersion() {
        this->stream.seekg(this->contentOffset, std::ios_base::beg);

        Core::Protocol::Types::Version protocolVersion = 0;
        if (this->stream.read(reinterpret_cast<char *>(&protocolVersion), sizeof(protocolVersion))) {
            Logger::LogManager::getLogger().Debug("Detected protocol version: " + std::to_string(protocolVersion));

            if (protocolVersion != Core::Protocol::Constants::ProtocolVersion) {
                throw std::runtime_error{"Unable to read this version of protocol"};
            }
        } else {
            throw std::runtime_error{"Failed to read protocol version offset"};
        }
    }

    void FileReader::readMagicSequence() {
        if (this->fileSize >= Core::Protocol::Constants::HeaderSize) {
            this->stream.seekg(-sizeof(Core::Protocol::Types::MagicSequence), std::ios_base::end);
            Core::Protocol::Types::MagicSequence magicSequenceBuffer = {0};
            if (this->stream.read(magicSequenceBuffer, sizeof(magicSequenceBuffer))) {
                Logger::LogManager::getLogger().Info("Magic sequence read");

                if (std::memcmp(magicSequenceBuffer, Core::Protocol::Constants::MagicSequence,
                                sizeof(Core::Protocol::Types::MagicSequence)) == 0) {
                    Logger::LogManager::getLogger().Info("Magic sequence successfully validated");
                } else {
                    throw MagicSequenceError{"Failed to validate the magic sequence"};
                }
            } else {
                throw MagicSequenceError{"Failed to read the magic sequence"};
            }
        } else {
            throw ProtocolError{"File size is too small"};
        }
    }

    void FileReader::readContentOffset() {
        this->stream.seekg(-Core::Protocol::Constants::FooterSize, std::ios_base::end);
        Core::Protocol::Types::Data contentOffsetBuffer(sizeof(this->contentOffset), 0);
        if (this->stream.read(contentOffsetBuffer.data(), sizeof(this->contentOffset))) {
            this->contentOffset = Utils::ByteUtils::GetNumberFromByteArrayLE<decltype(this->contentOffset)>(contentOffsetBuffer);
        } else {
            throw ContentOffsetError{"Failed to read content offset"};
        }

        this->stream.seekg(-Core::Protocol::Constants::FooterSize, std::ios_base::end);
        this->contentEnd = static_cast<decltype(this->contentEnd)>(this->stream.tellg());
    }
}
