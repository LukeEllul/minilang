#include <iostream>
#include <stack>
#include <string>
#include "../Token.h"
#include "../Parser/Parser.h"
#include "../Parser/ASTNodes.h"
#include "../SemanticAnalyzer/SemanticAnalyzer.h"
#include "../Execution/Interpreter.h"
#include "REPL.h"

using namespace std;

void printstack(stack<ASTNode *> *s)
{
    for (stack<ASTNode *> dump = *s; !dump.empty(); dump.pop())
        cout << *(dump.top()->getToken()->value) << endl;
}

REPL::REPL()
{
    this->analyzer = new SemanticAnalyzer();
    this->interpreter = new Interpreter();
    Token *token = new Token();
    token->value = new string("ans");
    this->interpreter->getRef()->firstScope()->insert(pair<string, string *>("ans", NULL));
}

void REPL::ReadVariableDecl(ASTNode *variableDecl)
{
    string *e = interpreter->InterpretVariableDecl(variableDecl);
    stack<ASTNode *> dump = *(variableDecl->getNodes());
    dump.pop();
    dump.pop();
    TokenType type = dump.top()->getToken()->type;

    Token *token = new Token();
    token->type = type;
    token->value = e;

    this->ans = token;
    updateAns();
}

void REPL::ReadAssignment(ASTNode *assignment)
{
    string *e = interpreter->InterpretAssignment(assignment);

    Token *token = new Token();
    token->type = this->ans->type;
    token->value = e;
    this->ans = token;
    updateAns();
}

void REPL::ReadExpression(ASTNode *expression)
{
    string *e = interpreter->InterpretExpression(expression);

    Token *token = new Token();
    token->value = e;

    this->ans = token;
    updateAns();
}

void REPL::ReadStatement(ASTNode *statement)
{
    stack<ASTNode *> dump = *(statement->getNodes());

    if (dump.top()->getToken()->type == SEMI_COLON)
    {
        dump.pop();
    }

    if (dump.top()->getToken()->type == VARIABLE_DECL)
    {
        ReadVariableDecl(dump.top());
    }
    else if (dump.top()->getToken()->type == ASSIGNMENT)
    {
        ReadAssignment(dump.top());
    }
    else
    {
        interpreter->InterpretStatement(statement);
    }
}

void REPL::updateAns()
{
    Token *token = new Token();
    token->value = new string("ans");
    this->interpreter->getRef()->update(token, this->ans->value);
}

void REPL::ParseInput(string *input)
{
    this->parser = new Parser(input);
    ASTNode *program = this->parser->ParseProgram();
    if (program->fail)
    {
        delete this->parser;
        this->parser = new Parser(input);
        ASTNode *expression = this->parser->ParseExpression();
        if (this->analyzer->AnalyzeExpression(expression) == INVALID)
        {
            Token *token = new Token();
            token->value = new string("semantic error/s occured in expression");
            this->ans = token;
            return;
        }
        ReadExpression(expression);
    }
    else
    {
        ASTNode *statement = program->getNodes()->top();
        if (this->analyzer->checkStatemant(statement) == false)
        {
            Token *token = new Token();
            token->value = new string("semantic error/s occured in expression");
            this->ans = token;
            return;
        }
        ReadStatement(statement);
    }
}

void REPL::LoadProgram(const char *loc)
{
    this->parser = new Parser(loc);
    ASTNode *program = this->parser->ParseProgram();
    if (this->analyzer->AnalyzeProgram(program) == false)
    {
        Token *token = new Token();
        token->value = new string("semantic error/s found in loaded program");
        this->ans = token;
        return;
    }
    this->interpreter->InterpretProgram(program);
}

void REPL::ReadLine(string *input)
{
    if (input->substr(0, 5).compare("#load") == 0)
    {
        LoadProgram(input->substr(7, input->length() - 8).c_str());
    }
    else
    {
        ParseInput(input);
    }
}

Token *REPL::getAnswer()
{
    return this->ans;
}