#pragma once

#include "expr.hpp"
#include "../lexer/token.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace tinyc::parser {

struct Stmt
{
    virtual ~Stmt() = default;
};

using StmtPtr = std::unique_ptr<Stmt>;

struct ExprStmt final : Stmt
{
    ExprPtr expr;

    explicit ExprStmt(ExprPtr e) : expr(std::move(e))
    {
    }
};

struct ReturnStmt final : Stmt
{
    ExprPtr expr;

    explicit ReturnStmt(ExprPtr e) : expr(std::move(e))
    {
    }
};

struct IfStmt final : Stmt
{
    ExprPtr condition;
    StmtPtr then_branch;
    StmtPtr else_branch;

    IfStmt(ExprPtr c, StmtPtr t, StmtPtr e) : condition(std::move(c)), then_branch(std::move(t)),
                                              else_branch(std::move(e))
    {
    }
};

struct WhileStmt final : Stmt
{
    ExprPtr condition;
    StmtPtr body;

    WhileStmt(ExprPtr c, StmtPtr b) : condition(std::move(c)), body(std::move(b))
    {
    }
};

struct ForStmt final : Stmt
{
    ExprPtr init;
    ExprPtr cond;
    ExprPtr incr;
    StmtPtr body;

    ForStmt(ExprPtr i, ExprPtr c, ExprPtr r, StmtPtr b) : init(std::move(i)), cond(std::move(c)),
                                                          incr(std::move(r)), body(std::move(b))
    {
    }
};

struct CompoundStmt final : Stmt
{
    std::vector<StmtPtr> statements;

    explicit CompoundStmt(std::vector<StmtPtr> s) : statements(std::move(s))
    {
    }
};

struct VarDeclStmt final : Stmt
{
    lexer::Token type_token;
    lexer::Token name;
    ExprPtr      initializer;

    VarDeclStmt(lexer::Token t, const lexer::Token &n, ExprPtr init)
        : type_token(std::move(t)), name(n), initializer(std::move(init))
    {
    }
};

struct FunctionDeclStmt final : Stmt
{
    lexer::Token                  type_token;
    lexer::Token                  name;
    std::vector<lexer::Token>     parameters;
    std::unique_ptr<CompoundStmt> body;

    FunctionDeclStmt(lexer::Token t, const lexer::Token &n, std::vector<lexer::Token> params,
                     std::unique_ptr<CompoundStmt> b)
        : type_token(std::move(t)), name(n), parameters(std::move(params)), body(std::move(b))
    {
    }
};

struct StructDeclStmt final : Stmt
{
    lexer::Token             name;
    std::vector<VarDeclStmt> fields;

    StructDeclStmt(lexer::Token n, std::vector<VarDeclStmt> f) : name(std::move(n)),
                                                                 fields(std::move(f))
    {
    }
};

}