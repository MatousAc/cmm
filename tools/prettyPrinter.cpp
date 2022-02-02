#include "prettyPrinter.h"

string prettyPrinter::on_visit(Lit* lit) {
    /*if (lit.value.empty()) return "nil";
    return lit.value.toString();*/
    //printf("on_visit in Lit called\n");
    return "on_visit in Lit called";
}


//string prettyPrinter::paranthesise(const string& name,
//    std::initializer_list<const Expression*> expressions) {
//    return "";
//}

