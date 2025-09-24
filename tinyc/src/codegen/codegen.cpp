#include "codegen.hpp"

namespace tinyc::codegen {
// This is an object that owns LLVM core data structures
llvm::LLVMContext context;

// This is a helper object that makes easy to generate LLVM instructions
llvm::IRBuilder<> builder(context);

// This is an LLVM construct that contains functions and global variables
std::unique_ptr<llvm::Module> modules;

// This map keeps track of which values are defined in the current scope
std::map<std::string, llvm::Value *> named_values;
}