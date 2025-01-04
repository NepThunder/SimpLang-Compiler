#include <string>
#include <vector>
#include "lexer.h"

Lexer::Lexer(const std::string &source) : sourceCode(source), currentPos(0) {}

char Lexer::currentChar()
{
    return isEndOfFile() ? '\0' : sourceCode[currentPos];
}

bool Lexer::isEndOfFile()
{
    return currentPos >= sourceCode.size();
}

void Lexer::advance()
{
    if (!isEndOfFile())
    {
        currentPos++;
    }
}

bool Lexer::isWhiteSpace(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

bool Lexer::isDigit(char c)
{
    return std::isdigit(c);
}

bool Lexer::isLetter(char c)
{
    return std::isalpha(c) || c == '_';
}

Token Lexer::nextToken()
{
    while (isWhiteSpace(currentChar()))
    {
        advance();
    }

    if (isEndOfFile())
    {
        return Token(TokenType::END, "");
    }

    char current = currentChar();

    if (isDigit(current))
    {
        std::string number;
        while (isDigit(current))
        {
            number += current;
            advance();
            current = currentChar();
        }
        return Token(TokenType::NUMBER, number);
    }

    if (isLetter(current))
    {
        std::string identifier;
        while (isLetter(current) || isDigit(current))
        {
            identifier += current;
            advance();
            current = currentChar();
        }

        if (identifier == "int")
            return Token(TokenType::INT, identifier);
        if (identifier == "if")
            return Token(TokenType::IF, identifier);
        return Token(TokenType::IDENTIFIER, identifier);
    }

    switch (current)
    {
    case '=':
        advance();
        if (currentChar() == '=')
        {
            advance();
            return Token(TokenType::EQ, "==");
        }
        return Token(TokenType::EQUAL, "=");
    case ';':
        advance();
        return Token(TokenType::SEMICOLON, ";");
    case '+':
        advance();
        return Token(TokenType::PLUS, "+");
    case '-':
        advance();
        return Token(TokenType::MINUS, "-");
    case '(':
        advance();
        return Token(TokenType::LPAREN, "(");
    case ')':
        advance();
        return Token(TokenType::RPAREN, ")");
    case '{':
        advance();
        return Token(TokenType::LBRACE, "{");
    case '}':
        advance();
        return Token(TokenType::RBRACE, "}");
        }

    std::string unknown(1, current);
    advance();
    return Token(TokenType::END, unknown);
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (!isEndOfFile())
    {
        tokens.push_back(nextToken());
    }
    tokens.push_back(Token(TokenType::END, ""));
    return tokens;
}
