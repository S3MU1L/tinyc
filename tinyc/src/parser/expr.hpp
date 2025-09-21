#pragma once

#include "../lexer/token.hpp"

#include <memory>
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

    explicit LiteralExpr(const lexer::Token &t) : token(t)
    {
    }
};

struct VariableExpr final : Expr
{
    lexer::Token name;

    explicit VariableExpr(const lexer::Token &n) : name(n)
    {
    }
};

struct UnaryExpr final : Expr
{
    lexer::Token op;
    ExprPtr      right;

    UnaryExpr(const lexer::Token &op_, ExprPtr r) : op(op_), right(std::move(r))
    {
    }
};

struct BinaryExpr final : Expr
{
    ExprPtr      left;
    lexer::Token op;
    ExprPtr      right;

    BinaryExpr(ExprPtr l, const lexer::Token &op_, ExprPtr r)
        : left(std::move(l)), op(op_), right(std::move(r))
    {
    }
};

struct AssignmentExpr final : Expr
{
    lexer::Token name;
    ExprPtr      value;

    AssignmentExpr(const lexer::Token &n, ExprPtr v) : name(n), value(std::move(v))
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