#pragma once
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

namespace tinyc::util {
struct FileUtil
{
    static void check_file(const std::string &file_name)
    {
        const std::size_t last_dot = file_name.rfind('.');
        if (last_dot == std::string::npos)
            throw std::runtime_error("Could not find dot '" + file_name + "'");

        const std::string substr = file_name.substr(last_dot);
        if (substr != ".c")
            throw std::runtime_error("Only support .c files, but got '" + substr + "'");
    }

    static std::string read_file(const std::string &filePath)
    {
        std::ifstream file(filePath, std::ios::in);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filePath);

        std::stringstream sstream;
        sstream << file.rdbuf();
        return sstream.str();
    }
};
};