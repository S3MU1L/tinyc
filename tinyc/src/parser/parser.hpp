#pragma once

#include "../ast/stmt.hpp"
#include "../lexer/token.hpp"

#include <vector>
#include <memory>

namespace tinyc::ast {

struct Parser
{
    int start   = 0;
    int current = 0;

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
                             const std::string &                                message);
    std::vector<StmtPtr> parse();
    void                 synchronize();
    static void          error(const lexer::Token &peek, const char *message);

    StmtPtr                       top_level();
    StmtPtr                       declaration();
    StmtPtr                       function_definition();
    StmtPtr                       struct_declaration();
    StmtPtr                       var_declaration(const lexer::Token &typeTok);
    std::unique_ptr<CompoundStmt> compound_statement();
    StmtPtr                       statement();

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> assignment();
    std::unique_ptr<Expr> logical_or();
    std::unique_ptr<Expr> logical_and();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> relational();
    std::unique_ptr<Expr> additive();
    std::unique_ptr<Expr> multiplicative();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> postfix();
    std::unique_ptr<Expr> primary();

    [[nodiscard]] bool is_type_specifier() const;
    lexer::Token       parse_type_specifier();
};

}