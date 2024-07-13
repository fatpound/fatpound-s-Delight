#pragma once

#include <string>

namespace fatpound::file
{
    static auto GetNameAndExtension(const std::string& filename) -> std::pair<std::string, std::string>;
}