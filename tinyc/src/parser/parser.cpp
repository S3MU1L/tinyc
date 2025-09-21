#include "parser.hpp"

#include <iostream>

namespace tinyc::parser {

using TT = lexer::TokenType;


// TODO: add diagnostics as in lexer and add parsing logic
Parser::Parser(const std::vector<lexer::Token> &tokens) : tokens(tokens)
{
}

lexer::Token Parser::advance()
{
    if (!is_end())
        current++;
    return previous();
}

bool Parser::check(const lexer::TokenType type) const
{
    if (is_end())
        return false;
    return tokens[current].type == type;
}

bool Parser::match(const lexer::TokenType type)
{
    if (check(type))
    {
        advance();
        return true;
    }
    return false;
}

bool Parser::is_end() const
{
    return tokens.empty() || tokens[current].type == TT::END_OF_FILE;
}

lexer::Token Parser::peek() const
{
    if (tokens.empty())
        return lexer::Token{TT::END_OF_FILE, {}, "", 0};
    return tokens[current];
}

lexer::Token Parser::previous() const
{
    if (current == 0)
        return tokens[0];
    return tokens[current - 1];
}

lexer::Token Parser::consume(lexer::TokenType type, const char *message)
{
    if (check(type))
        return advance();
    error(peek(), message);

    return lexer::Token{TT::END_OF_FILE, {}, "", 0};
}

lexer::Token Parser::consume_any(const std::vector<lexer::TokenType> &types,
                                 const std::string &                  message)
{
    for (const auto &type : types)
    {
        if (check(type))
            return advance();
    }
    error(peek(), message.c_str());
    return lexer::Token{TT::END_OF_FILE, {}, "", 0};
}


void Parser::parse()
{
}

void Parser::synchronize()
{
}

void Parser::error(const lexer::Token &peek, const char *message)
{

}
}