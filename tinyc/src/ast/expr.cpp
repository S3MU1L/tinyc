#include "expr.hpp"

#include "../codegen/codegen.hpp"

#include <utility>

namespace tinyc::ast {

LiteralExpr::LiteralExpr(lexer::Token t) : token(std::move(t))
{
}

llvm::Value *LiteralExpr::codegen()
{
    switch (token.type)
    {
    case lexer::TokenType::INT_LITERAL: {
        if (std::holds_alternative<long long>(token.literal))
            return llvm::ConstantInt::get(
                    codegen::context, llvm::APInt(32, std::get<long long>(token.literal), true));
    }
    case lexer::TokenType::UNSIGNED_LITERAL: {
        if (std::holds_alternative<unsigned long long>(token.literal))
            return llvm::ConstantInt::get(
                    codegen::context,
                    llvm::APInt(32, std::get<unsigned long long>(token.literal), false));
    }

    default: ;
    }
    return {};
}

VariableExpr::VariableExpr(lexer::Token n) : name(std::move(n))
{
}

llvm::Value *VariableExpr::codegen()
{
    return {};
}

UnaryExpr::UnaryExpr(lexer::Token op_, ExprPtr r) : op(std::move(op_)), right(std::move(r))
{
}

llvm::Value *UnaryExpr::codegen()
{
    llvm::Value *operand = right->codegen();
    if (!operand)
        return nullptr;
    switch (op.type)
    {
    case lexer::TokenType::MINUS:
        return codegen::builder.CreateNeg(operand, "negtmp");
    case lexer::TokenType::BANG:
        return codegen::builder.CreateNot(operand, "nottmp");
    case lexer::TokenType::PLUS:
        return operand;
    case lexer::TokenType::TILDE:
        return codegen::builder.CreateNot(operand, "nottmp");
    case lexer::TokenType::PLUS_PLUS:
    case lexer::TokenType::MINUS_MINUS:
        // Handle increment and decrement as needed
    default: ;
    }
    return {};
}

BinaryExpr::BinaryExpr(ExprPtr l, lexer::Token op_, ExprPtr r) : left(std::move(l)),
                                                                 op(std::move(op_)),
                                                                 right(std::move(r))
{
}

llvm::Value *BinaryExpr::codegen()
{
    const llvm::Value *lhs = left->codegen();
    const llvm::Value *rhs = right->codegen();
    if (!lhs || !rhs)
        return nullptr;

    switch (op.type)
    {
    case lexer::TokenType::PLUS:
        return codegen::builder.CreateAdd(const_cast<llvm::Value *>(lhs),
                                          const_cast<llvm::Value *>(rhs),
                                          "addtmp");
    case lexer::TokenType::MINUS:
        return codegen::builder.CreateSub(const_cast<llvm::Value *>(lhs),
                                          const_cast<llvm::Value *>(rhs),
                                          "subtmp");
    case lexer::TokenType::STAR:
        return codegen::builder.CreateMul(const_cast<llvm::Value *>(lhs),
                                          const_cast<llvm::Value *>(rhs),
                                          "multmp");
    case lexer::TokenType::SLASH:
        return codegen::builder.CreateSDiv(const_cast<llvm::Value *>(lhs),
                                           const_cast<llvm::Value *>(rhs),
                                           "divtmp");
    case lexer::TokenType::PERCENT:
        return codegen::builder.CreateSRem(const_cast<llvm::Value *>(lhs),
                                           const_cast<llvm::Value *>(rhs),
                                           "modtmp");
    default: ;
    }
    return {};
}

AssignmentExpr::AssignmentExpr(lexer::Token n, ExprPtr v) : name(std::move(n)), value(std::move(v))
{
}

llvm::Value *AssignmentExpr::codegen()
{
    return {};
}

CallExpr::CallExpr(ExprPtr c, std::vector<ExprPtr> args) : callee(std::move(c)),
                                                           arguments(std::move(args))
{
}

llvm::Value *CallExpr::codegen()
{
    return {};
}
}