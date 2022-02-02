#include "tools.h"

int runTool(vector<string> args) {
    auto argc = args.size();
    for (int i{ 0 }; i < argc; i++) {
        std::cout << args[i] << std::endl;
    }
    if (argc < 3) {
        printf("choose tool to run");
        return 0;
    }
    if (args[2] == "generateAst")
        genAst(args);
    else if (args[2] == "prettyPrinter")
        testPrettyPrinter();
    else
        printf("no such tool");
    return 0;
}

void testPrettyPrinter() {
    Lit lit{ 12 };
    prettyPrinter pp;
    cout << pp.print(lit) << std::endl;
}

// adapted from DelftStack:
void trim(string& str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
}

// adapted from Shiqi Ai on SO:
vector<string> split(string str, string token) {
    vector<string> result;
    while (str.size()) {
        auto index = str.find(token);
        string substr;
        if ((substr = str.substr(0, index)) == "") {
            str = str.substr(index + token.size());
        }
        else if (index != string::npos) {
            result.push_back(substr);
            str = str.substr(index + token.size());
        }
        else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

string toLower(string str) {
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c <= 'Z' && c >= 'A')
            str[i] -= ('Z' - 'z');
    }
    return str;
}

// prints a vector - Dr. Halterman
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "\n{\n";
    if (!vec.empty()) {
        auto iter = vec.begin();
        auto end = vec.end();
        os << *iter++;
        while (iter != end)
            os << '\n' << *iter++;
    }
    os << "\n}\n";
    return os;
}