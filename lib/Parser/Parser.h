#ifndef PARSER_H
#define PARSER_H
#include <stack>
#include "../Token.h"
#include "ASTNodes.h"
#include "../Lexer/Lexer.h"

class Parser 
{
    private:
        ASTNode *rootNode;
        Lexer *lexer;
        Token *currentToken;

        int count;
        bool counting;

        Token *nextToken();
        void backTrack();

    public:
        Parser(const char *fileName);
        Parser(string *inputString);

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

        ASTNode *Fail(Token *token, Token *badToken, ASTNode *node);
};


#endif