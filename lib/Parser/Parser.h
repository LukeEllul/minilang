#ifndef PARSER_H
#define PARSER_H
#include "../Token.h"
#include "ASTNodes.h"
#include "../Lexer/Lexer.h"

class Parser 
{
    private:
        const ASTNode *rootNode;
        const Lexer *lexer;
        Token *currentToken;

    public:
        Parser(const char *fileName);

        ASTNode *ParseStringLiteral();
        ASTNode *ParseLiteral();
        ASTNode *ParseIdentifier();
        ASTNode *ParseRelationalOp();

        ASTNode *ParseActualParams();
        ASTNode *ParseFunctionCall();

        ASTNode *ParseExpression();
        ASTNode *ParseSubExpression();
        ASTNode *ParseUnary();
        ASTNode *ParseFactor();
        ASTNode *ParseTerm();
        ASTNode *ParseSimpleExpression();

        ASTNode *ParseAssignment();
        ASTNode *ParseVariableDecl();

        ASTNode *ParsePrintStatement();
        ASTNode *ParseReturnStatement();
        ASTNode *ParseIfStatement();
        ASTNode *ParseWhileStatement();
        ASTNode *ParseFormalParam();
        ASTNode *ParseFormalParams();

        ASTNode *ParseFunctionDecl();

        ASTNode *ParseStatement();
        ASTNode *ParseBlock();
        ASTNode *ParseProgram();
};


#endif PARSER_H