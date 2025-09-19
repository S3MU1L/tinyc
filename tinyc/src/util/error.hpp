#pragma once
#include <stdexcept>

namespace tinyc {
struct ParseError final : std::runtime_error
{
    explicit ParseError(const std::string &message)
        : std::runtime_error(message)
    {
    }
};
}