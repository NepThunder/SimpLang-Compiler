#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "lexer.h"

enum class ASTNodeType
{
    BinaryExpression, // for operators: +, -
    Literal,          // for numbers
    Variable,         // for variables
};

struct ASTNode
{
    ASTNodeType type;
    ASTNode *left;
    ASTNode *right;
    std::string value;

    ASTNode(ASTNodeType t, const std::string &v) : type(t), value(v), left(nullptr), right(nullptr) {}
};

class Parser
{

public:
    Parser(const std::vector<Token> &tokens);
    ASTNode *parse();
    ASTNode *parseStatement();
    ASTNode *parseStatements();
    ASTNode *parseExpression();

private:
    std::vector<Token> tokens;
    size_t currentPos;

    Token currentToken();
    void advance();
    ASTNode *parseTerm();
    ASTNode *parsePrimary();
    ASTNode *parseIfstatement();
};

#endif