#include "codegen.hpp"

namespace tinyc::codegen {
llvm::LLVMContext context;

llvm::IRBuilder<> builder(context);

std::unique_ptr<llvm::Module> modules;

std::map<std::string, llvm::Value *> named_values;
} // namespace tinyc::codegen