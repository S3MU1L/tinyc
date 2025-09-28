#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <map>

namespace tinyc::codegen {
extern llvm::LLVMContext context;

extern llvm::IRBuilder<> builder;

extern std::unique_ptr<llvm::Module> modules;

extern std::map<std::string, llvm::Value *> named_values;
}