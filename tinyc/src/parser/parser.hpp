#pragma once

#include "stmt.hpp"
#include "../lexer/token.hpp"

#include <vector>

namespace tinyc::parser {

struct Parser
{
    int start   = 0;
    int current = 0;

    std::vector<Stmt>         statements = {};
    std::vector<lexer::Token> tokens;

    explicit                   Parser(const std::vector<lexer::Token> &tokens);
    lexer::Token               advance();
    [[nodiscard]] bool         check(lexer::TokenType type) const;
    bool                       match(lexer::TokenType type);
    [[nodiscard]] bool         is_end() const;
    [[nodiscard]] lexer::Token peek() const;
    [[nodiscard]] lexer::Token previous() const;
    lexer::Token               consume(lexer::TokenType type, const char *message);
    lexer::Token               consume_any(const std::vector<lexer::TokenType> &types,
                                          const std::string                   & message);
    void                       parse();
    void                       synchronize();
    void                       top_level();
    void                       declaration();
    void                       function_definition();
    void                       struct_declaration();
    void error(const lexer::Token & peek, const char * message);
};

}