#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>

enum class TokenType
{
    INT,        // int keyword
    IF,         // if keyword
    NUMBER,     // value number
    IDENTIFIER, // variable names
    EQUAL,      //=
    EQ,         //==
    PLUS,       //+
    MINUS,      //-
    LPAREN,     //(
    RPAREN,     //)
    LBRACE,     //{
    RBRACE,     //}
    SEMICOLON,  //;
    UNKNOWN, //unknown
    END         //'\0' end of file
};

struct Token
{
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &v) : type(t), value(v) {}
};

class Lexer
{

public:
    Lexer(const std::string &source);
    std::vector<Token> tokenize();

private:
    std::string sourceCode;
    size_t currentPos;

    char currentChar();
    bool isEndOfFile();
    void advance();
    bool isWhiteSpace(char c);
    bool isDigit(char c);
    bool isLetter(char c);
    Token nextToken();
};

#endif