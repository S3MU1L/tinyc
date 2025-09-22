#pragma once

#include "../parser/stmt.hpp"

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>


namespace tinyc::codegen {
struct CodeGen
{
    llvm::LLVMContext             context;
    llvm::IRBuilder<>             builder;
    std::unique_ptr<llvm::Module> module;

    explicit CodeGen(const std::string &module_name)
        : builder(context), module(std::make_unique<llvm::Module>(module_name, context))
    {
    }

    void generate(const std::vector<parser::StmtPtr> &statements);
    void genStmt(const std::unique_ptr<parser::Stmt> &stmt);
    void genExpr(const std::unique_ptr<parser::Expr> &expr);
};
}