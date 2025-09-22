#pragma once

#include "../lexer/token.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace tinyc::parser {

struct Expr
{
    virtual ~Expr() = default;
};

using ExprPtr = std::unique_ptr<Expr>;

struct LiteralExpr final : Expr
{
    lexer::Token token;

    explicit LiteralExpr(lexer::Token t) : token(std::move(t))
    {
    }
};

struct VariableExpr final : Expr
{
    lexer::Token name;

    explicit VariableExpr(lexer::Token n) : name(std::move(n))
    {
    }
};

struct UnaryExpr final : Expr
{
    lexer::Token op;
    ExprPtr      right;

    UnaryExpr(lexer::Token op_, ExprPtr r) : op(std::move(op_)), right(std::move(r))
    {
    }
};

struct BinaryExpr final : Expr
{
    ExprPtr      left;
    lexer::Token op;
    ExprPtr      right;

    BinaryExpr(ExprPtr l, lexer::Token op_, ExprPtr r)
        : left(std::move(l)), op(std::move(op_)), right(std::move(r))
    {
    }
};

struct AssignmentExpr final : Expr
{
    lexer::Token name;
    ExprPtr      value;

    AssignmentExpr(lexer::Token n, ExprPtr v) : name(std::move(n)), value(std::move(v))
    {
    }
};

struct CallExpr final : Expr
{
    ExprPtr              callee;
    std::vector<ExprPtr> arguments;

    CallExpr(ExprPtr c, std::vector<ExprPtr> args) : callee(std::move(c)),
                                                     arguments(std::move(args))
    {
    }
};

}