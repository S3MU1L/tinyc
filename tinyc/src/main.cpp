#include "codegen/codegen.hpp"
#include "lexer/lexer.hpp"
#include "ast/ast_printer.hpp"
#include "parser/parser.hpp"
#include "ast/stmt.hpp"
#include "resolver/resolver.hpp"
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

        tinyc::ast::Parser                     parser(lexer.tokens);
        const std::vector<tinyc::ast::StmtPtr> statements = parser.parse();
        std::cout << "Parsing completed successfully.\n";
        for (const auto &stmt : statements)
            tinyc::ast::ASTPrinter::print(stmt, std::cout, 0);

        tinyc::resolver::Resolver resolver;
        resolver.resolve(statements);
        std::cout << "Resolving completed successfully.\n";

        std::cout << "Resolver phases finished with : \n";
        std::cout << "  " << resolver.symbol_tables.size() << " symbol tables\n";
        std::cout << "  " << resolver.functions.size() << " functions\n";
        std::cout << "  " << resolver.structs.size() << " structs\n";

        return EXIT_SUCCESS;
    } catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
}