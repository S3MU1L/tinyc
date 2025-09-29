#include "parser.hpp"

#include <iostream>
#include <utility>

#include "../common/error.hpp"

namespace tinyc::ast {

using TT = lexer::TokenType;

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

std::vector<StmtPtr> Parser::parse()
{
    std::vector<StmtPtr> stmts = {};
    try
    {
        while (!is_end())
            if (StmtPtr t = top_level())
                stmts.push_back(std::move(t));
    } catch (const std::runtime_error &e)
    {
        synchronize();
    }
    return stmts;
}

void Parser::synchronize()
{
    while (!is_end())
    {
        if (previous().type == TT::SEMICOLON)
            return;
        switch (peek().type)
        {
        case TT::IF:
        case TT::FOR:
        case TT::WHILE:
        case TT::RETURN:
        case TT::STRUCT:
        case TT::INT:
        // TODO: we don't probably need to have char/bool
        case TT::CHAR:
        case TT::BOOL:
        case TT::UNSIGNED:
            return;
        default:
            break;
        }
        advance();
    }
}

void Parser::error(const lexer::Token &tok, const char *message)
{
    const std::string where = tok.type == TT::END_OF_FILE
                                  ? " at end"
                                  : (" at '" + tok.lexeme + "'");
    throw common::ParseError(std::string("[line ") + std::to_string(tok.line) + "] Parse error" +
                             where + ": " + message);
}

bool Parser::is_type_specifier() const
{
    const auto t = peek().type;
    return t == TT::INT || t == TT::CHAR || t == TT::BOOL || t == TT::UNSIGNED || t == TT::STRUCT;
}

lexer::Token Parser::parse_type_specifier()
{
    if (!is_type_specifier())
        error(peek(), "expected type specifier");

    if (match(TT::STRUCT))
    {
        consume(TT::IDENTIFIER, "expected struct name after 'struct'");
        return previous();
    }
    return advance();
}

StmtPtr Parser::top_level()
{
    if (check(TT::STRUCT))
        return struct_declaration();

    const int save        = current;
    bool      seen_lparen = false;
    while (!is_end())
    {
        if (check(TT::LPAREN))
        {
            seen_lparen = true;
            break;
        }
        if (check(TT::SEMICOLON) || check(TT::LBRACE))
            break;
        advance();
    }

    current = save;
    if (seen_lparen)
        return function_definition();

    return declaration();
}

StmtPtr Parser::declaration()
{
    if (is_type_specifier())
    {
        const lexer::Token typeTok = parse_type_specifier();
        return var_declaration(typeTok);
    }
    return statement();
}

StmtPtr Parser::function_definition()
{
    lexer::Token       typeTok = parse_type_specifier();
    const lexer::Token nameTok = advance();
    if (nameTok.type != TT::IDENTIFIER)
        error(nameTok, "expected function name");

    consume(TT::LPAREN, "expected '(' after function name");
    std::vector<lexer::Token> params;
    if (!check(TT::RPAREN))
    {
        while (true)
        {
            if (!is_type_specifier())
                error(peek(), "expected parameter type");
            parse_type_specifier();
            lexer::Token pname = consume(TT::IDENTIFIER, "expected parameter name");
            params.push_back(pname);
            if (!match(TT::COMMA))
                break;
        }
    }
    consume(TT::RPAREN, "expected ')' after parameters");
    auto body = compound_statement();
    return std::make_unique<FunctionDeclStmt>(typeTok, nameTok, std::move(params), std::move(body));
}

StmtPtr Parser::struct_declaration()
{
    consume(TT::STRUCT, "expected 'struct'");
    lexer::Token nameTok = consume(TT::IDENTIFIER, "expected struct name");

    std::vector<VarDeclStmt> fields;
    if (match(TT::LBRACE))
    {
        while (!check(TT::RBRACE) && !is_end())
        {
            if (!is_type_specifier())
                error(peek(), "expected field declaration");
            lexer::Token ftype = parse_type_specifier();
            while (true)
            {
                lexer::Token fname = consume(TT::IDENTIFIER, "expected field name");
                ExprPtr      init{};
                if (match(TT::EQUAL))
                {
                    init = expression();
                }
                fields.emplace_back(ftype, fname, std::move(init));
                if (!match(TT::COMMA))
                    break;
            }
            consume(TT::SEMICOLON, "expected ';' after field declaration");
        }
        consume(TT::RBRACE, "expected '}' after struct definition");
        consume(TT::SEMICOLON, "expected ';' after struct definition");
        return std::make_unique<StructDeclStmt>(nameTok, std::move(fields));
    }
    consume(TT::SEMICOLON, "expected ';' after struct declaration");
    return std::make_unique<StructDeclStmt>(nameTok, std::move(fields));
}

StmtPtr Parser::var_declaration(const lexer::Token &typeTok)
{
    std::vector<StmtPtr> decls;
    while (true)
    {
        lexer::Token nameTok = consume(TT::IDENTIFIER, "expected variable name");
        ExprPtr      init{};
        if (match(TT::EQUAL))
        {
            init = expression();
        }
        decls.push_back(std::make_unique<VarDeclStmt>(typeTok, nameTok, std::move(init)));
        if (!match(TT::COMMA))
            break;
    }
    consume(TT::SEMICOLON, "expected ';' after variable declaration");

    if (decls.size() == 1)
        return std::move(decls.front());
    return std::make_unique<CompoundStmt>(std::move(decls));
}

std::unique_ptr<CompoundStmt> Parser::compound_statement()
{
    consume(TT::LBRACE, "expected '{'");
    std::vector<StmtPtr> body;
    while (!check(TT::RBRACE) && !is_end())
    {
        if (is_type_specifier())
        {
            lexer::Token t    = parse_type_specifier();
            StmtPtr      decl = var_declaration(t);
            body.push_back(std::move(decl));
        }
        else
        {
            StmtPtr s = statement();
            if (s)
                body.push_back(std::move(s));
        }
    }
    consume(TT::RBRACE, "expected '}' after block");
    return std::make_unique<CompoundStmt>(std::move(body));
}

StmtPtr Parser::statement()
{
    if (match(TT::IF))
    {
        consume(TT::LPAREN, "expected '('");
        ExprPtr cond = expression();
        consume(TT::RPAREN, "expected ')'");
        StmtPtr then_branch = statement();
        StmtPtr else_branch;
        if (match(TT::ELSE))
            else_branch = statement();
        else
            else_branch = nullptr;
        return std::make_unique<IfStmt>(std::move(cond), std::move(then_branch),
                                        std::move(else_branch));
    }
    if (match(TT::WHILE))
    {
        consume(TT::LPAREN, "expected '('");
        ExprPtr cond = expression();
        consume(TT::RPAREN, "expected ')'");
        StmtPtr body = statement();
        return std::make_unique<WhileStmt>(std::move(cond), std::move(body));
    }
    if (match(TT::FOR))
    {
        consume(TT::LPAREN, "expected '('");
        ExprPtr init;
        if (!check(TT::SEMICOLON))
            init = expression();
        consume(TT::SEMICOLON, "expected ';' after for-init");
        ExprPtr cond;
        if (!check(TT::SEMICOLON))
            cond = expression();
        consume(TT::SEMICOLON, "expected ';' after for-cond");
        ExprPtr incr;
        if (!check(TT::RPAREN))
            incr = expression();
        consume(TT::RPAREN, "expected ')' after for-clause");
        StmtPtr body = statement();
        return std::make_unique<ForStmt>(std::move(init), std::move(cond), std::move(incr),
                                         std::move(body));
    }
    if (match(TT::RETURN))
    {
        ExprPtr value;
        if (!check(TT::SEMICOLON))
            value = expression();
        consume(TT::SEMICOLON, "expected ';' after return value");
        return std::make_unique<ReturnStmt>(std::move(value));
    }
    if (match(TT::LBRACE))
    {
        current--;
        return compound_statement();
    }
    if (match(TT::ASSERT))
    {
        consume(TT::LPAREN, "expected '(' after assert");
        ExprPtr cond = expression();
        consume(TT::RPAREN, "expected ')' after assert condition");
        consume(TT::SEMICOLON, "expected ';' after assert statement");
        return std::make_unique<AssertStmt>(std::move(cond));
    }

    if (match(TT::SEMICOLON))
        return nullptr;

    ExprPtr expr = expression();
    consume(TT::SEMICOLON, "expected ';' after expression");
    return std::make_unique<ExprStmt>(std::move(expr));
}

std::unique_ptr<Expr> Parser::expression()
{
    return assignment();
}

std::unique_ptr<Expr> Parser::assignment()
{
    auto lhs = logical_or();
    if (match(TT::EQUAL))
    {
        const lexer::Token equals = previous();
        auto               rhs    = assignment();
        if (const auto *var = dynamic_cast<VariableExpr *>(lhs.get()))
        {
            lexer::Token nameTok = var->name;
            return std::make_unique<AssignmentExpr>(nameTok, std::move(rhs));
        }
        error(equals, "invalid assignment target");
    }
    return lhs;
}

std::unique_ptr<Expr> Parser::logical_or()
{
    auto expr = logical_and();
    while (match(TT::PIPE_PIPE))
    {
        lexer::Token op  = previous();
        auto         rhs = logical_and();
        expr             = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::logical_and()
{
    auto expr = equality();
    while (match(TT::AMPERSAND_AMPERSAND))
    {
        lexer::Token op  = previous();
        auto         rhs = equality();
        expr             = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::equality()
{
    auto expr = relational();
    while (match(TT::EQUAL_EQUAL) || match(TT::BANG_EQUAL))
    {
        lexer::Token op  = previous();
        auto         rhs = relational();
        expr             = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::relational()
{
    auto expr = additive();
    while (match(TT::LESS) || match(TT::LESS_EQUAL) || match(TT::GREATER) || match(
                   TT::GREATER_EQUAL))
    {
        lexer::Token op  = previous();
        auto         rhs = additive();
        expr             = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::additive()
{
    auto expr = multiplicative();
    while (match(TT::PLUS) || match(TT::MINUS))
    {
        lexer::Token op  = previous();
        auto         rhs = multiplicative();
        expr             = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::multiplicative()
{
    auto expr = unary();
    while (match(TT::STAR) || match(TT::SLASH) || match(TT::PERCENT))
    {
        lexer::Token op  = previous();
        auto         rhs = unary();
        expr             = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::unary()
{
    if (match(TT::BANG) || match(TT::MINUS) || match(TT::AMPERSAND) || match(TT::STAR))
    {
        lexer::Token op  = previous();
        auto         rhs = unary();
        return std::make_unique<UnaryExpr>(op, std::move(rhs));
    }
    return postfix();
}

std::unique_ptr<Expr> Parser::postfix()
{
    auto expr = primary();
    while (true)
    {
        if (match(TT::LPAREN))
        {
            std::vector<ExprPtr> args;
            if (!check(TT::RPAREN))
            {
                while (true)
                {
                    args.push_back(assignment());
                    if (!match(TT::COMMA))
                        break;
                }
            }
            consume(TT::RPAREN, "expected ')' after arguments");
            expr = std::make_unique<CallExpr>(std::move(expr), std::move(args));
            continue;
        }
        // TODO: array access, member access can be added later
        break;
    }
    return expr;
}

std::unique_ptr<Expr> Parser::primary()
{
    if (match(TT::IDENTIFIER))
    {
        return std::make_unique<VariableExpr>(previous());
    }

    if (match(TT::INT_LITERAL) || match(TT::UNSIGNED_LITERAL) || match(TT::TRUE) || match(TT::FALSE)
        || match(TT::NULLPTR))
    {
        return std::make_unique<LiteralExpr>(previous());
    }

    if (match(TT::LPAREN))
    {
        auto e = expression();
        consume(TT::RPAREN, "expected ')' after expression");
        return e;
    }

    error(peek(), "expected expression");
    return nullptr;
}
}