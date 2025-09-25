#pragma once
#include "option.hpp"

#include <stdexcept>
#include <string>

namespace tinyc::common {

struct ArgsParser
{
    static Option parse(const int argc, char **argv)
    {
        Option opt{};
        opt.help_mode    = false;
        opt.version_mode = false;
        opt.input_file.clear();
        opt.output_file.clear();

        if (argc < 2)
            throw std::runtime_error("Usage tinyc <source_file> [-o output] [-h --help]");
        for (int i = 1; i < argc; ++i)
        {
            if (std::string arg = argv[i]; arg == "-h" || arg == "--help")
                opt.help_mode   = true;
            else if (arg == "-v" || arg == "--version")
                opt.version_mode = true;
            else if (arg == "-o")
            {
                if (i + 1 < argc)
                    opt.output_file = argv[++i];
                else
                    throw std::runtime_error("Error: -o option requires an argument");
            }
            else if (arg[0] == '-')
                throw std::runtime_error("Error: Unknown option " + arg);
            else
            {
                if (opt.input_file.empty())
                    opt.input_file = arg;
                else
                    throw std::runtime_error("Error: Multiple input files specified");
            }
        }
        return opt;
    }
};
};