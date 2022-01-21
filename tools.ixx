export module tools;
import <stdio.h>;
//import <string>;
//using std::string;

void generateAst(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: tools <tool> <output directory>");
    }
    printf("generating . . .");
    //string outputDir = argv[0];
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("choose tool to run");
        return 0;
    }
    if (argv[2] == "generateAst")
        generateAst(argc, argv);
    else
        printf("no such tool");
    return 0;
}