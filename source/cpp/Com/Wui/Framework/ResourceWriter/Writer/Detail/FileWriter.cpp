/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#include <stdexcept>

#include "../../Logger/LogManager.hpp"

#include "FileWriter.hpp"

namespace Com::Wui::Framework::ResourceWriter::Writer::Detail {
    FileWriter::FileWriter(const std::string &$path, const Core::Protocol::Types::ContentOffset $contentOffset)
            : contentOffset($contentOffset) {
        Logger::LogManager::getLogger().Info("Writing to file " + $path + ", content offset=" + std::to_string($contentOffset));

        this->stream.open($path.c_str(), std::ios::app | std::ios::binary);

        if (!this->stream.is_open()) {
            throw std::runtime_error{"File " + $path + " cannot be opened for writing"};
        }
    }

    void FileWriter::Write(Core::Resource &&$resource) {
        this->stream << std::move($resource);
    }

    void FileWriter::WriteProtocolVersion() {
        Logger::LogManager::getLogger().Info("Writing protocol version: " + std::to_string(Core::Protocol::Constants::ProtocolVersion));

        if (!this->stream.write(reinterpret_cast<const char *>(&Core::Protocol::Constants::ProtocolVersion),
                                sizeof(Core::Protocol::Types::Version))) {
            throw std::runtime_error{"Failed to write the protocol version"};
        }
    }

    void FileWriter::Close() {
        this->writeOffset();
        this->writeMagicSequence();
    }

    void FileWriter::writeOffset() {
        Logger::LogManager::getLogger().Debug("Writing offset " + std::to_string(this->contentOffset));

        if (!this->stream.write(reinterpret_cast<char *>(&this->contentOffset), sizeof(this->contentOffset))) {
            throw std::runtime_error{"Failed to write the offset where injected content starts"};
        }
    }

    void FileWriter::writeMagicSequence() {
        Logger::LogManager::getLogger().Debug("Writing magic sequence");

        if (!this->stream.write(Core::Protocol::Constants::MagicSequence, sizeof(Core::Protocol::Types::MagicSequence))) {
            throw std::runtime_error{"Failed to write the magic sequence"};
        }
    }
}
