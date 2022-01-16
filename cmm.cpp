// a class for cmm
// thanks to https://www.delftstack.com/howto/cpp/read-file-into-string-cpp/#use-istreambuf_iterator-to-read-file-into-string-in-c%2b%2b

#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include "Token.h"
using namespace std;

void runPrompt();
void runFile(string& filepath);
void run(string& source);

bool hadError = false;
void main(string file = string()) {
    if (file == "")
        runPrompt();
    else
        runFile(file);
}

void runPrompt() {
    string line;
    while (true) {
        cout << "> ";
        getline(cin, line, '\n');
        if (line == "") break;
        run(line);
        hadError = false;
    }
}

void runFile(string& filepath) {
    struct stat sb {};
    string program;
    FILE* file = fopen(filepath.c_str(), "r");
    if (file == nullptr) {
        cout << filepath << "could not be opened";
        return;
    }
    stat(filepath.c_str(), &sb);
    program.resize(sb.st_size);
    fread(const_cast<char*>(program.data()), sb.st_size, 1, file);
    fclose(file);
    run(program);
    if (hadError) return;
}

void run(string& source) {
    Scanner scanner = new Scanner(source);
    vector<Token> = scanner.scanTokens();
}

void error(int line, string msg, string where = "") {
    cout << "error on line " << line
        << " @ " << where << ": "
        << msg << endl;
    hadError = true;
}