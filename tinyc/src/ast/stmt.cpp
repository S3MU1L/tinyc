#include "stmt.hpp"

#include "../codegen/codegen.hpp"

#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>

namespace tinyc::ast {

static llvm::AllocaInst *create_entry_block_alloca(llvm::Function *func, const std::string &name)
{
    llvm::IRBuilder<> tmp(&func->getEntryBlock(), func->getEntryBlock().begin());
    return tmp.CreateAlloca(llvm::Type::getInt32Ty(codegen::context), nullptr, name);
}

ExprStmt::ExprStmt(ExprPtr e) : expr(std::move(e))
{
}

llvm::Value *ExprStmt::codegen()
{
    if (expr)
        return expr->codegen();
    return nullptr;
}

ReturnStmt::ReturnStmt(ExprPtr e) : expr(std::move(e))
{
}

llvm::Value *ReturnStmt::codegen()
{
    if (const llvm::Function *fn = codegen::builder.GetInsertBlock()->getParent(); !fn)
        return nullptr;

    if (!expr)
    {
        return codegen::builder.CreateRetVoid();
    }

    llvm::Value *val = expr->codegen();
    if (!val)
        return nullptr;
    return codegen::builder.CreateRet(val);
}

IfStmt::IfStmt(ExprPtr c, StmtPtr t, StmtPtr e) : condition(std::move(c)),
                                                  then_branch(std::move(t)),
                                                  else_branch(std::move(e))
{
}

llvm::Value *IfStmt::codegen()
{
    llvm::Value *condv = condition ? condition->codegen() : nullptr;
    if (!condv)
        return nullptr;

    // convert to boolean i1
    llvm::Value *cond = codegen::builder.CreateICmpNE(
            condv, llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)), "ifcond");

    llvm::Function *  fn      = codegen::builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *thenBB  = llvm::BasicBlock::Create(codegen::context, "then", fn);
    llvm::BasicBlock *elseBB  = llvm::BasicBlock::Create(codegen::context, "else", fn);
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(codegen::context, "ifcont", fn);

    tinyc::codegen::builder.CreateCondBr(cond, thenBB, elseBB);

    codegen::builder.SetInsertPoint(thenBB);
    if (then_branch)
        then_branch->codegen();
    if (!codegen::builder.GetInsertBlock()->getTerminator())
        codegen::builder.CreateBr(mergeBB);

    codegen::builder.SetInsertPoint(elseBB);
    if (else_branch)
        else_branch->codegen();
    if (!codegen::builder.GetInsertBlock()->getTerminator())
        codegen::builder.CreateBr(mergeBB);

    codegen::builder.SetInsertPoint(mergeBB);

    return nullptr;
}

WhileStmt::WhileStmt(ExprPtr c, StmtPtr b) : condition(std::move(c)), body(std::move(b))
{
}

llvm::Value *WhileStmt::codegen()
{
    llvm::Function *fn = codegen::builder.GetInsertBlock()->getParent();
    if (!fn)
        return nullptr;

    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(codegen::context, "while.cond", fn);
    llvm::BasicBlock *bodyBB = llvm::BasicBlock::Create(codegen::context, "while.body", fn);
    llvm::BasicBlock *endBB  = llvm::BasicBlock::Create(codegen::context, "while.end", fn);

    codegen::builder.CreateBr(condBB);
    codegen::builder.SetInsertPoint(condBB);

    llvm::Value *condv = condition ? condition->codegen() : nullptr;
    if (!condv)
        return nullptr;
    llvm::Value *cond = codegen::builder.CreateICmpNE(
            condv, llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)),
            "whilecond");
    codegen::builder.CreateCondBr(cond, bodyBB, endBB);

    codegen::builder.SetInsertPoint(bodyBB);
    if (body)
        body->codegen();
    if (!codegen::builder.GetInsertBlock()->getTerminator())
        codegen::builder.CreateBr(condBB);

    codegen::builder.SetInsertPoint(endBB);
    return nullptr;
}

ForStmt::ForStmt(StmtPtr i, ExprPtr c, ExprPtr r, StmtPtr b) : init(std::move(i)),
                                                               cond(std::move(c)),
                                                               incr(std::move(r)),
                                                               body(std::move(b))
{
}

