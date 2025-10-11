#pragma once

#include "../lexer/token.hpp"

#include <memory>
#include <vector>
#include <llvm/IR/Value.h>

namespace tinyc::ast {

struct Expr
{
    virtual              ~Expr() = default;
    virtual llvm::Value *codegen() = 0;
};

using ExprPtr = std::unique_ptr<Expr>;

struct LiteralExpr final : Expr
{
    lexer::Token token;

    explicit     LiteralExpr(lexer::Token t);
    llvm::Value *codegen() override;
};

struct VariableExpr final : Expr
{
    lexer::Token name;

    explicit     VariableExpr(lexer::Token n);
    llvm::Value *codegen() override;
};

struct UnaryExpr final : Expr
{
    lexer::Token op;
    ExprPtr      right;

    UnaryExpr(lexer::Token op_, ExprPtr r);
    llvm::Value *codegen() override;
};

struct BinaryExpr final : Expr
{
    ExprPtr      left;
    lexer::Token op;
    ExprPtr      right;

    BinaryExpr(ExprPtr l, lexer::Token op_, ExprPtr r);
    llvm::Value *codegen() override;
};

struct AssignmentExpr final : Expr
{
    ExprPtr      lhs;
    ExprPtr      value;

    AssignmentExpr(ExprPtr l, ExprPtr v);
    llvm::Value *codegen() override;
};

struct CallExpr final : Expr
{
    ExprPtr              callee;
    std::vector<ExprPtr> arguments;

    CallExpr(ExprPtr c, std::vector<ExprPtr> args);
    llvm::Value *codegen() override;
};

struct MemberExpr final : Expr
{
    ExprPtr      object;
    lexer::Token member;
    bool         arrow;

    MemberExpr(ExprPtr obj, lexer::Token m, bool a);
    llvm::Value *codegen() override;
    llvm::Value *codegen_address();
};
}