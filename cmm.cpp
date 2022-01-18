#include "cmm.h"
bool hadError = false;
int main() {
    string file;
    cin >> file;
    if (file == "try")
        runPrompt();
    else
        runFile(file);
    return 0;
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
    FILE* file; // safely open a file
    errno_t err;
    if (( (err = fopen_s(&file, filepath.c_str(), "r")) != 0) ||
        (file == nullptr) ) {
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
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();
}

void error(int line, string msg, string where) {
    cout << "error on line " << line
        << " @ " << where << ": "
        << msg << endl;
    hadError = true;
}