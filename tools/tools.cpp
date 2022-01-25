#include "tools.h"

int runTool(vector<string> args) {
    int argc = args.size();
    for (int i{ 0 }; i < argc; i++) {
        std::cout << args[i] << std::endl;
    }
    if (argc < 3) {
        printf("choose tool to run");
        return 0;
    }
    if (args[2] == "generateAst")
        genAst(args);
    else
        printf("no such tool");
    return 0;
}

void genAst(vector<string> args) {
    int argc = args.size();
    string outputDir;
    if (argc <= 3) {
        printf("Usage: tools <tool> <output directory>\n");
        outputDir = ".";
    }
    else {
        outputDir = args[3];
    }
    cout << "generating in: " << outputDir << std::endl;
    writeAst(outputDir, "Expression", vector<string>{
        "Binary     : Expression left, Token op, Expression right",
        "Grouping   : Expression expression",
        "Lit        : Literal value",
        "Unary      : Token op, Expression right"
    });
}

void writeAst(string outputDir, string base, vector<string> types) {
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
    program += "#include \"../scanner/Token.h\"\n";
    program += "struct " + base + " {\n";
    program += TAB + "virtual ~" + base + "() = default;\n\n";

    // visitor class
    program += buildVisitorClass(base, types);
    program += TAB + "virtual void accept(Visitor&) const {}\n";
    program += "};\n\n";
    // derived classes
    auto type = types.begin();
    auto end = types.end();
    while (type != end) {
        int pos = type->find(':');
        string structname = type->substr(0, pos);
        string contents = type->substr(++pos);
        program += buildStruct(base, structname, contents);
        type++;
    }
    fprintf(file, program.c_str());
    fclose(file);
}


string buildVisitorClass(string base, vector<string> types) {
    string code = TAB + "class Visitor {\n" + TAB + "public:\n";
    if (types.empty()) return code += "}\n";
    auto type = types.begin();
    auto end = types.end();
    while (type != end) {
        string name = type->substr(0, type->find(' '));
        code += TAB + TAB + "virtual void visit" + name +
        "(const " + name + "& " + toLower(base) + ") = 0;\n";
        type++;
    }
    code += TAB + "};\n\n";
    return code;
}

string buildStruct(string base, string structname, string contents) {
    // string splitting
    vector<string> fields = split(contents, ",");
    vector<vector<string>> members{};
    if (fields.empty()) return "";
    auto field = fields.begin();
    auto back = fields.end();
    while (field != back)
        members.push_back({ split(*(field++), " ") });
    trim(structname);

    // putting the struct together
    string code = "struct " + structname + " : public " + base + " {\n";
    if (members.empty()) return "";
    auto member = members.begin();
    auto end = members.end();
    while (member != end) {// declerations
        code += TAB + (*member)[0] + " " + (*member)[1] + ";\n";
        member++;
    }
    // constructor
    code += "\n" + TAB + structname + "(";
    member = members.begin();
    while (member != end) {
        if (member != members.begin()) code += ", ";
        code += (*member)[0] + " " + (*member)[1];
        member++;
    }
    code += ")\n" + TAB + TAB + ":";
    member = members.begin();
    while (member != end) {
        if (member != members.begin()) code += ", ";
        code += (*member)[1] + "{ " + (*member)[1] + " }";
        member++;
    }
    code += " {}\n\n";
    // visitor accept override
    code += TAB + "void accept(Visitor& visitor) const override {\n";
    code += TAB + TAB + "visitor.visit" + structname + "(*this);\n";
    code += TAB + "}\n";

    //end
    code += "};\n\n";
    return code;
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
        int index = str.find(token);
        string substr;
        if ((substr = str.substr(0, index)) == "") {
            str = str.substr(index + token.size());
        } else if (index != string::npos) {
            result.push_back(substr);
            str = str.substr(index + token.size());
        } else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

//
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