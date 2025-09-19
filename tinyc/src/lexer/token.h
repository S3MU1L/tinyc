#pragma once
#include "token_type.h"

#include <string>
#include <variant>

namespace tinyc::lexer {
using Literal = std::variant<unsigned long long, long long, bool>;

struct Token
{
    TokenType   type;
    Literal     literal;
    std::string lexeme;
    int         line;
};
}