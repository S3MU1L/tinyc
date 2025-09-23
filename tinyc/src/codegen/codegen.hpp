#pragma once

#include "../parser/stmt.hpp"
#include "../lexer/token.hpp"

#include <map>
#include <memory>
#include <string>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>


namespace tinyc::codegen {
struct CodeGen
{
    llvm::LLVMContext                    context;
    llvm::IRBuilder<>                    builder;
    std::unique_ptr<llvm::Module>        module;
    std::map<std::string, llvm::Value *> named_values;

    llvm::Function *current_function = nullptr;

    explicit CodeGen(const std::string &module_name)
        : builder(context), module(std::make_unique<llvm::Module>(module_name, context))
    {
    }

    void              generate(const std::vector<parser::StmtPtr> &statements);
    void              gen_stmt(const parser::StmtPtr &stmt);
    void              gen_expr(const parser::ExprPtr &expr);
    llvm::AllocaInst *create_entry_block_alloca(llvm::Function *func, const std::string &var_name,
                                                llvm::Type *    type);
    llvm::Type *get_llvm_type_from_token(const lexer::Token &type_token);
};
}