#include "tools.h"

int runTool(vector<string> args) {
    int argc = args.size();
    for (int i{ 0 }; i < argc; i++) {
        std::cout << args[i] << std::endl;
    }
    if (argc < 2) {
        printf("choose tool to run");
        return 0;
    }
    if (args[2] == "generateAst")
        generateAst(args);
    else
        printf("no such tool");
    return 0;
}

void generateAst(vector<string> args) {
    int argc = args.size();
    if (argc != 3) {
        printf("Usage: tools <tool> <output directory>");
    }
    printf("generating . . .");
    string outputDir = args[0];
}
