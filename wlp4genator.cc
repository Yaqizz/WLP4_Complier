#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;

// symbol table
// map<wain, map<variable name, pair<type, offset>>>
map<string, map<string, pair<string, int>>> symbol_table;

//curr table
map<string, pair<string, int>> curr_table;

string procedure_name = "";
int offset = 0;
int ifcounter = 0;
int whilecounter = 0;

void print_symbol_table() {
    for(map<string, map<string, pair<string, int>>>::iterator it = symbol_table.begin(); it != symbol_table.end(); ++it) {
        cout << it->first << endl;
        for(map<string, pair<string, int>>::iterator itt = it->second.begin(); itt != it->second.end(); ++itt) {
            cout << itt->first << " " << itt->second.first << " " << itt->second.second << endl;
        }
    }
}

class Node {
    public:
    string rule;
    string LHS;
    // terminal lexeme = name or ".EMPTY"
    string lexeme;
    // type = int/int*/""
    string type;

    vector<shared_ptr<Node>> RHS;
    unsigned int rhs_size = 0;
};

bool ifterminal(string kind) {
    for (unsigned int i = 0; i < kind.size(); i++) {
        if (isupper(kind[i]) == 0) {
            return false;
        } 
    }
    return true;
}

shared_ptr<Node> buildtree() {
    Node root;
    if (cin.eof()) {
        return make_shared<Node>(root);
    }

    string line = "";
    getline(cin, line);
    string s = "";
    vector<string> my_rule;  //忽略空格，所有string
    int other = 0;   // : int
    for (unsigned int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            if (s == ":") {
                other = 2;
            }
            my_rule.emplace_back(s);
            s = "";
        } else {
            s.push_back(line[i]);
        }
    }
    my_rule.emplace_back(s);
 
    root.rule = line;
    root.LHS = my_rule[0];
    unsigned int true_len = my_rule.size() - other;
    if ((ifterminal(my_rule[0]) || my_rule[1] == ".EMPTY") && true_len == 2) {
        root.lexeme = my_rule[1];
        if (my_rule.size() == 4 && other == 2) {
            root.type = my_rule[3];
        } else {
            root.type = my_rule[1];
        }
    } else {
        root.lexeme = "";
        root.type = "";
    }
    root.rhs_size = my_rule.size() - other - 1;
    unsigned int rhs_size = root.rhs_size;
    if ((ifterminal(my_rule[0]) || my_rule[1] == ".EMPTY") && true_len == 2) {
        Node one;
        root.RHS.emplace_back(make_shared<Node>(one));
        return make_shared<Node>(root);
    }
    for (unsigned int i = 0; i < rhs_size; i++) {
        root.RHS.emplace_back(buildtree());
    }
    return make_shared<Node>(root);
}

void prepare() {
    cout << ".import print" << endl;
    cout << "lis $4" << endl;
    cout << ".word 4" << endl;
    cout << "lis $10" << endl;
    cout << ".word print" << endl;
    cout << "lis $11" << endl;
    cout << ".word 1" << endl;
    cout << "sub $29, $30, $4" << endl;
}

pair<string, string> myget(Node& root) {
    pair<string, string> result;
    if (root.LHS == "ID" || root.LHS == "NUM") {
        result.first = root.type;
        result.second = root.lexeme;
    }
    return result;
}

void push(string reg) {
    cout << "sw " << reg << ", -4($30)" << endl;
    cout << "sub $30, $30, $4" << endl;
}

void pop(string reg) {
    cout << "add $30, $30, $4" << endl;
    cout << "lw " << reg << ", -4($30)" << endl;
}


