#include "codegen.h"
#include <iostream>

CodeGenerator::CodeGenerator(const std::string &outputFile) : labelCounter(0), nextMemoryLocation(1)
{
    outFile.open(outputFile);
    if (!outFile.is_open())
    {
        throw std::runtime_error("could not open file");
    }
}
CodeGenerator::~CodeGenerator()
{

    if (outFile.is_open())
    {
        outFile.close();
    }
}

void CodeGenerator::generate(ASTNode *ast)
{
    if (!ast)
        return;
    // std::cout << static_cast<int>(ast->type) << "value: " << ast->value << "\n";
    switch (ast->type)
    {
    case ASTNodeType::BinaryExpression:
        if (ast->value == ";")
        {

            generate(ast->left);
            generate(ast->right);
        }
        if (ast->value == "=")
        {

            if (ast->left->type == ASTNodeType::Variable)
            {
                bool isNewVariable = symbolTable.find(ast->left->value) == symbolTable.end();
                if (isNewVariable)
                {
                    outFile << "; Variable declaration for '" << ast->left->value << "'\n";
                }
                generateAssignment(ast);
            }
        }
        else if (ast->value == "if")
        {

            generateIfStatement(ast);
        }
        else if (ast->value == "==")
        {
            std::cout << "compare";
            generateComparision(ast);
        }
        else if (ast->value == "+")
        {
            generateExpression(ast);
        }
        break;
    default:
        break;
    }
}

void CodeGenerator::generateAssignment(ASTNode *node)
{
    if (node->right->type == ASTNodeType::Literal)
    {
        outFile << "ldi r1 " << node->right->value << "   ;Load inittial value\n";
    }
    else if (node->right->type == ASTNodeType::BinaryExpression)
    {
        generateExpression(node->right);
    }

    int memLoc = getVariableLocation(node->left->value);
    outFile << "mov M r1 " << memLoc << "    ;Store in Variable '" << node->left->value << "'\n";
}

int CodeGenerator::getVariableLocation(const std::string &varName)
{
    if (symbolTable.find(varName) == symbolTable.end())
    {
        symbolTable[varName] = nextMemoryLocation++;
    }
    return symbolTable[varName];
}

void CodeGenerator::generateExpression(ASTNode *node)
{
    if (!node)
        return;

    if (node->value == "+")
    {
        if (node->left->type == ASTNodeType::Variable)
        {
            int leftloc = getVariableLocation(node->left->value);
            outFile << "mov r1 M " << leftloc << "   ;Load Variable\n";
        }
        else
        {
            outFile << "ldi r1 " << node->left->value << "    ;Load constant\n";
        }

        if (node->right->type == ASTNodeType::Variable)
        {
            int rightloc = getVariableLocation(node->right->value);
            outFile << "mov r2 M " << rightloc << "   ;Load Variable\n";
        }
        else
        {
            outFile << "ldi r2 " << node->right->value << "    ;Load constant\n";
        }
        outFile << "add   ;A=A+B or r1=r1+r2    ;didn't mention any register in instruction\n";
    }
}

void CodeGenerator::generateIfStatement(ASTNode *node)
{
    outFile << ";if Statement\n";
    generateComparision(node->left);
    std::string elseLabel = "ESLE" + std::to_string(labelCounter);
    std::string endLabel = "ENDIF" + std::to_string(labelCounter);
    labelCounter++;

    outFile << "jnz %" << elseLabel << "\n";
    generate(node->right);
    outFile << "jmp %" << endLabel << "\n";
    outFile << elseLabel << ":" << "  ;ESLE Label\n";
    outFile << endLabel << ":" << "  ;END Label\n";
}

void CodeGenerator::generateComparision(ASTNode *node)
{
    if (node->left->type == ASTNodeType::Variable)
    {
        int leftloc = getVariableLocation(node->left->value);
        outFile << "mov r1 M " << leftloc << "    ;Load Variable for comparision\n";
    }
    else
    {
        outFile << "ldi r1 " << node->left->value << "    ;Load Constant\n";
    }
    if (node->right->type == ASTNodeType::Variable)
    {
        int rightloc = getVariableLocation(node->right->value);
        outFile << "mov r2 M " << rightloc << "    ;Load Variable for comparision\n";
    }
    else
    {
        outFile << "ldi r2 " << node->right->value << "    ;Load Constant\n";
    }
    outFile << "cmp   ;Compare A and B or r1 and r2\n";
}
