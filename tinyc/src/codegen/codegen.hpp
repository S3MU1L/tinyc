#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <map>

namespace tinyc::codegen {
// This is an object that owns LLVM core data structures
extern llvm::LLVMContext context;

// This is a helper object that makes easy to generate LLVM instructions
extern llvm::IRBuilder<> builder;

// This is an LLVM construct that contains functions and global variables
extern std::unique_ptr<llvm::Module> modules;

// This map keeps track of which values are defined in the current scope
extern std::map<std::string, llvm::Value *> named_values;
}