void code(Node& root) {
    string type = "";
    string id = "";
    //cout << root.rule << endl;
    if (root.rule == "main INT WAIN LPAREN dcl COMMA dcl RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE") {
        procedure_name = "WAIN";
        push("$1");
        push("$2");
        map<string, pair<string, int>> table;
        symbol_table[procedure_name] = table;
        curr_table = symbol_table[procedure_name];
        offset = 0;
    } else if (root.rule == "dcl type ID") {             //store symbol table
        type = myget(*root.RHS[1]).first;
        id = myget(*root.RHS[1]).second;
        //cout << type << " " << id << endl;
        curr_table.emplace(id, make_pair(type, offset));
        symbol_table[procedure_name] = curr_table;
        offset -= 4;
    } else if (root.LHS == "factor" && root.RHS[0]->LHS == "ID") { // factor ID
        id = myget(*root.RHS[0]).second;
        map<string, pair<string, int>> next = symbol_table.find(procedure_name)->second;
        int off = next.find(id)->second.second;
        cout << "lw $3, " << off << "($29)" << endl;
    } else if (root.LHS == "factor" && root.RHS[0]->LHS == "NUM") {  //factor NUM
        id = myget(*root.RHS[0]).second;
        cout << "lis $3" << endl;
        cout << ".word " << id << endl;
    } else if (root.LHS == "factor" &&  root.RHS[0]->LHS == "LPAREN" && root.RHS[1]->LHS == "expr" && root.RHS[2]->LHS == "RPAREN") {  // factor LPAREN expr RPAREN
        code(*root.RHS[1]);
    } else if ((root.LHS == "expr" && root.rhs_size == 1) || (root.LHS == "term" && root.rhs_size == 1)) {   // expr term + term factor
        code(*root.RHS[0]);


    } else if (root.rule == "dcls dcls dcl BECOMES NUM SEMI") {  // dcls dcls dcl BECOMES NUM SEMI
        code(*root.RHS[0]);
        id = myget(*root.RHS[3]).second;
        cout << "lis $3" << endl;
        cout << ".word " << id << endl;
        push("$3");
        code(*root.RHS[1]);
    } else if (root.rule == "statements statements statement") {  // statements statements statement
        code(*root.RHS[0]);
        code(*root.RHS[1]);
    } else if (root.rule == "statement lvalue BECOMES expr SEMI") {  // statement lvalue BECOMES expr SEMI
        code(*root.RHS[2]);           // expr store in $3
        code(*root.RHS[0]);           // sw $3, off ($29)
    } else if (root.LHS == "lvalue" && root.RHS[0]->LHS == "ID") {  // lvalue ID
        id = myget(*root.RHS[0]).second;
        map<string, pair<string, int>> next = symbol_table.find(procedure_name)->second;
        int off = next.find(id)->second.second;
        cout << "sw $3, " << off << "($29)" << endl;
    } else if (root.LHS == "lvalue" &&  root.RHS[0]->LHS == "LPAREN" && root.RHS[1]->LHS == "lvalue" && root.RHS[2]->LHS == "RPAREN") { //lvalue LPAREN lvalue RPAREN
        code(*root.RHS[1]);


    } else if (root.LHS == "expr" &&  root.RHS[0]->LHS == "expr" && root.RHS[1]->LHS == "PLUS" && root.RHS[2]->LHS == "term") {  // expr expr PLUS term
        code(*root.RHS[0]);           // expr store in $3
        push("$3");
        code(*root.RHS[2]);           // term store in $3
        pop("$5");
        cout << "add $3, $3, $5" << endl;
    } else if (root.LHS == "expr" &&  root.RHS[0]->LHS == "expr" && root.RHS[1]->LHS == "MINUS" && root.RHS[2]->LHS == "term") {  // expr expr MINUS term
        code(*root.RHS[0]);           // expr store in $3
        push("$3");
        code(*root.RHS[2]);           // term store in $3
        pop("$5");
        cout << "sub $3, $5, $3" << endl;
    } else if (root.LHS == "term" &&  root.RHS[0]->LHS == "term" && root.RHS[1]->LHS == "STAR" && root.RHS[2]->LHS == "factor") {  // term term STAR factor
        code(*root.RHS[0]);           // expr store in $3
        push("$3");
        code(*root.RHS[2]);           // term store in $3
        pop("$5");
        cout << "mult $3, $5" << endl;
        cout << "mflo $3" << endl;
    } else if (root.LHS == "term" &&  root.RHS[0]->LHS == "term" && root.RHS[1]->LHS == "SLASH" && root.RHS[2]->LHS == "factor") {  // term term SLASH factor
        code(*root.RHS[0]);           // expr store in $3
        push("$3");
        code(*root.RHS[2]);           // term store in $3
        pop("$5");
        cout << "div $5, $3" << endl;
        cout << "mflo $3" << endl;
    } else if (root.LHS == "term" &&  root.RHS[0]->LHS == "term" && root.RHS[1]->LHS == "PCT" && root.RHS[2]->LHS == "factor") {  // term term PCT factor
        code(*root.RHS[0]);           // expr store in $3
        push("$3");
        code(*root.RHS[2]);           // term store in $3
        pop("$5");
        cout << "div $5, $3" << endl;
        cout << "mfhi $3" << endl;
    

    } else if (root.rule == "statement IF LPAREN test RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE") {
        code(*root.RHS[2]);
        cout << "beq $3, $0, else" << ifcounter << endl;
        code(*root.RHS[5]);
        cout << "beq $0, $0, endif" << ifcounter << endl;
        cout << "else" << ifcounter << ":" << endl;
        code(*root.RHS[9]);
        cout << "endif" << ifcounter << ":" << endl;
        ifcounter++;
    } else if (root.rule == "statement WHILE LPAREN test RPAREN LBRACE statements RBRACE") {
        cout << "loop" << whilecounter << ":" << endl;
        code(*root.RHS[2]);
        cout << "beq $3, $0, endwhile" << whilecounter << endl;
        code(*root.RHS[5]);
        cout << "beq $0, $0, loop" << whilecounter << endl;
        cout << "endwhile" << whilecounter << ":" << endl;
        whilecounter++;
    } else if (root.rule == "test expr EQ expr") {  // ==
        code(*root.RHS[0]);
        push("$3");
        code(*root.RHS[2]);
        pop("$5");
        cout << "slt $6, $3, $5" << endl;
        cout << "slt $7, $5, $3" << endl;
        cout << "add $3, $6, $7" << endl;
        cout << "sub $3, $11, $3" << endl;
    } else if (root.rule == "test expr NE expr") {  // !=
        code(*root.RHS[0]);
        push("$3");
        code(*root.RHS[2]);
        pop("$5");
        cout << "slt $6, $3, $5" << endl;
        cout << "slt $7, $5, $3" << endl;
        cout << "add $3, $6, $7" << endl;
    } else if (root.rule == "test expr LT expr") {  // <
        code(*root.RHS[0]);           // expr store in $3
        push("$3");
        code(*root.RHS[2]);           // term store in $3
        pop("$5");
        cout << "slt $3, $5, $3" << endl; 
    } else if (root.rule == "test expr LE expr") {  // <= 
        code(*root.RHS[0]);
        push("$3");
        code(*root.RHS[2]);
        pop("$5");
        cout << "slt $3, $3, $5" << endl;
        cout << "sub $3, $11, $3" << endl;

    } else if (root.rule == "test expr GE expr") {  // >=
        code(*root.RHS[0]);
        push("$3");
        code(*root.RHS[2]);
        pop("$5");
        cout << "slt $3, $5, $3" << endl;
        cout << "sub $3, $11, $3" << endl;
    } else if (root.rule == "test expr GT expr") {  // >
        code(*root.RHS[0]);
        push("$3");
        code(*root.RHS[2]);
        pop("$5");
        cout << "slt $3, $3, $5" << endl;



    } else if (root.rule == "statement PRINTLN LPAREN expr RPAREN SEMI") {   // 
        push("$1");
        code(*root.RHS[2]);
        cout << "add $1, $3, $0" << endl;
        push("$31");
        cout << "jalr $10" << endl;
        pop("$31");
        pop("$1");

    } else if (root.rule == "EOF EOF") {
        int num = (0 - offset) / 4;
        for (int i = 2; i < num; i++) {
            cout << "add $30, $30, $4" << endl;   // pop 额外的
        }
        pop("$2");
        pop("$1");
    }
}

void wain(Node& root) {
    if (root.rhs_size == 0) {return;}
    if (root.LHS == "expr" || root.LHS == "dcls" || root.LHS == "statements") {
        code(root);
    } else {
        code(root);
        for (unsigned int i = 0; i < root.rhs_size; i++) {
            wain(*root.RHS[i]);
        }
    }
}

void myprint(Node& root) {
    if (root.rhs_size == 0) {return;}
    cout << root.rule << endl;
    for (unsigned int i = 0; i < root.rhs_size; i++) {
        myprint(*root.RHS[i]);
    }
}

void end() {
    cout << "add $29, $29, $4" << endl;
    cout << "jr $31" << endl;
}


int main() {
    shared_ptr<Node> Tree = make_shared<Node>();
    Tree = buildtree();
    //myprint(*Tree);
    prepare();
    wain(*Tree);
    end();
    //print_symbol_table();
    return 0;
}
