#pragma once
#include "file_util.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <llvm/Support/raw_ostream.h>

namespace tinyc::common {
struct FileUtil
{
    static std::string get_file_name(const std::string& file_path)
    {
        const std::size_t last_slash = file_path.rfind('/');
        if (last_slash == std::string::npos)
            return file_path;
        return file_path.substr(last_slash + 1);
    }

    static void check_file(const std::string &file_name)
    {
        const std::size_t last_dot = file_name.rfind('.');
        if (last_dot == std::string::npos)
            throw std::runtime_error("Could not find dot '" + file_name + "'");

        const std::string substr = file_name.substr(last_dot);
        if (substr != ".c")
            throw std::runtime_error("Only support .c files, but got '" + substr + "'");
    }

    static std::string read_file(const std::string &file_path)
    {
        std::ifstream file(file_path, std::ios::in);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + file_path);

        std::stringstream sstream;
        sstream << file.rdbuf();
        return sstream.str();
    }

    static void writeLLVMFiles(llvm::Module &M, const std::string &base_name)
    {
        std::error_code EC;
        std::string     file_name = base_name;
        if (file_name.empty())
            file_name = "a";

        const std::string    llFile = file_name + ".ll";
        llvm::raw_fd_ostream llOut(llFile, EC);
        if (EC)
            llvm::errs() << "Cannot open " << llFile << ": " << EC.message() << "\n";
        else
        {
            M.print(llOut, nullptr);
            llOut.close();
        }
    }
};
};