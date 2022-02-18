#include "generator.h"
#include "helpers.h" // for trim|split helpers

void generator(vector<string> args) {
	auto argc = args.size();
	string outputDir;
	if (argc <= 3) {
		printf("Usage: tools <tool> <output directory>\n");
		return;
	} else {
		outputDir = args[3];
	}
	cout << "generating in: " << outputDir << std::endl;
	writeSyntax(outputDir, "Expr", 
		{ "../scanner/Token.h" },
		vector<string>{
		"Assign : Token name, Expr* value",
			"Binary : Expr* left, Token op, Expr* right",
			"Grouping : Expr* expression",
			"Literal : LoxType value",
			"Logical : Expr* left, Token op, Expr* right",
			"Ternary : Expr* condition, Expr* ifTrue, Expr* ifFalse",
			"Unary : Token op, Expr* right",
			"Variable : Token name"
	});
	writeSyntax(outputDir, "Stmt", 
		{ "Expr.hpp" },
		vector<string>{
		"Block : vector<Stmt*> statements",
			"Expression	: Expr* expression",
			"For : Stmt* initializer, Stmt* condition, Stmt* change, Stmt* body",
			"If : Expr* condition, Stmt* thenBranch, Stmt* elseBranch",
			"Print : Expr* expression",
			"Var : Token name, Expr* initializer",
			"While : Expr* condition, Stmt* body"
	});
}

void writeSyntax(string outputDir, string base, 
	vector<string> include, vector<string> types) {
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
	string hpp;
	hpp = "#pragma once\n";
	auto curIncl = include.begin();
	auto lastIncl = include.end();
	while (curIncl != lastIncl) {
		*curIncl = curIncl->substr(0, curIncl->find(':'));
		trim(*curIncl);
		hpp += "#include \"" + *curIncl + "\"\n\n";
		curIncl++;
	}
	// prototype structs
	hpp += buildProtoStructs(names);
	// visitor struct
	hpp += buildVisitorStruct(base, names);
	// expression struct
	hpp += buildBase(base);
	// derived structs
	auto type = types.begin();
	auto end = types.end();
	name = names.begin();
	while (type != end) {
		auto pos = type->find(':');
		string contents = type->substr(++pos);
		hpp += buildStruct(base, *name, split(contents, ","));
		type++;
		name++;
	}

	fprintf(file, hpp.c_str());
	fclose(file);
}

string buildVisitorStruct(string base, vector<string> names) {
	string code = "struct " + base + "Visitor {\n";
	if (names.empty()) return code += "}\n";
	auto name = names.begin();
	auto end = names.end();
	while (name != end) {
		code += TAB + "virtual void visit" + *name + "(const " +
			*name + "* " + toLower(base) + ") = 0;\n";
		name++;
	}
	code += "};\n\n";
	return code;
}

string buildBase(string base) {
	string code = "struct " + base + " {\n";
	code += TAB + "virtual ~" + base + "() = default;\n";
	code += TAB + "virtual void accept(" + base + 
		"Visitor* visitor) = 0;\n";
	code += "};\n\n";
	return code;
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
	string code = "struct " + name + " : " + base + " {\n";
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
	// accept
	code += TAB + "void accept(" + base + 
		"Visitor* visitor) override {\n";
	code += TABx2 + "visitor->visit" + name + "(this);\n";
	code += TAB + "}\n";

	//end
	code += "};\n\n";
	return code;
}
