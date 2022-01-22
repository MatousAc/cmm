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
    cout << "generating in: " << outputDir;
    genAst(outputDir, "Expr", vector<string>{
        "Binary   : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Unary    : Token operator, Expr right"
    });
}

void genAst(string outputDir, string base, vector<string> types) {
    string fp = outputDir + "/" + base + ".cpp";
    const char* filepath = fp.c_str();
    FILE* file; // safely open a file
    errno_t err;
    if (((err = fopen_s(&file, filepath, "w")) != 0) ||
        (file == nullptr)) {
        cout << filepath << " could not be opened: " << file;
        return;
    }
    // base
    string program;
    program = "#pragma once\n";
    program += "#include \".. / scanner / Token.h\"";
    program += "struct " + base + " {}\n";

    // derived classes
    auto type = types.begin();
    auto end = types.end();
    while (type != end) {
        int pos = type->find(':');
        string structname = type->substr(0, pos);
        string members = type->substr(pos);

        trim(structname);
        trim(members);
        program += genStruct(base, structname, members);
        type++;
    }

    fprintf(file, program.c_str());
    fclose(file);
}

string genStruct(string base, string structname, string members) {

}

void trim(string str) {
    // from DelftStack:
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}
//std::wstring ExePath() {
//    TCHAR buffer[MAX_PATH] = { 0 };
//    GetModuleFileName(NULL, buffer, MAX_PATH);
//    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
//    return std::wstring(buffer).substr(0, pos);
//}
