#include "File.hpp"

#include <algorithm>
#include <filesystem>
#include <stdexcept>
#include <ranges>

namespace rn = std::ranges;

namespace fatpound::file
{
    auto GetNameAndExtension(const std::string& filename) -> std::pair<std::string, std::string>
    {
        if (std::filesystem::is_regular_file(filename))
        {
            const auto it = std::find(filename.rbegin(), filename.rend(), '.');
            std::int64_t dot_index = 0;

            if (it != filename.rend())
            {
                dot_index = it - filename.rbegin() + 1;
            }

            auto&& temp_revstr = std::string(filename.rbegin(), it);

            rn::reverse(temp_revstr);

            return {
                std::string(filename.cbegin(), filename.cend() - dot_index),
                std::string(temp_revstr)
            };
        }
        else
        {
            throw std::runtime_error("The given path is not pointing to a file!");
        }
    }
}