#pragma once

#include "expr.hpp"
#include "../lexer/token.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace tinyc::ast {
struct Stmt
{
    virtual              ~Stmt() = default;
    virtual llvm::Value *codegen() = 0;
};

using StmtPtr = std::unique_ptr<Stmt>;

struct ExprStmt final : Stmt
{
    ExprPtr expr;

    explicit     ExprStmt(ExprPtr e);
    llvm::Value *codegen() override;
};

struct ReturnStmt final : Stmt
{
    ExprPtr expr;

    explicit     ReturnStmt(ExprPtr e);
    llvm::Value *codegen() override;
};

struct IfStmt final : Stmt
{
    ExprPtr condition;
    StmtPtr then_branch;
    StmtPtr else_branch;

    IfStmt(ExprPtr c, StmtPtr t, StmtPtr e);
    llvm::Value *codegen() override;
};

struct WhileStmt final : Stmt
{
    ExprPtr condition;
    StmtPtr body;

    WhileStmt(ExprPtr c, StmtPtr b);
    llvm::Value *codegen() override;
};

struct ForStmt final : Stmt
{
    StmtPtr init; // can be VarDeclStmt or ExprStmt or nullptr
    ExprPtr cond;
    ExprPtr incr;
    StmtPtr body;

    ForStmt(StmtPtr i, ExprPtr c, ExprPtr r, StmtPtr b);
    llvm::Value *codegen() override;
};

struct CompoundStmt final : Stmt
{
    std::vector<StmtPtr> statements;

    explicit     CompoundStmt(std::vector<StmtPtr> s);
    llvm::Value *codegen() override;
};

struct VarDeclStmt final : Stmt
{
    lexer::Token type_token;
    lexer::Token name;
    ExprPtr      initializer;

    VarDeclStmt(lexer::Token t, lexer::Token n, ExprPtr init);
    llvm::Value *codegen() override;
};

struct FunctionDeclStmt final : Stmt
{
    lexer::Token                  type_token;
    lexer::Token                  name;
    std::vector<lexer::Token>     parameters;
    std::unique_ptr<CompoundStmt> body;

    FunctionDeclStmt(lexer::Token t, lexer::Token n, std::vector<lexer::Token> params,
                     std::unique_ptr<CompoundStmt> b);
    llvm::Value *codegen() override;
};

struct StructDeclStmt final : Stmt
{
    lexer::Token             name;
    std::vector<VarDeclStmt> fields;

    StructDeclStmt(lexer::Token n, std::vector<VarDeclStmt> f);
    llvm::Value *codegen() override;
};

struct AssertStmt final : Stmt
{
    ExprPtr condition;

    explicit     AssertStmt(ExprPtr c);
    llvm::Value *codegen() override;
};
}