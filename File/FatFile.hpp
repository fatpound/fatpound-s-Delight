#pragma once

#include <string>

namespace fatpound::file
{
    std::pair<std::string, std::string> GetNameAndExtensionFromFilename(const std::string& filename)
    {
        const auto dot_it = std::find(filename.rbegin(), filename.rend(), '.');
        size_t dot_index = 0u;

        if (dot_it != filename.rend())
        {
            dot_index = dot_it - filename.rbegin() + 1u;
        }

        return {
            std::string(filename.cbegin(), filename.cend() - dot_index),
            std::string(_strrev(const_cast<char*>(std::string(filename.rbegin(), dot_it).c_str())))
        };
    }
}
