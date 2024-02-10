#pragma once

#include <string>
#include <filesystem>
#include <exception>
#include <stdexcept>

namespace fatpound::file
{
    static std::pair<std::string, std::string> GetNameAndExtensionFromFilename(const std::string& filename)
    {
        if (std::filesystem::is_regular_file(filename))
        {
            const auto it = std::find(filename.rbegin(), filename.rend(), '.');
            size_t dot_index = 0u;

            if (it != filename.rend())
            {
                dot_index = it - filename.rbegin() + 1u;
            }

            return {
                std::string(filename.cbegin(), filename.cend() - dot_index),
                std::string(_strrev(const_cast<char*>(std::string(filename.rbegin(), it).c_str())))
            };
        }
        else
        {
            throw std::invalid_argument("The given path is not pointing to a file!");
        }
    }
}