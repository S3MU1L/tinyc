#include "codegen.hpp"

namespace tinyc::codegen {
void CodeGen::generate(const std::vector<parser::StmtPtr> &statements)
{
    for (const auto &stmt : statements)
        genStmt(stmt);
}

void CodeGen::genStmt(const std::unique_ptr<parser::Stmt> &stmt)
{
    
}

void CodeGen::genExpr(const std::unique_ptr<parser::Expr> &expr)
{
}
}