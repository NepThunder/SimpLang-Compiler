#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"
#include "lexer.h"
#include "codegen.h"

std::string readFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <input_file> " << std::endl;
        return 1;
    }

    try
    {
        std::string source = readFile(argv[1]);
        Lexer lexer(source);
        std::vector<Token> tokens = lexer.tokenize();
        Parser parser(tokens);
        ASTNode *ast = parser.parse();
        CodeGenerator codegen("output.asm");
        codegen.generate(ast);
        std::cout << "Assembly code generated in output.asm\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}