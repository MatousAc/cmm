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
    defineAst(outputDir, "Expr", vector<string>{
        "Binary   : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Unary    : Token operator, Expr right"
    });
}

void defineAst(string outputDir, string base, vector<string> types) {
    //struct stat sb {}; 
    string fp = outputDir + "/" + base + ".cpp";
    const char* filepath = fp.c_str();
    FILE* file; // safely open a file
    errno_t err;
    if (((err = fopen_s(&file, filepath, "w")) != 0) ||
        (file == nullptr)) {
        cout << filepath << " could not be opened: " << file;
        return;
    }
    // stat(filepath, &sb);
    //program.resize(sb.st_size);
    //fread(const_cast<char*>(program.data()), sb.st_size, 1, file);
    string program;
    program = "#pragma once\n";
    program += "class " + base + " {\n";
    program += "}\n";
    fprintf(file, program.c_str());
    fclose(file);
}

//std::wstring ExePath() {
//    TCHAR buffer[MAX_PATH] = { 0 };
//    GetModuleFileName(NULL, buffer, MAX_PATH);
//    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
//    return std::wstring(buffer).substr(0, pos);
//}