llvm::Value *ForStmt::codegen()
{
    auto saved_named = codegen::named_values;

    if (init)
        init->codegen();

    llvm::Function *fn = codegen::builder.GetInsertBlock()->getParent();
    if (!fn)
        return nullptr;

    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(codegen::context, "for.cond", fn);
    llvm::BasicBlock *bodyBB = llvm::BasicBlock::Create(codegen::context, "for.body", fn);
    llvm::BasicBlock *incBB  = llvm::BasicBlock::Create(codegen::context, "for.inc", fn);
    llvm::BasicBlock *endBB  = llvm::BasicBlock::Create(codegen::context, "for.end", fn);

    codegen::builder.CreateBr(condBB);
    codegen::builder.SetInsertPoint(condBB);

    if (!cond)
        codegen::builder.CreateBr(bodyBB);
    else
    {
        llvm::Value *condv = cond->codegen();
        if (!condv)
            return nullptr;
        llvm::Value *c = codegen::builder.CreateICmpNE(
                condv, llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)),
                "forcond");
        codegen::builder.CreateCondBr(c, bodyBB, endBB);
    }

    codegen::builder.SetInsertPoint(bodyBB);
    if (body)
        body->codegen();
    if (!codegen::builder.GetInsertBlock()->getTerminator())
        codegen::builder.CreateBr(incBB);

    codegen::builder.SetInsertPoint(incBB);
    if (incr)
        incr->codegen();
    codegen::builder.CreateBr(condBB);

    codegen::builder.SetInsertPoint(endBB);

    codegen::named_values = std::move(saved_named);

    return nullptr;
}

CompoundStmt::CompoundStmt(std::vector<StmtPtr> s) : statements(std::move(s))
{
}

llvm::Value *CompoundStmt::codegen()
{
    auto saved = codegen::named_values;
    for (auto &st : statements)
        if (st)
            st->codegen();
    codegen::named_values = std::move(saved);
    return nullptr;
}

VarDeclStmt::VarDeclStmt(lexer::Token t, lexer::Token n, ExprPtr init) :
    type_token(std::move(t)),
    name(std::move(n)),
    initializer(std::move(init))
{
}

llvm::Value *VarDeclStmt::codegen()
{
    llvm::Function *fn = nullptr;
    if (codegen::builder.GetInsertBlock())
        fn = codegen::builder.GetInsertBlock()->getParent();

    if (fn)
    {
        if (auto it = codegen::named_values.find(name.lexeme); it == codegen::named_values.end())
        {
            llvm::AllocaInst *alloca           = create_entry_block_alloca(fn, name.lexeme);
            codegen::named_values[name.lexeme] = alloca;
            if (initializer)
            {
                llvm::Value *v = initializer->codegen();
                codegen::builder.CreateStore(
                        v ? v : llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)),
                        alloca);
            }
            else
            {
                codegen::builder.CreateStore(
                        llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)),
                        alloca);
            }
        }
        else
        {
            if (initializer)
            {
                llvm::Value *v = initializer->codegen();
                codegen::builder.CreateStore(
                        v ? v : llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)),
                        it->second);
            }
        }
        return nullptr;
    }

    if (!codegen::modules)
        return nullptr;

    llvm::Constant *init_const =
            llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0));
    if (initializer)
    {
        if (const auto lit = dynamic_cast<LiteralExpr *>(initializer.get()))
        {
            if (lit->token.type == lexer::TokenType::INT_LITERAL)
            {
                if (std::holds_alternative<long long>(lit->token.literal))
                    init_const = llvm::ConstantInt::get(codegen::context,
                                                        llvm::APInt(
                                                                32, std::get<long long>(
                                                                        lit->token.literal), true));
            }
            else if (lit->token.type == lexer::TokenType::UNSIGNED_LITERAL)
            {
                if (std::holds_alternative<unsigned long long>(lit->token.literal))
                    init_const = llvm::ConstantInt::get(codegen::context,
                                                        llvm::APInt(
                                                                32, std::get<unsigned long long>(
                                                                        lit->token.literal),
                                                                false));
            }
        }
    }

    auto *gv = new llvm::GlobalVariable(*codegen::modules,
                                        llvm::Type::getInt32Ty(codegen::context),
                                        false,
                                        llvm::GlobalValue::ExternalLinkage,
                                        init_const,
                                        name.lexeme);
    return gv;
}

