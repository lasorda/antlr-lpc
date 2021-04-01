#include <iostream>
#include <fstream>
#include "LPCBaseListener.h"
#include "LPCLexer.h"
#include "LPCParser.h"
#include "LPCListener.h"
#include "antlr4-runtime.h"

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
        cout << ctx->getText() << endl;
    }
    void exitFunction_defination(LPCParser::Function_definationContext *ctx)
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
