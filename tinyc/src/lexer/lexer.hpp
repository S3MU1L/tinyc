#pragma once
#include "token.hpp"
#include "token_type.hpp"

#include <string>
#include <vector>

namespace tinyc::lexer {
struct Lexer
{
    std::string        content;
    std::vector<Token> tokens;
    int                start   = 0;
    int                current = 0;
    int                line    = 1;

    struct Diagnostic
    {
        enum class Level { Warning, Error } level;

        std::string message;
        int         line;
    };

    std::vector<Diagnostic> diagnostics;

    explicit           Lexer(std::string content);
    void               scan_tokens();
    void               number_literal();
    void               scan_token();
    [[nodiscard]] char peek() const;
    [[nodiscard]] bool is_end() const;
    char               advance();
    bool               match(char expected);
    void               add_token(TokenType type, const Literal &literal);

    void               warn(const std::string &msg);
    void               error(const std::string &msg);
    [[nodiscard]] bool has_errors() const;
    [[nodiscard]] bool has_warnings() const;

    [[nodiscard]] const std::vector<Diagnostic> &get_diagnostics() const
    {
        return diagnostics;
    }

    static bool is_alpha(char c);
    static bool is_alphanum(char c);
    static bool is_digit(char c);
    static bool is_hex_digit(char c);
};
}