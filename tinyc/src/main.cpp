#include "lexer/lexer.hpp"
#include "util/args_parser.hpp"
#include "util/file_reader.hpp"
#include "util/option.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Hello from tinyc!\n";
    try
    {
        tinyc::util::Option opt = tinyc::util::ArgsParser::parse(argc, argv);
        tinyc::util::FileUtil::check_file(opt.input_file);
        const std::string content = tinyc::util::FileUtil::read_file(opt.input_file);
        std::cout << content << "\n";

        tinyc::lexer::Lexer lexer(content);
        lexer.scan_tokens();

        const auto &diags = lexer.get_diagnostics();
        for (const auto &d : diags)
        {
            const char *lvl = (d.level == tinyc::lexer::Lexer::Diagnostic::Level::Error)
                                  ? "error"
                                  : "warning";
            std::cerr << lvl << ": " << opt.input_file << ":" << d.line << ": " << d.message <<
                    "\n";
        }

        if (lexer.has_errors())
            return EXIT_FAILURE;

        for (const auto &token : lexer.tokens)
        {

            std::cout << "Token: " << token.lexeme << " ";

            if (std::holds_alternative<long long>(token.literal))
                std::cout << "Literal: " << std::get<long long>(token.literal);
            else if (std::holds_alternative<unsigned long long>(token.literal))
                std::cout << "Literal: " << std::get<unsigned long long>(token.literal);
            else if (std::holds_alternative<bool>(token.literal))
                std::cout << "Literal: " << (std::get<bool>(token.literal) ? "true" : "false");
            else
                std::cout << "No Literal";
            std::cout << " (line " << token.line << ")\n";
        }

        return EXIT_SUCCESS;
    } catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
}