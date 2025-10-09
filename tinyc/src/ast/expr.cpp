#include "expr.hpp"

#include "../codegen/codegen.hpp"

#include <utility>
#include <llvm/IR/Function.h>
#include <llvm/IR/DerivedTypes.h>
#include <string>

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
        break;
    }
    case lexer::TokenType::UNSIGNED_LITERAL: {
        if (std::holds_alternative<unsigned long long>(token.literal))
            return llvm::ConstantInt::get(
                    codegen::context,
                    llvm::APInt(32, std::get<unsigned long long>(token.literal), false));
        break;
    }
    case lexer::TokenType::TRUE:
        return llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 1));
    case lexer::TokenType::FALSE:
        return llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0));
    case lexer::TokenType::NULLPTR:
        return llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0));
    case lexer::TokenType::STRING_LITERAL: {
        if (std::holds_alternative<std::string>(token.literal))
        {
            const std::string &str = std::get<std::string>(token.literal);
            return codegen::createGlobalString(str);
        }
        break;
    }
    default:
        break;
    }
    return nullptr;
}

VariableExpr::VariableExpr(lexer::Token n) : name(std::move(n))
{
}

llvm::Value *VariableExpr::codegen()
{
    if (const auto it = codegen::named_values.find(name.lexeme); it != codegen::named_values.end())
    {
        return codegen::builder.CreateLoad(llvm::Type::getInt32Ty(codegen::context),
                                           it->second, name.lexeme.c_str());
    }

    if (codegen::modules)
    {
        if (auto *fn = codegen::modules->getFunction(name.lexeme))
            return fn;
    }

    return nullptr;
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
    case lexer::TokenType::PLUS:
        return operand;
    case lexer::TokenType::BANG: {
        auto *cmp = codegen::builder.CreateICmpEQ(
                operand, llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)),
                "notcmp");
        return codegen::builder.CreateZExt(
                cmp, llvm::Type::getInt32Ty(codegen::context), "nottmp");
    }
    case lexer::TokenType::TILDE:
        return codegen::builder.CreateNot(operand, "bitnottmp");
    case lexer::TokenType::PLUS_PLUS:
    case lexer::TokenType::MINUS_MINUS: {
        if (const auto *var = dynamic_cast<VariableExpr *>(right.get()))
        {
            const auto it = codegen::named_values.find(var->name.lexeme);
            if (it == codegen::named_values.end())
                return nullptr;

            llvm::Value *loaded = codegen::builder.CreateLoad(
                    llvm::Type::getInt32Ty(codegen::context), it->second,
                    var->name.lexeme + ".load");
            llvm::Value *one = llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 1));
            llvm::Value *res = nullptr;
            if (op.type == lexer::TokenType::PLUS_PLUS)
                res = codegen::builder.CreateAdd(loaded, one, "inctmp");
            else
                res = codegen::builder.CreateSub(loaded, one, "dectmp");

            codegen::builder.CreateStore(res, it->second);
            return res;
        }
        return nullptr;
    }
    default:
        break;
    }
    return nullptr;
}

BinaryExpr::BinaryExpr(ExprPtr l, lexer::Token op_, ExprPtr r) : left(std::move(l)),
                                                                 op(std::move(op_)),
                                                                 right(std::move(r))
{
}

llvm::Value *BinaryExpr::codegen()
{
    llvm::Value *lhs = left->codegen();
    llvm::Value *rhs = right->codegen();
    if (!lhs || !rhs)
        return nullptr;

    switch (op.type)
    {
    case lexer::TokenType::PLUS:
        return codegen::builder.CreateAdd(lhs, rhs, "addtmp");
    case lexer::TokenType::MINUS:
        return codegen::builder.CreateSub(lhs, rhs, "subtmp");
    case lexer::TokenType::STAR:
        return codegen::builder.CreateMul(lhs, rhs, "multmp");
    case lexer::TokenType::SLASH:
        return codegen::builder.CreateSDiv(lhs, rhs, "divtmp");
    case lexer::TokenType::PERCENT:
        return codegen::builder.CreateSRem(lhs, rhs, "modtmp");
    case lexer::TokenType::EQUAL_EQUAL: {
        auto *cmp = codegen::builder.CreateICmpEQ(lhs, rhs, "cmpeq");
        return tinyc::codegen::builder.CreateZExt(
                cmp, llvm::Type::getInt32Ty(codegen::context), "booleq");
    }
    case lexer::TokenType::BANG_EQUAL: {
        auto *cmp = codegen::builder.CreateICmpNE(lhs, rhs, "cmpne");
        return codegen::builder.CreateZExt(
                cmp, llvm::Type::getInt32Ty(codegen::context), "boolne");
    }
    case lexer::TokenType::LESS: {
        auto *cmp = codegen::builder.CreateICmpSLT(lhs, rhs, "cmplt");
        return codegen::builder.CreateZExt(
                cmp, llvm::Type::getInt32Ty(codegen::context), "boollt");
    }
    case lexer::TokenType::LESS_EQUAL: {
        auto *cmp = codegen::builder.CreateICmpSLE(lhs, rhs, "cmplte");
        return codegen::builder.CreateZExt(
                cmp, llvm::Type::getInt32Ty(codegen::context), "boolle");
    }
    case lexer::TokenType::GREATER: {
        auto *cmp = codegen::builder.CreateICmpSGT(lhs, rhs, "cmpgt");
        return codegen::builder.CreateZExt(
                cmp, llvm::Type::getInt32Ty(codegen::context), "boolgt");
    }
    case lexer::TokenType::GREATER_EQUAL: {
        auto *cmp = codegen::builder.CreateICmpSGE(lhs, rhs, "cmpgte");
        return codegen::builder.CreateZExt(
                cmp, llvm::Type::getInt32Ty(codegen::context), "boolge");
    }
    default:
        break;
    }
    return nullptr;
}

