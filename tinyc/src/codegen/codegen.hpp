#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <map>
#include <string>
#include <vector>

namespace tinyc::codegen {
extern llvm::LLVMContext context;

extern llvm::IRBuilder<> builder;

extern std::unique_ptr<llvm::Module> modules;

extern std::map<std::string, llvm::Value *> named_values;

extern std::map<std::string, llvm::StructType *> struct_types;

extern std::map<std::string, std::vector<std::string>> struct_fields;

extern std::map<std::string, std::string> named_struct_vars;

llvm::FunctionCallee getPrintf();

llvm::Value *createGlobalString(const std::string &str, const std::string &name = "fmt");

} // namespace tinyc::codegen