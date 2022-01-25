#include "genAst.h"

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
    program += "#include \"../scanner/Token.h\"\n";
    // prototype structs
    program += buildProtoStructs(names);
    // base
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