FunctionDeclStmt::FunctionDeclStmt(lexer::Token t, lexer::Token n, std::vector<lexer::Token> params,
                                   std::unique_ptr<CompoundStmt> b) :
    type_token(std::move(t)),
    name(std::move(n)),
    parameters(std::move(params)),
    body(std::move(b))

{
}

llvm::Value *FunctionDeclStmt::codegen()
{
    if (!codegen::modules)
        return nullptr;

    const bool                      is_void = (type_token.lexeme == "void");
    const std::vector<llvm::Type *> param_types(parameters.size(),
                                                llvm::Type::getInt32Ty(codegen::context));
    llvm::Type *ret_type = is_void
                               ? llvm::Type::getVoidTy(codegen::context)
                               : llvm::Type::getInt32Ty(codegen::context);
    llvm::FunctionType *ft = llvm::FunctionType::get(ret_type, param_types, false);

    llvm::Function *function = llvm::Function::Create(ft, llvm::Function::ExternalLinkage,
                                                      name.lexeme, codegen::modules.get());

    size_t idx = 0;
    for (auto &arg : function->args())
    {
        if (idx < parameters.size())
            arg.setName(parameters[idx].lexeme);
        ++idx;
    }

    llvm::BasicBlock *bb = llvm::BasicBlock::Create(codegen::context, "entry", function);
    llvm::IRBuilder<>::InsertPointGuard guard(codegen::builder); // restore later
    codegen::builder.SetInsertPoint(bb);

    auto saved_named = codegen::named_values;
    codegen::named_values.clear();

    size_t p = 0;
    for (auto &arg : function->args())
    {
        llvm::AllocaInst *alloca = create_entry_block_alloca(function, arg.getName().str());
        codegen::builder.CreateStore(&arg, alloca);
        codegen::named_values[arg.getName().str()] = alloca;
        ++p;
    }

    if (body)
        body->codegen();

    // ensure function has a terminating return
    if (!codegen::builder.GetInsertBlock()->getTerminator())
    {
        if (is_void)
            codegen::builder.CreateRetVoid();
        else
            codegen::builder.CreateRet(
                    llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)));
    }

    codegen::named_values = std::move(saved_named);
    return function;
}

StructDeclStmt::StructDeclStmt(lexer::Token n, std::vector<VarDeclStmt> f) :
    name(std::move(n)),
    fields(std::move(f))
{
}

llvm::Value *StructDeclStmt::codegen()
{
    // structs are not supported in codegen yet
    return nullptr;
}

AssertStmt::AssertStmt(ExprPtr c) : condition(std::move(c))
{
}

llvm::Value *AssertStmt::codegen()
{
    llvm::BasicBlock *insertBB = codegen::builder.GetInsertBlock();
    if (!insertBB || !condition || !codegen::modules)
        return nullptr;

    llvm::Function *fn = insertBB->getParent();
    if (!fn)
        return nullptr;

    llvm::Value *condv = condition->codegen();
    if (!condv)
        return nullptr;

    llvm::Value *cond = codegen::builder.CreateICmpNE(
            condv, llvm::ConstantInt::get(codegen::context, llvm::APInt(32, 0)),
            "assertcond");

    llvm::BasicBlock *okBB   = llvm::BasicBlock::Create(codegen::context, "assert.ok", fn);
    llvm::BasicBlock *failBB = llvm::BasicBlock::Create(codegen::context, "assert.fail", fn);

    codegen::builder.CreateCondBr(cond, okBB, failBB);
    codegen::builder.SetInsertPoint(failBB);

    llvm::Value *msg = codegen::builder.CreateGlobalStringPtr("Assertion failed\n", "assert.msg");

    llvm::FunctionType *putsTy = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(codegen::context),
            {llvm::Type::getInt8Ty(codegen::context)},
            false);
    llvm::FunctionCallee putsF = codegen::modules->getOrInsertFunction("puts", putsTy);
    codegen::builder.CreateCall(putsF, {msg});

    llvm::FunctionType *abortTy = llvm::FunctionType::get(llvm::Type::getVoidTy(codegen::context),
                                                          false);
    llvm::FunctionCallee abortF = codegen::modules->getOrInsertFunction("abort", abortTy);
    codegen::builder.CreateCall(abortF, {});

    codegen::builder.CreateUnreachable();
    codegen::builder.SetInsertPoint(okBB);
    return nullptr;
}
}