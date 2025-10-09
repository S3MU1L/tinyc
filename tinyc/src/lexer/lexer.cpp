#include "lexer.hpp"

#include <utility>
#include <cctype>
#include <charconv>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <limits>
#include <algorithm>

namespace tinyc::lexer {
static const std::unordered_map<std::string, TokenType> keywords = {
        {"if", TokenType::IF}, {"else", TokenType::ELSE}, {"while", TokenType::WHILE},
        {"for", TokenType::FOR}, {"return", TokenType::RETURN}, {"struct", TokenType::STRUCT},
        {"int", TokenType::INT}, {"char", TokenType::CHAR}, {"bool", TokenType::BOOL},
        {"unsigned", TokenType::UNSIGNED}, {"true", TokenType::TRUE}, {"false", TokenType::FALSE},
        {"NULL", TokenType::NULLPTR}, {"break", TokenType::BREAK},
        {"continue", TokenType::CONTINUE},
        {"do", TokenType::DO}, {"assert", TokenType::ASSERT}
};

Lexer::Lexer(std::string content) : content(std::move(content))
{
}

void Lexer::scan_tokens()
{
    while (!is_end())
    {
        start = current;
        scan_token();
    }
    add_token(TokenType::END_OF_FILE, {});
}


void Lexer::scan_token()
{
    switch (const char c = advance())
    {
    case '(':
        add_token(TokenType::LPAREN, {});
        break;
    case ')':
        add_token(TokenType::RPAREN, {});
        break;
    case '{':
        add_token(TokenType::LBRACE, {});
        break;
    case '}':
        add_token(TokenType::RBRACE, {});
        break;
    case '[':
        add_token(TokenType::LBRACKET, {});
        break;
    case ']':
        add_token(TokenType::RBRACKET, {});
        break;
    case ',':
        add_token(TokenType::COMMA, {});
        break;
    case '.':
        add_token(TokenType::DOT, {});
        break;
    case '-':
        if (match('>'))
            add_token(TokenType::ARROW, {});
        else if (match('-'))
            add_token(TokenType::MINUS_MINUS, {});
        else if (match('='))
            add_token(TokenType::MINUS_EQUAL, {});
        else
            add_token(TokenType::MINUS, {});
        break;
    case '+':
        if (match('+'))
            add_token(TokenType::PLUS_PLUS, {});
        else if (match('='))
            add_token(TokenType::PLUS_EQUAL, {});
        else
            add_token(TokenType::PLUS, {});
        break;
    case ';':
        add_token(TokenType::SEMICOLON, {});
        break;
    case '*':
        if (match('='))
            add_token(TokenType::STAR_EQUAL, {});
        else
            add_token(TokenType::STAR, {});
        break;
    case '%':
        if (match('='))
            add_token(TokenType::PERCENT_EQUAL, {});
        else
            add_token(TokenType::PERCENT, {});
        break;
    case '!':
        if (match('='))
            add_token(TokenType::BANG_EQUAL, {});
        else
            add_token(TokenType::BANG, {});
        break;
    case '~':
        add_token(TokenType::TILDE, {});
        break;
    case '?':
        add_token(TokenType::QUESTION, {});
        break;
    case ':':
        add_token(TokenType::COLON, {});
        break;
    case '^':
        if (match('='))
            add_token(TokenType::CARET_EQUAL, {});
        else
            add_token(TokenType::CARET, {});
        break;
    case '&':
        if (match('&'))
            add_token(TokenType::AMPERSAND_AMPERSAND, {});
        else if (match('='))
            add_token(TokenType::AMPERSAND_EQUAL, {});
        else
            add_token(TokenType::AMPERSAND, {});
        break;
    case '|':
        if (match('|'))
            add_token(TokenType::PIPE_PIPE, {});
        else if (match('='))
            add_token(TokenType::PIPE_EQUAL, {});
        else
            add_token(TokenType::PIPE, {});
        break;
    case '=':
        if (match('='))
            add_token(TokenType::EQUAL_EQUAL, {});
        else
            add_token(TokenType::EQUAL, {});
        break;
    case '<':
        if (match('<'))
        {
            if (match('='))
                add_token(TokenType::LEFT_SHIFT_EQUAL, {});
            else
                add_token(TokenType::LEFT_SHIFT, {});
        }
        else if (match('='))
            add_token(TokenType::LESS_EQUAL, {});
        else
            add_token(TokenType::LESS, {});
        break;
    case '>':
        if (match('>'))
        {
            if (match('='))
                add_token(TokenType::RIGHT_SHIFT_EQUAL, {});
            else
                add_token(TokenType::RIGHT_SHIFT, {});
        }
        else if (match('='))
            add_token(TokenType::GREATER_EQUAL, {});
        else
            add_token(TokenType::GREATER, {});
        break;
    case '/': {
        if (match('/'))
        {
            while (peek() != '\n' && !is_end())
                advance();
            break;
        }
        if (match('*'))
        {
            while (!(peek() == '*' && current + 1 < content.size() && content[current + 1] == '/')
                   && !is_end())
            {
                if (peek() == '\n')
                    line++;
                advance();
            }
            if (!is_end())
            {
                advance();
                advance();
            }
            break;
        }

        if (match('='))
            add_token(TokenType::SLASH_EQUAL, {});
        else
            add_token(TokenType::SLASH, {});
        break;
    }
    case '"':
        string_literal();
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        line++;
        break;
    default:
        if (is_digit(c))
        {
            number_literal();
            break;
        }
        if (is_alpha(c))
        {
            while (is_alphanum(peek()))
                advance();
            const std::string text = content.substr(start, current - start);
            if (const auto it = keywords.find(text); it != keywords.end())
            {
                if (const TokenType tt = it->second; tt == TokenType::TRUE)
                    add_token(tt, Literal{true});
                else if (tt == TokenType::FALSE)
                    add_token(tt, Literal{false});
                else if (tt == TokenType::NULLPTR)
                    add_token(tt, {});
                else
                    add_token(tt, {});
            }
            else
                add_token(TokenType::IDENTIFIER, {});
        }
        else
            throw std::runtime_error(std::string("Unexpected character: ") + c);
    }
}

char Lexer::peek() const
{
    if (is_end())
        return '\0';
    return content[current];
}

bool Lexer::is_end() const
{
    return current >= content.size();
}

char Lexer::advance()
{
    const char c = peek();
    current++;
    return c;
}

bool Lexer::match(const char expected)
{
    if (is_end())
        return false;
    if (content[current] != expected)
        return false;
    current++;
    return true;
}

void Lexer::add_token(const TokenType type, const Literal &literal)
{
    const std::string lexeme = content.substr(start, current - start);
    tokens.push_back(Token{type, literal, lexeme, line});
}

bool Lexer::is_alpha(const char c)
{
    return c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Lexer::is_alphanum(const char c)
{
    return isalpha(c) || isdigit(c);
}

bool Lexer::is_digit(const char c)
{
    return c >= '0' && c <= '9';
}

bool Lexer::is_hex_digit(char c)
{
    return (c >= '0' && c <= '9') ||
           (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

void Lexer::string_literal()
{
    // We assume the opening '"' has already been consumed; start points at opening position.
    std::string value;
    while (!is_end())
    {
        char c = advance();
        if (c == '\\')
        {
            if (is_end())
            {
                error("Unterminated string literal");
                break;
            }
            char esc = advance();
            switch (esc)
            {
            case 'n': value.push_back('\n'); break;
            case 't': value.push_back('\t'); break;
            case 'r': value.push_back('\r'); break;
            case '\\': value.push_back('\\'); break;
            case '\"': value.push_back('"'); break;
            default:
                // unknown escape, keep literal char
                value.push_back(esc);
                break;
            }
        }
        else if (c == '"')
        {
            // end of string
            add_token(TokenType::STRING_LITERAL, Literal{value});
            return;
        }
        else
        {
            if (c == '\n')
                line++;
            value.push_back(c);
        }
    }
    // If we reach here, unterminated
    error("Unterminated string literal");
}

void Lexer::number_literal()
{
    int base = 10;
    if (content[start] == '0' && current < content.size())
    {
        if (peek() == 'x' || peek() == 'X')
        {
            base = 16;
            advance();
        }
        else if (peek() == 'b' || peek() == 'B')
        {
            base = 2;
            advance();
        }
        else if (isdigit(peek()))
        {
            base = 8;
        }
    }
    while (true)
    {
        const char p  = peek();
        bool       ok = false;
        if (base == 16)
            ok = is_hex_digit(p);
        else if (base == 10)
            ok = is_digit(p);
        else if (base == 8)
            ok = p >= '0' && p <= '7';
        else
            ok = p == '0' || p == '1';
        if (ok)
            advance();
        else
            break;
    }

    bool is_unsigned = false;
    if (peek() == 'u' || peek() == 'U')
    {
        is_unsigned = true;
        advance();
    }

    size_t prefix_len = 0;
    if ((base == 16 || base == 2) && start + 1 < content.size() && content[start] == '0' &&
        ((content[start + 1] == 'x' || content[start + 1] == 'X') ||
         (content[start + 1] == 'b' || content[start + 1] == 'B')))
        prefix_len = 2;
    else if (base == 8 && content[start] == '0')
        prefix_len = 1;

    const size_t           digits_start = start + prefix_len;
    const size_t           digits_end   = current - (is_unsigned ? 1 : 0);
    const char *           digits_ptr   = content.data() + digits_start;
    const std::size_t      digits_len   = digits_end - digits_start;
    const std::string_view digits_sv(digits_ptr, digits_len);

    if (is_unsigned)
    {
        unsigned long long value     = 0;
        const auto         [ptr, ec] = std::from_chars(digits_sv.data(),
                                               digits_sv.data() + digits_sv.size(),
                                               value,
                                               base);
        if (ec == std::errc::result_out_of_range)
        {
            error(std::string("Unsigned integer literal out of range: ") + std::string(digits_sv));
            value = std::numeric_limits<unsigned long long>::max();
        }
        else if (ptr != digits_sv.data() + digits_sv.size())
        {
            error(std::string("Invalid digits in unsigned integer literal: ") + std::string(
                          digits_sv));
        }
        add_token(TokenType::UNSIGNED_LITERAL, Literal{value});
    }
    else
    {
        long long value = 0;
        // parse into unsigned first if base > 10 to avoid sign issues, then check range
        if (base == 10)
        {
            const auto [ptr, ec] = std::from_chars(digits_sv.data(),
                                                   digits_sv.data() + digits_sv.size(),
                                                   value,
                                                   base);
            if (ec == std::errc::result_out_of_range)
            {
                error(std::string("Integer literal out of range: ") + std::string(digits_sv));
                value = std::numeric_limits<long long>::max();
            }
            else if (ptr != digits_sv.data() + digits_sv.size())
            {
                error(std::string("Invalid digits in integer literal: ") + std::string(digits_sv));
            }
            add_token(TokenType::INT_LITERAL, Literal{value});
            return;
        }
        // hex, oct, bin -> parse as unsigned and then clamp to signed max
        unsigned long long uvalue = 0;
        auto [ptr, ec] = std::from_chars(digits_sv.data(), digits_sv.data() + digits_sv.size(),
                                         uvalue, base);
        if (ec == std::errc::result_out_of_range)
        {
            error(std::string("Integer literal out of range: ") + std::string(digits_sv));
            value = std::numeric_limits<long long>::max();
        }
        else if (ptr != digits_sv.data() + digits_sv.size())
            error(std::string("Invalid digits in integer literal: ") + std::string(digits_sv));
        else
        {
            if (uvalue > static_cast<unsigned long long>(std::numeric_limits<long long>::max()))
            {
                error(std::string("Integer literal exceeds signed range, clamping: ") +
                      std::string(digits_sv));
                value = std::numeric_limits<long long>::max();
            }
            else
                value = static_cast<long long>(uvalue);
        }
        add_token(TokenType::INT_LITERAL, Literal{value});
    }
}

void Lexer::warn(const std::string &msg)
{
    diagnostics.push_back({Diagnostic::Level::Warning, msg, line});
}

void Lexer::error(const std::string &msg)
{
    diagnostics.push_back({Diagnostic::Level::Error, msg, line});
}

bool Lexer::has_errors() const
{
    return std::ranges::any_of(diagnostics, [](const Diagnostic &d) {
        return d.level == Diagnostic::Level::Error;
    });
}

bool Lexer::has_warnings() const
{
    return std::ranges::any_of(diagnostics, [](const Diagnostic &d) {
        return d.level == Diagnostic::Level::Warning;
    });
}
}