#include <iostream>
#include "LPCBaseListener.h"
#include "LPCLexer.h"
#include "LPCParser.h"
#include "LPCListener.h"
#include "antlr4-runtime.h"

using namespace antlrcpptest;
using namespace antlr4;

int main(int argc, char const *argv[])
{
    ANTLRInputStream input(u8"void foo(){return 100;}");
    LPCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens())
    {
        std::cout << token->toString() << std::endl;
    }

    LPCParser parser(&tokens);
    tree::ParseTree *tree = parser.program();

    std::cout << tree->toStringTree(&parser) << std::endl
              << std::endl;

    return 0;
    return 0;
}
