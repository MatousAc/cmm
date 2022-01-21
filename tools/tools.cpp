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
    string outputDir;
    if (argc <= 3) {
        printf("Usage: tools <tool> <output directory>\n");
        outputDir = ".";//ExePath();// args[0];
    }
    else {
        outputDir = args[3];
    }
    cout << "generating in" << outputDir;
    defineAst(outputDir, "Expr", vector<string>{
        "Binary   : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Unary    : Token operator, Expr right"
    });
}

void defineAst(string outputDir, string base, vector<string> types) {

}

std::wstring ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}
