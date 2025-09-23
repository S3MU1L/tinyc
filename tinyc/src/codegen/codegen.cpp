#include "codegen.hpp"

namespace tinyc::codegen {
void CodeGen::generate(const std::vector<parser::StmtPtr> &statements)
{
    for (const auto &stmt : statements)
        gen_stmt(stmt);
}

void CodeGen::gen_stmt(const parser::StmtPtr &stmt)
{

    if (const auto s = dynamic_cast<parser::ExprStmt *>(stmt.get()))
    {
        gen_expr(s->expr);
        return;
    }

    if (const auto s = dynamic_cast<parser::CompoundStmt *>(stmt.get()))
    {
        // TODO
    }

    if (const auto s = dynamic_cast<parser::ReturnStmt *>(stmt.get()))
    {
        // TODO
    }
    if (const auto s = dynamic_cast<parser::IfStmt *>(stmt.get()))
    {
        // TODO
    }
    if (const auto s = dynamic_cast<parser::WhileStmt *>(stmt.get()))
    {
        // TODO
    }
    if (const auto s = dynamic_cast<parser::ForStmt *>(stmt.get()))
    {
        // TODO
    }
    if (const auto s = dynamic_cast<parser::VarDeclStmt *>(stmt.get()))
    {
        // TODO
    }
    if (const auto s = dynamic_cast<parser::FunctionDeclStmt *>(stmt.get()))
    {
        // TODO
    }

    if (const auto s = dynamic_cast<parser::StructDeclStmt *>(stmt.get()))
    {
        // TODO
    }
}

void CodeGen::gen_expr(const parser::ExprPtr &expr)
{
    if (const auto e = dynamic_cast<parser::LiteralExpr *>(expr.get()))
    {
        // TODO
    }
    if (const auto e = dynamic_cast<parser::VariableExpr *>(expr.get()))
    {
        // TODO
    }
    if (const auto e = dynamic_cast<parser::UnaryExpr *>(expr.get()))
    {
        // TODO
    }
    if (const auto e = dynamic_cast<parser::BinaryExpr *>(expr.get()))
    {
        // TODO
    }
    if (const auto e = dynamic_cast<parser::AssignmentExpr *>(expr.get()))
    {
        // TODO
    }
    if (const auto e = dynamic_cast<parser::CallExpr *>(expr.get()))
    {
        // TODO
    }
}

llvm::AllocaInst *CodeGen::create_entry_block_alloca(llvm::Function *   func,
                                                     const std::string &var_name, llvm::Type *type)
{
}

llvm::Type *CodeGen::get_llvm_type_from_token(const lexer::Token &type_token)
{
}

}