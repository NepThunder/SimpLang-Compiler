#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
#include "parser.h"

void printAST(ASTNode *node, int depth = 0)
{
    if (!node)
        return;
    for (int i = 0; i < depth; i++)
    {
        std::cout << " ";
    }

    std::cout << "Type:" << static_cast<int>(node->type) << ",Value:" << node->value << std::endl;
    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);
}

int main()
{
    std::string source = "int a=10;\na=a+2;\nif(a==10){a=20;}";
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();
    std::cout << "Tokens:\n";
    for (const Token &token : tokens)
    {
        std::cout << "Type:" << static_cast<int>(token.type) << ",Value:" << token.value << std::endl;
    }

    Parser parser(tokens);
    ASTNode *ast = parser.parse();

    // std::cout << "\n AST\n";
    // printAST(ast);

    return 0;
}