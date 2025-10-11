#pragma once

#include "stmt.hpp"
#include <ostream>
#include <string>

namespace tinyc::ast {

struct ASTPrinter
{
    static void print(const StmtPtr &stmt, std::ostream &out, int indent = 0);
    static void print(const ExprPtr &expr, std::ostream &out, int indent = 0);

private:
    static void print_indent(std::ostream &out, const int indent)
    {
        for (int i = 0; i < indent; ++i)
            out << "  ";
    }
};

inline void ASTPrinter::print(const StmtPtr &stmt, std::ostream &out, const int indent)
{
    if (!stmt)
    {
        print_indent(out, indent);
        out << "NullStmt\n";
        return;
    }
    if (const auto s = dynamic_cast<ExprStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "ExprStmt\n";
        print(s->expr, out, indent + 1);
    }
    else if (auto s = dynamic_cast<ReturnStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "ReturnStmt\n";
        print(s->expr, out, indent + 1);
    }
    else if (auto s = dynamic_cast<IfStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "IfStmt\n";
        print_indent(out, indent + 1);
        out << "Condition:\n";
        print(s->condition, out, indent + 2);
        print_indent(out, indent + 1);
        out << "Then:\n";
        print(s->then_branch, out, indent + 2);
        print_indent(out, indent + 1);
        out << "Else:\n";
        print(s->else_branch, out, indent + 2);
    }
    else if (auto s = dynamic_cast<WhileStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "WhileStmt\n";
        print_indent(out, indent + 1);
        out << "Condition:\n";
        print(s->condition, out, indent + 2);
        print_indent(out, indent + 1);
        out << "Body:\n";
        print(s->body, out, indent + 2);
    }
    else if (auto s = dynamic_cast<ForStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "ForStmt\n";
        print_indent(out, indent + 1);
        out << "Init:\n";
        print(s->init, out, indent + 2);
        print_indent(out, indent + 1);
        out << "Cond:\n";
        print(s->cond, out, indent + 2);
        print_indent(out, indent + 1);
        out << "Incr:\n";
        print(s->incr, out, indent + 2);
        print_indent(out, indent + 1);
        out << "Body:\n";
        print(s->body, out, indent + 2);
    }
    else if (auto s = dynamic_cast<CompoundStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "CompoundStmt\n";
        for (const auto &st : s->statements)
            print(st, out, indent + 1);
    }
    else if (auto s = dynamic_cast<VarDeclStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "VarDeclStmt: " << s->name.lexeme << " (type: " << s->type_token.lexeme << ")\n";
        if (s->initializer)
            print(s->initializer, out, indent + 1);
    }
    else if (auto s = dynamic_cast<FunctionDeclStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "FunctionDeclStmt: " << s->name.lexeme << " (type: " << s->type_token.lexeme <<
                ")\n";
        print_indent(out, indent + 1);
        out << "Parameters: ";
        for (const auto &p : s->parameters)
            out << p.lexeme << " ";
        out << "\n";
        print_indent(out, indent + 1);
        out << "Body:\n";
        for (const auto &stmt : s->body->statements)
            print(stmt, out, indent + 2);
    }
    else if (auto s = dynamic_cast<StructDeclStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "StructDeclStmt: " << s->name.lexeme << "\n";
        for (const auto &f : s->fields)
        {
            print_indent(out, indent + 1);
            out << "Field: " << f.name.lexeme << " (type: " << f.type_token.lexeme << ")\n";
            if (f.initializer)
                print(f.initializer, out, indent + 2);
        }
    }
    else if (auto s = dynamic_cast<AssertStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "AssertStmt\n";
        print_indent(out, indent + 1);
        out << "Condition:\n";
        print(s->condition, out, indent + 2);
    }
    else if (auto s = dynamic_cast<StructDeclStmt *>(stmt.get()))
    {
        print_indent(out, indent);
        out << "StructDeclStmt: " << s->name.lexeme << "\n";
        for (const auto &f : s->fields)
        {
            print_indent(out, indent + 1);
            out << "Field: " << f.name.lexeme << " (type: " << f.type_token.lexeme << ")\n";
            if (f.initializer)
                print(f.initializer, out, indent + 2);
        }
    }
    else
    {
        print_indent(out, indent);
        out << "UnknownStmt\n";
    }
}

inline void ASTPrinter::print(const ExprPtr &expr, std::ostream &out, const int indent)
{
    if (!expr)
    {
        print_indent(out, indent);
        out << "NullExpr\n";
        return;
    }
    if (auto e = dynamic_cast<LiteralExpr *>(expr.get()))
    {
        print_indent(out, indent);
        out << "LiteralExpr: " << e->token.lexeme << "\n";
    }
    else if (auto e = dynamic_cast<VariableExpr *>(expr.get()))
    {
        print_indent(out, indent);
        out << "VariableExpr: " << e->name.lexeme << "\n";
    }
    else if (auto e = dynamic_cast<UnaryExpr *>(expr.get()))
    {
        print_indent(out, indent);
        out << "UnaryExpr: " << e->op.lexeme << "\n";
        print(e->right, out, indent + 1);
    }
    else if (auto e = dynamic_cast<BinaryExpr *>(expr.get()))
    {
        print_indent(out, indent);
        out << "BinaryExpr: " << e->op.lexeme << "\n";
        print_indent(out, indent + 1);
        out << "Left:\n";
        print(e->left, out, indent + 2);
        print_indent(out, indent + 1);
        out << "Right:\n";
        print(e->right, out, indent + 2);
    }
    else if (auto e = dynamic_cast<AssignmentExpr *>(expr.get()))
    {
        print_indent(out, indent);
        print(e->value, out, indent + 1);
    }
    else if (auto e = dynamic_cast<CallExpr *>(expr.get()))
    {
        print_indent(out, indent);
        out << "CallExpr\n";
        print_indent(out, indent + 1);
        out << "Callee:\n";
        print(e->callee, out, indent + 2);
        print_indent(out, indent + 1);
        out << "Arguments:\n";
        for (const auto &arg : e->arguments)
            print(arg, out, indent + 2);
    }
    else
    {
        print_indent(out, indent);
        out << "UnknownExpr\n";
    }
}

} // namespace tinyc::parser