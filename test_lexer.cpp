#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"

int main()
{
    std::string source = "int a; a=10;";

    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();

    for (const Token &token : tokens)
    {
        std::cout << "Token type:" << static_cast<int>(token.type) << ",Value:" << token.value << std::endl;
    }
}