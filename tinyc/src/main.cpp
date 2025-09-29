#include "codegen/codegen.hpp"
#include "lexer/lexer.hpp"
#include "ast/ast_printer.hpp"
#include "parser/parser.hpp"
#include "ast/stmt.hpp"
#include "common/args_parser.hpp"
#include "common/file_util.hpp"
#include "common/option.hpp"
#include <iostream>
#include <memory>

int main(const int argc, char *argv[])
{
    std::cout << "Hello from tinyc!\n";
    try
    {
        const tinyc::common::Option opt = tinyc::common::ArgsParser::parse(argc, argv);
        tinyc::common::FileUtil::check_file(opt.input_file);
        const std::string content = tinyc::common::FileUtil::read_file(opt.input_file);

        /* LEXING */
        tinyc::lexer::Lexer lexer(content);
        lexer.scan_tokens();

        for (const auto &diags = lexer.get_diagnostics();
             const auto &[level, message, line] : diags)
        {
            const char *lvl = (level == tinyc::lexer::Lexer::Diagnostic::Level::Error)
                                  ? "error"
                                  : "warning";
            std::cerr << lvl << ": " << opt.input_file << ":" << line << ": " << message <<
                    "\n";
        }

        if (lexer.has_errors())
            return EXIT_FAILURE;
        /* FINISHED LEXING */

        /* PARSING */
        tinyc::ast::Parser                     parser(lexer.tokens);
        const std::vector<tinyc::ast::StmtPtr> statements = parser.parse();
        /* FINISHED PARSING */

        std::cout << "codegen\n";
        std::cout << statements.size() << '\n';
        /* CODEGEN */
        tinyc::codegen::modules = std::make_unique<llvm::Module>(
                tinyc::common::FileUtil::get_file_name(opt.input_file), tinyc::codegen::context);

        for (const auto &stmt : statements)
        {
            if (!stmt)
                continue;
            tinyc::ast::ASTPrinter::print(stmt, std::cout, 0);
            if (stmt)
                stmt->codegen();
        }
        if (tinyc::codegen::modules)
            tinyc::common::FileUtil::writeLLVMFiles(*tinyc::codegen::modules, opt.output_file);
        /* FINISHED CODEGEN */

        return EXIT_SUCCESS;
    } catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
}