AssignmentExpr::AssignmentExpr(lexer::Token n, ExprPtr v) : name(std::move(n)), value(std::move(v))
{
}

llvm::Value *AssignmentExpr::codegen()
{
    llvm::Value *val = value->codegen();
    if (!val)
        return nullptr;

    const auto it = codegen::named_values.find(name.lexeme);
    if (it == codegen::named_values.end())
        return nullptr;

    codegen::builder.CreateStore(val, it->second);
    return val;
}

CallExpr::CallExpr(ExprPtr c, std::vector<ExprPtr> args) : callee(std::move(c)),
                                                           arguments(std::move(args))
{
}

llvm::Value *CallExpr::codegen()
{
    if (const auto *ve = dynamic_cast<VariableExpr *>(callee.get()))
    {
        if (ve->name.lexeme == "print" || ve->name.lexeme == "println")
        {
            if (!codegen::modules)
                return nullptr;

            std::vector<llvm::Value *> callArgs;
            std::string                fmt;
            fmt.reserve(arguments.size() * 4);

            for (size_t i = 0; i < arguments.size(); ++i)
            {
                Expr *       argptr = arguments[i].get();
                llvm::Value *av     = argptr->codegen();
                if (!av)
                    return nullptr;

                if (llvm::Type *t = av->getType(); t->isPointerTy())
                {
                    if (llvm::Type *i8Ptr = llvm::Type::getInt8Ty(codegen::context)->getPointerTo();
                        t != i8Ptr)
                        av = codegen::builder.CreateBitCast(av, i8Ptr, "strcast");
                    fmt += "%s";
                    callArgs.push_back(av);
                }
                else if (t->isIntegerTy())
                {
                    unsigned    bw    = t->getIntegerBitWidth();
                    llvm::Type *i32Ty = llvm::Type::getInt32Ty(codegen::context);
                    if (bw < 32)
                        av = codegen::builder.CreateSExt(av, i32Ty, "sexttmp");
                    else if (bw > 32)
                        av = codegen::builder.CreateTrunc(av, i32Ty, "trunctmp");
                    fmt += "%d";
                    callArgs.push_back(av);
                }
                else
                {
                    return nullptr;
                }

                if (i + 1 < arguments.size())
                    fmt += " ";
            }

            // Special-case: println behaves like print but appends a newline automatically.
            if (ve->name.lexeme == "println")
            {
                // If there are no arguments, just print a newline
                if (fmt.empty())
                    fmt = "\n";
                else
                    fmt += "\n";

                llvm::Value *fmtPtr = codegen::createGlobalString(fmt, "fmt");
                if (!fmtPtr)
                    return nullptr;

                callArgs.insert(callArgs.begin(), fmtPtr);
                llvm::FunctionCallee printfCallee = codegen::getPrintf();
                if (!printfCallee)
                    return nullptr;

                return codegen::builder.CreateCall(printfCallee, callArgs, "printlncall");
            }

             llvm::Value *fmtPtr = codegen::createGlobalString(fmt, "fmt");
             if (!fmtPtr)
                 return nullptr;

             callArgs.insert(callArgs.begin(), fmtPtr);
             llvm::FunctionCallee printfCallee = codegen::getPrintf();
             if (!printfCallee)
                 return nullptr;

             return codegen::builder.CreateCall(printfCallee, callArgs, "printcall");
        }

        if (!codegen::modules)
            return nullptr;
        llvm::Function *calleeF = codegen::modules->getFunction(ve->name.lexeme);
        if (!calleeF)
            return nullptr;

        std::vector<llvm::Value *> argsv;
        for (const auto &arg : arguments)
        {
            llvm::Value *av = arg->codegen();
            if (!av)
                return nullptr;
            argsv.push_back(av);
        }
        return codegen::builder.CreateCall(calleeF, argsv, "calltmp");
    }

    // otherwise try to codegen callee expression (e.g., function pointer)
    llvm::Value *cval = callee->codegen();
    if (!cval)
        return nullptr;
    std::vector<llvm::Value *> argsv;
    for (auto &arg : arguments)
    {
        llvm::Value *av = arg->codegen();
        if (!av)
            return nullptr;
        argsv.push_back(av);
    }

    if (auto *fn = llvm::dyn_cast<llvm::Function>(cval))
    {
        return tinyc::codegen::builder.CreateCall(fn, argsv, "calltmp");
    }

    return nullptr;
}
} // namespace tinyc::ast
