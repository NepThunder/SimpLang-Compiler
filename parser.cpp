#include <iostream>
#include <string>
#include <vector>
#include "parser.h"

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), currentPos(0) {}

Token Parser::currentToken()
{
    if (currentPos < tokens.size())
    {
        return tokens[currentPos];
    }

    return Token(TokenType::END, "");
}

void Parser::advance()
{
    currentPos++;
}

ASTNode *Parser::parse()
{
    try
    {
        return parseStatements();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return nullptr;
    }
}

ASTNode *Parser::parseStatements()
{
    ASTNode *firstStatement = parseStatement();
    if (!firstStatement)
        return nullptr;

    if (currentPos < tokens.size() && currentToken().type != TokenType::END)
    {
        ASTNode *sequence = new ASTNode(ASTNodeType::BinaryExpression, ";");
        sequence->left = firstStatement;
        sequence->right = parseStatements();
        return sequence;
    }
    return firstStatement;
}

ASTNode *Parser::parseStatement()
{
    Token token = currentToken();

    // Handles only the declaration of variable along with initialization

    if (token.type == TokenType::INT)
    {
        advance();
        if (currentToken().type != TokenType::IDENTIFIER)
        {
            throw std::runtime_error("Expected identifier after 'int'");
        }
        std::string varName = currentToken().value;
        advance();

        if (currentToken().type == TokenType::EQUAL)
        {
            advance();

            ASTNode *node = new ASTNode(ASTNodeType::BinaryExpression, "=");
            node->left = new ASTNode(ASTNodeType::Variable, varName);
            node->right = parseExpression();

            if (currentToken().type != TokenType::SEMICOLON)
            {
                throw std::runtime_error("Expected ';' after declaration");
            }
            advance();

            return node;
        }
        else
        {
            if (currentToken().type != TokenType::SEMICOLON)
            {
                throw std::runtime_error("Expected ';' after declaration");
            }
            advance();

            return new ASTNode(ASTNodeType::Variable,varName);
        }
    }

    if (token.type == TokenType::IF)
    {
        return parseIfstatement();
    }

    // Handle the assignment statements; a=10;

    if (token.type == TokenType::IDENTIFIER)
    {
        std::string varName = token.value;
        advance();

        if (currentToken().type != TokenType::EQUAL)
        {
            throw std::runtime_error("Expected '=' after identifier");
        }
        advance();

        ASTNode *value = parseExpression();

        if (currentToken().type != TokenType::SEMICOLON)
        {
            throw std::runtime_error("Expected ';' after expression");
        }

        advance();

        ASTNode *node = new ASTNode(ASTNodeType::BinaryExpression, "=");
        node->left = new ASTNode(ASTNodeType::Variable, varName);
        node->right = value;
        return node;
    }
    throw std::runtime_error("Unexpected token");
}

ASTNode *Parser::parseIfstatement()
{
    advance();

    if (currentToken().type != TokenType::LPAREN)
    {
        throw std::runtime_error("Expected '(' after 'if'");
    }
    advance();

    ASTNode *condition = parseExpression();

    if (currentToken().type != TokenType::RPAREN)
    {
        throw std::runtime_error("Expected ')' after condition");
    }
    advance();
    if (currentToken().type != TokenType::LBRACE)
    {
        throw std::runtime_error("Expected '{' after ')'");
    }
    advance();

    ASTNode *thenBranch = parseStatement();

    if (currentToken().type != TokenType::RBRACE)
    {
        throw std::runtime_error("Expected '}' after if block");
    }
    advance();

    ASTNode *ifNode = new ASTNode(ASTNodeType::BinaryExpression, "if");
    ifNode->left = condition;
    ifNode->right = thenBranch;
    return ifNode;
}

ASTNode *Parser::parsePrimary()
{
    Token token = currentToken();
    advance();

    if (token.type == TokenType::NUMBER)
    {
        return new ASTNode(ASTNodeType::Literal, token.value);
    }
    if (token.type == TokenType::IDENTIFIER)
    {
        return new ASTNode(ASTNodeType::Variable, token.value);
    }
    throw std::runtime_error("Unexpected token:" + token.value);
}

ASTNode *Parser::parseTerm()
{
    Token token = currentToken();
    if (token.type == TokenType::LPAREN)
    {
        advance();
        ASTNode *expr = parseExpression();
        if (currentToken().type != TokenType::RPAREN)
        {
            throw std::runtime_error("Expected ')'");
        }
        advance();
        return expr;
    }
    return parsePrimary();
}

ASTNode *Parser::parseExpression()
{
    ASTNode *left = parseTerm();

    while (currentPos < tokens.size())
    {
        Token token = currentToken();

        if (token.type == TokenType::PLUS || token.type == TokenType::EQ)
        {
            advance();
            ASTNode *right = parseTerm();
            ASTNode *newNode = new ASTNode(ASTNodeType::BinaryExpression, token.value);
            newNode->left = left;
            newNode->right = right;
            left = newNode;
        }
        else
        {
            break;
        }
    }
    return left;
}
