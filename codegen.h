#ifndef CODEGEN_H
#define CODEGEN_H

#include <string>
#include <fstream>
#include <unordered_map>
#include "parser.h"

class CodeGenerator
{
public:
    CodeGenerator(const std::string &outputFile);
    ~CodeGenerator();
    void generate(ASTNode *ast);

private:
    std::ofstream outFile;
    int labelCounter;
    int nextMemoryLocation;
    std::unordered_map<std::string, int> symbolTable;

    void generateExpression(ASTNode *node);
    void generateAssignment(ASTNode *node);
    void generateIfStatement(ASTNode *node);
    void generateComparision(ASTNode *node);
    int getVariableLocation(const std::string &varName);
};

#endif