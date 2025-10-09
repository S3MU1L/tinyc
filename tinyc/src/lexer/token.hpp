#pragma once
#include "token_type.hpp"

#include <string>
#include <variant>

namespace tinyc::lexer {
using Literal = std::variant<std::string, unsigned long long, long long, bool>;

struct Token
{
    TokenType   type;
    Literal     literal;
    std::string lexeme;
    int         line;
};
}