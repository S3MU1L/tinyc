#include "codegen/codegen.hpp"
#include "lexer/lexer.hpp"
#include "parser/ast_printer.hpp"
#include "parser/parser.hpp"
#include "parser/stmt.hpp"
#include "util/args_parser.hpp"
#include "util/file_reader.hpp"
#include "util/option.hpp"

#include <iostream>

int main(const int argc, char *argv[])
{
    std::cout << "Hello from tinyc!\n";
    try
    {
        const tinyc::util::Option opt = tinyc::util::ArgsParser::parse(argc, argv);
        tinyc::util::FileUtil::check_file(opt.input_file);
        const std::string content = tinyc::util::FileUtil::read_file(opt.input_file);
        std::cout << content << "\n";

        tinyc::lexer::Lexer lexer(content);
        lexer.scan_tokens();

        for (const auto &diags = lexer.get_diagnostics(); const auto &d : diags)
        {
            const char *lvl = (d.level == tinyc::lexer::Lexer::Diagnostic::Level::Error)
                                  ? "error"
                                  : "warning";
            std::cerr << lvl << ": " << opt.input_file << ":" << d.line << ": " << d.message <<
                    "\n";
        }

        if (lexer.has_errors())
            return EXIT_FAILURE;

        tinyc::parser::Parser                     parser(lexer.tokens);
        const std::vector<tinyc::parser::StmtPtr> statements = parser.parse();
        std::cout << "Parsing completed successfully.\n";
        for (const auto &stmt : statements)
            tinyc::parser::ASTPrinter::print(stmt, std::cout, 0);

        tinyc::codegen::CodeGen codegen("tinyc_module");
        codegen.generate(statements);
        codegen.module->print(llvm::outs(), nullptr);
        return EXIT_SUCCESS;
    } catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
}