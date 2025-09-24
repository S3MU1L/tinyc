#include "resolver.hpp"

#include <stdexcept>

namespace tinyc::resolver {

void Resolver::resolve(const std::vector<ast::StmtPtr> &statements)
{
    if (symbol_tables.empty())
        begin_scope();

    for (const auto &stmt : statements)
        resolve_stmt(stmt);

    while (!symbol_tables.empty())
        end_scope();
}

void Resolver::resolve_stmt(const ast::StmtPtr &stmt)
{
    if (!stmt)
        return;

    if (const auto e = dynamic_cast<ast::ExprStmt *>(stmt.get()))
    {
        resolve_expr(e->expr);
        return;
    }

    if (const auto e = dynamic_cast<ast::ForStmt *>(stmt.get()))
    {
        resolve_expr(e->init);
        resolve_expr(e->cond);
        resolve_expr(e->incr);
        resolve_stmt(e->body);
        return;
    }

    if (const auto e = dynamic_cast<ast::IfStmt *>(stmt.get()))
    {
        resolve_expr(e->condition);
        resolve_stmt(e->then_branch);
        resolve_stmt(e->else_branch);
        return;
    }

    if (const auto e = dynamic_cast<ast::ReturnStmt *>(stmt.get()))
    {
        resolve_expr(e->expr);
        return;
    }

    if (const auto e = dynamic_cast<ast::VarDeclStmt *>(stmt.get()))
    {
        declare(e->name.lexeme);
        if (e->initializer)
            resolve_expr(e->initializer);
        define(e->name.lexeme);

        if (!current_function.empty())
        {
            auto &curr      = symbol_tables.back();
            auto &sym       = curr.at(e->name.lexeme);
            sym.local_index = static_cast<int>(function_locals[current_function].size());
            function_locals[current_function].push_back(sym);
        }
        return;
    }

    if (const auto e = dynamic_cast<ast::CompoundStmt *>(stmt.get()))
    {
        begin_scope();
        resolve(e->statements);
        end_scope();
        return;
    }

    if (const auto e = dynamic_cast<ast::FunctionDeclStmt *>(stmt.get()))
    {
        const std::string fname     = e->name.lexeme;
        const size_t      param_cnt = e->parameters.size();

        if (const auto it = functions.find(fname); it != functions.end())
        {
            if (it->second.defined && e->body)
                throw std::runtime_error("Function '" + fname + "' already defined");

            if (it->second.param_count != 0 && it->second.param_count != param_cnt)
                throw std::runtime_error("Conflicting declaration for function '" + fname + "'");

            if (e->body)
                it->second.defined = true;
        }
        else
        {
            Symbol sym;
            sym.kind        = Symbol::Kind::Function;
            sym.name        = fname;
            sym.param_count = param_cnt;
            sym.defined     = (e->body != nullptr);
            functions.emplace(fname, std::move(sym));
        }

        if (e->body)
        {
            // We're entering the function body: set current function and create a new scope
            current_function = fname;
            begin_scope();

            // Add parameters into the current scope AND persist them for codegen
            for (const auto &p : e->parameters)
            {
                Symbol psym;
                psym.kind         = Symbol::Kind::Variable;
                psym.name         = p.lexeme;
                psym.defined      = true;
                psym.is_parameter = true;
                psym.local_index  = static_cast<int>(function_locals[current_function].size());

                // insert into scope and into persisted function locals
                symbol_tables.back().emplace(p.lexeme, psym);
                function_locals[current_function].push_back(psym);
            }

            resolve(e->body->statements);
            end_scope();

            // leaving function body
            current_function.clear();
        }
        return;
    }

    if (const auto e = dynamic_cast<ast::StructDeclStmt *>(stmt.get()))
    {
        const std::string sname = e->name.lexeme;
        if (structs.contains(sname))
            throw std::runtime_error("Struct '" + sname + "' already declared");

        Symbol sym;
        sym.kind    = Symbol::Kind::Struct;
        sym.name    = sname;
        sym.defined = true;
        structs.emplace(sname, std::move(sym));

        // TODO: validate fields here
        return;
    }

    if (const auto e = dynamic_cast<ast::WhileStmt *>(stmt.get()))
    {
        resolve_expr(e->condition);
        resolve_stmt(e->body);
        return;
    }

    throw std::runtime_error("Resolving failed for some reason.");
}

void Resolver::resolve_expr(const ast::ExprPtr &expr)
{
    if (!expr)
        return;
    if (dynamic_cast<ast::LiteralExpr *>(expr.get()))
        return;
    if (const auto e = dynamic_cast<ast::UnaryExpr *>(expr.get()))
        return resolve_expr(e->right);
    if (const auto e = dynamic_cast<ast::BinaryExpr *>(expr.get()))
    {
        resolve_expr(e->left);
        resolve_expr(e->right);
        return;
    }
    if (const auto e = dynamic_cast<ast::VariableExpr *>(expr.get()))
    {
        if (const std::optional<Symbol> symbol = find_symbol(e->name.lexeme); !symbol.has_value())
            throw std::runtime_error("Undefined variable: " + e->name.lexeme);
        return;
    }
    if (const auto e = dynamic_cast<ast::CallExpr *>(expr.get()))
    {
        // resolve callee (it could be a variable that references a function) and args
        resolve_expr(e->callee);
        for (const auto &arg : e->arguments)
            resolve_expr(arg);
        return;
    }
    if (const auto e = dynamic_cast<ast::AssignmentExpr *>(expr.get()))
    {
        resolve_expr(e->value);
        if (const std::optional<Symbol> symbol = find_symbol(e->name.lexeme); !symbol.has_value())
            throw std::runtime_error("Undefined variable: " + e->name.lexeme);
    }
}

std::optional<Symbol> Resolver::find_symbol(const std::string &name) const
{
    for (int i = symbol_tables.size() - 1; i >= 0; --i)
        if (const auto &curr_table = symbol_tables[i]; curr_table.contains(name))
            return curr_table.at(name);

    if (const auto itf = functions.find(name); itf != functions.end())
        return itf->second;
    if (const auto its = structs.find(name); its != structs.end())
        return its->second;

    return std::nullopt;
}

void Resolver::declare(const std::string &name)
{
    if (symbol_tables.empty())
        begin_scope();

    auto &curr = symbol_tables.back();
    if (curr.contains(name))
        throw std::runtime_error("Variable '" + name + "' already declared in this scope");

    Symbol sym;
    sym.kind    = Symbol::Kind::Variable;
    sym.name    = name;
    sym.defined = false;
    curr.emplace(name, std::move(sym));
}

void Resolver::define(const std::string &name)
{
    for (int i = symbol_tables.size() - 1; i >= 0; --i)
    {
        if (auto &curr = symbol_tables[i]; curr.contains(name))
        {
            curr.at(name).defined = true;
            return;
        }
    }

    if (symbol_tables.empty())
        begin_scope();
    symbol_tables.back().emplace(name, Symbol{Symbol::Kind::Variable, name, 0, true});
}

void Resolver::begin_scope()
{
    symbol_tables.emplace_back();
}

void Resolver::end_scope()
{
    if (symbol_tables.empty())
        return;
    symbol_tables.pop_back();
}

const std::vector<Symbol> &Resolver::get_function_locals(const std::string &function_name) const
{
    static constexpr std::vector<Symbol> empty{};
    if (const auto it = function_locals.find(function_name); it != function_locals.end())
        return it->second;
    return empty;
}

} // namespace tinyc::resolver