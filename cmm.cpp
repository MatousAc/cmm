// conatins main and basic interpreter structure
#include "cmm.h"
bool hadError = false;

int main(int argc, char* argv[]) {
    // running tools
    vector<string> args{};
    for (int i{ 0 }; i < argc; i++) {
        args.push_back(argv[i]);
    };
    // cheat
    //argc += 3;
    //args.push_back("-t");
    //args.push_back("generateAst");
    //args.push_back(".");
    if ((argc > 1) and args[1] == "-t") {
        runTool(args);
        return 0;
    };

    // initilize keywords
    keywords["and"] = AND;
    keywords["class"] = CLASS;
    keywords["else"] = ELSE;
    keywords["false"] = FALSE;
    keywords["for"] = FOR;
    keywords["fun"] = FUN;
    keywords["if"] = IF;
    keywords["nil"] = NIL;
    keywords["or"] = OR;
    keywords["print"] = PRINT;
    keywords["return"] = RETURN;
    keywords["super"] = SUPER;
    keywords["this"] = THIS;
    keywords["true"] = TRUE;
    keywords["var"] = VAR;
    keywords["while"] = WHILE;

    if (argc <= 1)
        runPrompt();
    else if (argc > 2)
        printf("invalid # of args\n");
    else
        runFile(argv[1]);
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

void runFile(char* filepath) {
    struct stat sb {};
    string program;
    FILE* file; // safely open a file
    errno_t err;
    if (( (err = fopen_s(&file, filepath, "r")) != 0) ||
        (file == nullptr) ) {
        cout << filepath << " could not be opened: " << file;
        return;
    }
    stat(filepath, &sb);
    program.resize(sb.st_size);
    fread(const_cast<char*>(program.data()), sb.st_size, 1, file);
    fclose(file);
    run(program);
    if (hadError) return;
}

void run(string& source) {
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();
    printTokens(tokens);
}

void error(int line, string msg, string where) {
    cout << "error on line " << line
        << " @ " << where << ": "
        << msg << endl;
    hadError = true;
}

// prints a vector - Dr. Halterman
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << '{';
    if (!vec.empty()) {
        auto iter = vec.begin();
        auto end = vec.end();
        os << *iter++;
        while (iter != end)
            os << ", " << *iter++;
    }
    os << '}';
    return os;
}


// prints a vector of tokens
void printTokens(vector<Token>& vec) {
    if (!vec.empty()) {
        auto iter = vec.begin();
        auto end = vec.end();
        printf("l: type\t| lexeme \tliteral\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        cout << (*iter++).toString() << endl;
        while (iter != end)
            cout << (*iter++).toString() << endl;
    }
}