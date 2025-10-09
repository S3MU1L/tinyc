#include "codegen.hpp"

#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>

namespace tinyc::codegen {
llvm::LLVMContext context;

llvm::IRBuilder<> builder(context);

std::unique_ptr<llvm::Module> modules;

std::map<std::string, llvm::Value *> named_values;

llvm::FunctionCallee getPrintf()
{
    if (!modules)
        return llvm::FunctionCallee();
    llvm::Type *        i32Ty    = llvm::Type::getInt32Ty(context);
    llvm::Type *i8Ty = llvm::Type::getInt8Ty(context);
    llvm::PointerType *i8PtrTy = llvm::PointerType::get(i8Ty, 0);
    llvm::FunctionType *printfTy = llvm::FunctionType::get(i32Ty, {i8PtrTy}, true);
    return modules->getOrInsertFunction("printf", printfTy);
}

llvm::Value *createGlobalString(const std::string &str, const std::string &name)
{
    if (!modules)
        return nullptr;
    return builder.CreateGlobalStringPtr(str, name);
}

} // namespace tinyc::codegen