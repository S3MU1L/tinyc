#include "stmt.hpp"

namespace tinyc::ast {
ExprStmt::ExprStmt(ExprPtr e) : expr(std::move(e))
{
}

llvm::Value *ExprStmt::codegen()
{
    return {};
}

ReturnStmt::ReturnStmt(ExprPtr e) : expr(std::move(e))
{
}

llvm::Value *ReturnStmt::codegen()
{
    return {};
}

IfStmt::IfStmt(ExprPtr c, StmtPtr t, StmtPtr e) : condition(std::move(c)),
                                                  then_branch(std::move(t)),
                                                  else_branch(std::move(e))
{
}

llvm::Value *IfStmt::codegen()
{
    return {};
}

WhileStmt::WhileStmt(ExprPtr c, StmtPtr b) : condition(std::move(c)), body(std::move(b))
{
}

llvm::Value *WhileStmt::codegen()
{
    return {};
}

ForStmt::ForStmt(ExprPtr i, ExprPtr c, ExprPtr r, StmtPtr b) : init(std::move(i)),
                                                               cond(std::move(c)),
                                                               incr(std::move(r)),
                                                               body(std::move(b))
{
}

llvm::Value *ForStmt::codegen()
{
    return {};
}

CompoundStmt::CompoundStmt(std::vector<StmtPtr> s) : statements(std::move(s))
{
}

llvm::Value *CompoundStmt::codegen()
{
    return {};
}

VarDeclStmt::VarDeclStmt(lexer::Token t, lexer::Token n, ExprPtr init) :
    type_token(std::move(t)),
    name(std::move(n)),
    initializer(std::move(init))
{
}

llvm::Value *VarDeclStmt::codegen()
{
    return {};
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
    return {};
}

StructDeclStmt::StructDeclStmt(lexer::Token n, std::vector<VarDeclStmt> f) :
    name(std::move(n)),
    fields(std::move(f))
{
}

llvm::Value *StructDeclStmt::codegen()
{
    return {};
}
}