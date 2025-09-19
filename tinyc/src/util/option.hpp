#pragma once
#include <string>

namespace tinyc::util {
struct Option
{
    bool        help_mode;
    bool        version_mode;
    std::string input_file;
    std::string output_file;
};
};