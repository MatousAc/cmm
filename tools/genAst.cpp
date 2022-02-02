#include "genAst.h"

void genAst(vector<string> args) {
    auto argc = args.size();
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
    string fp = outputDir + "/" + base + ".hpp";
    const char* filepath = fp.c_str();
    FILE* file; // safely open a file
    errno_t err;
    if (((err = fopen_s(&file, filepath, "w")) != 0) ||
        (file == nullptr)) {
        cout << filepath << " could not be opened: " << file;
        return;
    }
    // struct names
    vector<string> names(types);
    auto name = names.begin();
    auto back = names.end();
    while (name != back) {
        *name = name->substr(0, name->find(':'));
        trim(*name);
        name++;
    }
    // header
    string program;
    program = "#pragma once\n";
    program += "#include \"../scanner/Token.h\"\n\n";
    // prototype structs
    program += buildProtoStructs(names);
    // base
    program += "struct " + base + " {\n";
    program += TAB + "virtual ~" + base + "() = default;\n\n";
        // visitor class
    program += buildVisitorClass(base, names);
    program += "};\n\n";
    // derived classes
    auto type = types.begin();
    auto end = types.end();
    name = names.begin();
    while (type != end) {
        auto pos = type->find(':');
        string contents = type->substr(++pos);
        program += buildStruct(base, *name, split(contents, ","));
        type++;
        name++;
    }
    fprintf(file, program.c_str());
    fclose(file);
}

string buildProtoStructs(vector<string> names) {
    string code = "";
    auto name = names.begin();
    auto back = names.end();
    while (name != back) {
        code += "struct " + *name + ";\n";
        name++;
    }
    code += "\n";
    return code;
}

string buildVisitorClass(string base, vector<string> names) {
    string code = TAB + "template <typename T>";
    code += TAB + "class Visitor {\n" + TAB + "public:\n";
    if (names.empty()) return code += "}\n";
    auto name = names.begin();
    auto end = names.end();
    while (name != end) {
        code += TABx2 + "virtual T visit" + *name +
            "(const " + *name + "& " + toLower(base) + ") = 0;\n";
        name++;
    }
    code += TAB + "};\n" + TAB + "template <typename T>\n";
    code += TAB + "T accept(Visitor<T>& visitor) const;\n";
    return code;
}

string buildStruct(string base, string name, vector<string> fields) {
    // string splitting
    vector<vector<string>> members{};
    if (fields.empty()) return "";
    auto field = fields.begin();
    auto back = fields.end();
    while (field != back)
        members.push_back({ split(*(field++), " ") });
    trim(name);

    // putting the struct together
    string code = "struct " + name + " : public " 
        + base + " {\n";
    if (members.empty()) return "";
    auto member = members.begin();
    auto end = members.end();
    while (member != end) {// declerations
        code += TAB + (*member)[0] + " " + 
            (*member)[1] + ";\n";
        member++;
    }
    // constructor
    code += "\n" + TAB + name + "(";
    member = members.begin();
    while (member != end) {
        if (member != members.begin()) code += ", ";
        code += (*member)[0] + " " + (*member)[1];
        member++;
    }
    code += ")\n" + TABx2 + ":";
    member = members.begin();
    while (member != end) {
        if (member != members.begin()) code += ", ";
        code += (*member)[1] + "{ " + (*member)[1] + " }";
        member++;
    }
    code += " {}\n\n";
    // visitor accept override
    code += TAB + "template <typename T>\n";
    code += TAB + "T " + base + 
        "::accept(Visitor<T>& visitor) const {\n";
    code += TABx2 + "return visitor.visit" + 
        name + "(*this);\n";
    code += TAB + "}\n";

    //end
    code += "};\n\n";
    return code;
}
