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
    static void          error(const lexer::Token &peek, const char *message);

    StmtPtr                       top_level();
    StmtPtr                       init_declarator_list(const lexer::Token &type);
    StmtPtr                       declaration();
    StmtPtr                       function_definition();
    StmtPtr                       struct_declaration();
    StmtPtr                       var_declaration(const lexer::Token &typeTok);
    StmtPtr                       direct_declarator(StmtPtr base);
    std::vector<StmtPtr>          parameter_list();
    std::unique_ptr<CompoundStmt> compound_statement();
    StmtPtr                       init_declarator();
    StmtPtr                       parameter();
    StmtPtr                       statement();
    StmtPtr                       declarator();

    ExprPtr              assignment_expression();
    ExprPtr              logical_or_expression();
    ExprPtr              logical_and_expression();
    ExprPtr              equality_expression();
    ExprPtr              relational_expression();
    ExprPtr              additive_expression();
    ExprPtr              multiplicative_expression();
    ExprPtr              unary_expression();
    ExprPtr              postfix_expression();
    std::vector<ExprPtr> argument_expression_list();
    std::vector<ExprPtr> initializer_list();
    ExprPtr              initializer();
    ExprPtr              expression();
    ExprPtr              assignment();
    ExprPtr              logical_or();
    ExprPtr              logical_and();
    ExprPtr              equality();
    ExprPtr              relational();
    ExprPtr              additive();
    ExprPtr              multiplicative();
    ExprPtr              unary();
    ExprPtr              postfix();
    ExprPtr              primary();

    [[nodiscard]] bool        is_type_specifier() const;
    lexer::Token              type_specifier();
    std::vector<lexer::Token> identifier_list();
    lexer::Token              parse_type_specifier();
};

}