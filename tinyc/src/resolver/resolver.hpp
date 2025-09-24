#pragma once
#include "../ast/stmt.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

namespace tinyc::resolver {
struct Symbol
{
    enum class Kind { Variable, Function, Struct } kind;

    std::string name;
    size_t      param_count = 0;
    bool        defined     = false;

    std::string type_name;
    bool        is_parameter = false;
    int         local_index  = -1;
};

using SymbolTable = std::unordered_map<std::string, Symbol>;

struct Resolver
{

    std::unordered_map<std::string, std::vector<Symbol>> function_locals{};
    std::vector<SymbolTable>                             symbol_tables{};
    SymbolTable                                          functions{};
    SymbolTable                                          structs{};


    std::string current_function{};

    Resolver() = default;
    void                  resolve(const std::vector<ast::StmtPtr> &statements);
    void                  resolve_stmt(const ast::StmtPtr &stmt);
    void                  resolve_expr(const ast::ExprPtr &expr);
    std::optional<Symbol> find_symbol(const std::string &name) const;
    void                  declare(const std::string &name);
    void                  define(const std::string &name);
    void                  begin_scope();
    void                  end_scope();

    const std::vector<Symbol> &get_function_locals(const std::string &function_name) const;
};
}