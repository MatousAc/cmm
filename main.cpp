// conatins main and basic interpreter structure
#include "Lox.h"

int main(int argc, char* argv[]) {
    // running tools
    vector<string> args{};
    for (int i{ 0 }; i < argc; i++) {
        args.push_back(argv[i]);
    };

    if ((argc > 1) and args[1] == "-t") {
        runTool(args);
        return 0;
    };

    // we can interpret now
    // make Lox structure
    Lox lox{};
    if (argc <= 1)
        lox.runPrompt();
    else if (argc > 2)
        printf("invalid # of args\n");
    else
        lox.runFile(argv[1]);
    return 0;
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
