/* ********************************************************************************************************* *
 *
 * Copyright (c) 2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * The BSD-3-Clause license for this file can be found in the LICENSE.txt file included with this distribution
 * or at https://spdx.org/licenses/BSD-3-Clause.html#licenseText
 *
 * ********************************************************************************************************* */

#ifndef COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_RESOURCE_HPP_
#define COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_RESOURCE_HPP_

#include <fstream>
#include <string>
#include <vector>

#include "Protocol.hpp"

namespace Com::Wui::Framework::ResourceWriter::Core {
    class Resource {
     public:
        using ResourceData = Core::Protocol::Types::Data;

        using ResourceCompressionSize = std::uint8_t;

        using ResourceNameSize = std::uint16_t;

        using ResourceDataSize = std::uint32_t;

        enum class CompressionType : std::uint8_t {
            NONE = 0,
            ZIP = 1
        };

        Resource() = default;

        explicit Resource(std::string $contentPath, CompressionType $compression = CompressionType::NONE);

        // Enabled for neat usage via initializer lists (these have to copy)
        Resource(const Resource &$other) = default;

        Resource(Resource&& $other) = default;

        Resource& operator=(const Resource &$other) = delete;

        Resource& operator=(Resource&& $other) = default;

        bool operator==(const Resource &$other) const;

        bool isEmpty() const;

        std::string getName() const;

        std::string &&moveName();

        std::string getContentPath() const;

        CompressionType getCompression() const;

        Resource::ResourceData getData() const;

        void setName(const std::string &$name);

     private:
        void setName(Core::Protocol::Types::Data $bytes);

        template<typename T>
        void Read(std::ifstream &$stream, T $value, size_t $size) {
            if (!$stream.read(reinterpret_cast<char *>($value), $size)) {
                throw std::runtime_error{"Failed to read content of size " + std::to_string($size)};
            }
        }

        template<typename T>
        void Write(std::ofstream &$stream, T $value, size_t $size) {
            if (!$stream.write(reinterpret_cast<const char *>($value), $size)) {
                throw std::runtime_error{"Failed to write content of size " + std::to_string($size)};
            }
        }

        std::string name;
        std::string contentPath;
        CompressionType compression = CompressionType::NONE;
        ResourceData data;

        friend std::ostream &operator<<(std::ostream &$stream, const Resource &$resource);
        friend std::ifstream &operator>>(std::ifstream &$stream, Resource &$resource);
        friend std::ofstream &operator<<(std::ofstream &$stream, Resource &&$resource);
    };
}

#endif  // COM_WUI_FRAMEWORK_RESOURCEWRITER_CORE_RESOURCE_HPP_
