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

int main(int argc, char const *argv[])
{
    ifstream file("./example.lpc");
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    ANTLRInputStream input(str);
    LPCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens())
    {
        std::cout << token->toString() << std::endl;
    }

    LPCParser parser(&tokens);
    tree::ParseTree *tree = parser.program();

    std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

    return 0;
}
