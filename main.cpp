#include <iostream>
#include <fstream>
#include "LPCBaseListener.h"
#include "LPCLexer.h"
#include "LPCParser.h"
#include "LPCListener.h"
#include "antlr4-runtime.h"
#include "mcpp_lib.h"

using namespace antlrcpptest;
using namespace antlr4;
using namespace std;
using namespace tree;

class FunctionListener : public LPCBaseListener
{
  private:
    LPCParser *parser;

  public:
    FunctionListener(LPCParser &parser)
    {
        this->parser = &parser;
    }
    void enterFunction_defination(LPCParser::Function_definationContext *ctx)
    {
        fprintf(stdout, "%s %d %d\n", ctx->identifier()->getText().c_str(), ctx->identifier()->getStart()->getLine(), ctx->identifier()->getStart()->getCharPositionInLine());
    }
    void exitFunction_defination(LPCParser::Function_definationContext *ctx)
    {
    }

    void enterNew_local_name(LPCParser::New_local_nameContext *ctx)
    {
        fprintf(stdout, "%s %d %d\n", ctx->getText().c_str(), ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine());
    }

    void enterBlock(LPCParser::BlockContext *ctx)
    {
    }
    void exitBlock(LPCParser::BlockContext *ctx)
    {
    }
};

int main(int argc, char const *argv[])
{
    ifstream file("./example.lpc");
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    ANTLRInputStream input(str);
    LPCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    LPCParser parser(&tokens);
    tree::ParseTree *tree = parser.program();

    FunctionListener functionListener(parser);
    ParseTreeWalker::DEFAULT.walk(&functionListener, tree);

    return 0;
}
