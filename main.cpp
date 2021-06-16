#include <iostream>
#include <fstream>
#include "LPCBaseListener.h"
#include "LPCLexer.h"
#include "LPCParser.h"
#include "LPCListener.h"
#include "antlr4-runtime.h"
#include "mcpp_lib.h"
#include <cstdlib>

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

string from_mcpp;
char buff[102400];

int func_fputc(int c, OUTDEST od)
{
    if(od != OUT) return 0;
    from_mcpp.push_back(c);
    return 0;
}

int func_fputs(const char *s, OUTDEST od)
{
    if(od != OUT) return 0;
    from_mcpp.append(s);
    return 0;
}

int func_fprintf(OUTDEST od, const char *format, ...)
{
    if(od != OUT) return 0;
    va_list args;
    va_start(args, format);
    sprintf(buff, format, args);
    va_end(args);
    from_mcpp.append(buff);
    return 0;
}

int main(int argc, char const *argv[])
{
    int mcpp_argc = 6;
    char const *mcpp_argv[6];

    mcpp_argv[0] = string("mcpp").c_str();
    mcpp_argv[1] = string("-I").c_str();
    mcpp_argv[2] = string("inc").c_str();
    mcpp_argv[3] = string("-d").c_str();
    mcpp_argv[4] = string(".").c_str();
    mcpp_argv[5] = string("cmd/wizard_common.c").c_str();

    mcpp_set_out_func(func_fputc, func_fputs, func_fprintf);
    //  = {argv[0], "-I", "inc", "-d", ".", "cmd/wizard_common.c"};
    mcpp_lib_main(mcpp_argc, mcpp_argv);

    cout << from_mcpp;
    return 0;
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
