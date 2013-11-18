// ============================================================================ 
// main.cpp
// ~~~~~~~~
// Hung Q. ngo
// Modified by: Sean Frischmann
// ****************************************************************************
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>  // for exit()

#include "listmanip.h"
#include "Lexer.h"
#include "error_handling.h"
#include "term_control.h"

using namespace std;

// -----------------------------------------------------------------------------
// prototypes, typedefs, and global variables
// -----------------------------------------------------------------------------
typedef void (*cmd_t)(Lexer);
void loaddb_cmd(Lexer);
void print_list_cmd(Lexer);
void slow_union_cmd(Lexer);
void fast_union_cmd(Lexer);
void slow_intersect_cmd(Lexer);
void fast_intersect_cmd(Lexer);
void bye(Lexer);    // simply quit
void prompt();
map<string, vector< vector<Token> > > list_table;
extern const string usage_msg;                                                  

/**
 * -----------------------------------------------------------------------------
 * main body
 * -----------------------------------------------------------------------------
 */
int main() {
    Lexer lexer; string line; Token tok;
    map<string,cmd_t> cmd_map;
    cmd_map["exit"]  = &bye;
    cmd_map["bye"]   = &bye;
    cmd_map["quit"]  = &bye;
    cmd_map["loaddb"]   = &loaddb_cmd;
    cmd_map["print"] = &print_list_cmd;
    cmd_map["slowunion"] = &slow_union_cmd;
    cmd_map["fastunion"] = &fast_union_cmd;
    cmd_map["slowintersect"] = &slow_intersect_cmd;
    cmd_map["fastintersect"] = &fast_intersect_cmd;

    cout << term_cc(YELLOW) << usage_msg << endl;

    while (cin) {
        prompt(); getline(cin, line); lexer.set_input(line);
        if (!lexer.has_more_token()) continue;
        tok = lexer.next_token();
        if (tok.type != IDENT) { error_return("Syntax error\n"); continue; }

        if (cmd_map.find(tok.value) != cmd_map.end()) {
            try {
                cmd_map[tok.value](lexer);
            } catch (runtime_error &e) {
                error_return(e.what());
            }
        } else {
            error_return("Unknown command");
        }
    }
    return 0;

}

/**
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 */
void _cmd(Lexer lex) 
{

}


/**
 * -----------------------------------------------------------------------------
 * process command 'print vecname'
 * -----------------------------------------------------------------------------
 */
void print_list_cmd(Lexer lex) 
{
    Token tok = lex.next_token();
    if (tok.type != IDENT || lex.has_more_token())
        throw runtime_error("SYNTAX: print vecname");
    if (list_table.find(tok.value) == list_table.end())
        throw runtime_error(tok.value + " not defined or already destroyed");
    print_list(list_table[tok.value]);
}


/**
 * -----------------------------------------------------------------------------
 * process command 'slowintersect vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void slow_intersect_cmd(Lexer lex) 
{
    vector<Token> vec = lex.tokenize();
    if (vec.size() != 2 || vec[0].type != IDENT || vec[1].type != IDENT)
        throw runtime_error("SYNTAX: slowintersect vecname1 vecname2");

    if (list_table.find(vec[0].value) == list_table.end())
        throw runtime_error(string("The list " + vec[0].value + 
                                   " doesn't exist"));
    if (list_table.find(vec[1].value) == list_table.end())
        throw runtime_error(string("The list " + vec[1].value + 
                                   " doesn't exist"));

    list_table[vec[0].value] = slow_intersect(list_table[vec[0].value],
                                           list_table[vec[1].value]);
}

/**
 * -----------------------------------------------------------------------------
 * process command 'fastintersect vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void fast_intersect_cmd(Lexer lex) 
{
    vector<Token> vec = lex.tokenize();
    if (vec.size() != 2 || vec[0].type != IDENT || vec[1].type != IDENT)
        throw runtime_error("SYNTAX: fastintersect vecname1 vecname2");

    if (list_table.find(vec[0].value) == list_table.end())
        throw runtime_error(string("The list " + vec[0].value + 
                                   " doesn't exist"));
    if (list_table.find(vec[1].value) == list_table.end())
        throw runtime_error(string("The list " + vec[1].value + 
                                   " doesn't exist"));

    list_table[vec[0].value] = fast_intersect(list_table[vec[0].value],
                                           list_table[vec[1].value]);
}
/**
 * -----------------------------------------------------------------------------
 * process command 'slowunion vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void slow_union_cmd(Lexer lex) 
{
    vector<Token> vec = lex.tokenize();
    if (vec.size() != 2 || vec[0].type != IDENT || vec[1].type != IDENT)
        throw runtime_error("SYNTAX: slowunion vecname1 vecname2");

    if (list_table.find(vec[0].value) == list_table.end() ||
        list_table.find(vec[1].value) == list_table.end())
        throw runtime_error("Give me existing lists only");

    list_table[vec[0].value] = slow_union(list_table[vec[0].value],
                                           list_table[vec[1].value]);
    list_table.erase(vec[1].value);
}

/**
 * -----------------------------------------------------------------------------
 * process command 'fastunion vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void fast_union_cmd(Lexer lex) 
{
    vector<Token> vec = lex.tokenize();
    if (vec.size() != 2 || vec[0].type != IDENT || vec[1].type != IDENT)
        throw runtime_error("SYNTAX: fastunion vecname1 vecname2");

    if (list_table.find(vec[0].value) == list_table.end() ||
        list_table.find(vec[1].value) == list_table.end())
        throw runtime_error("Give me existing lists only");

    list_table[vec[0].value] = fast_union(list_table[vec[0].value],
                                           list_table[vec[1].value]);
    list_table.erase(vec[1].value);
}
/**
 * -----------------------------------------------------------------------------
 * process command 'loaddb vecname'
 * -----------------------------------------------------------------------------
 */
void loaddb_cmd(Lexer lex) 
{
    Token tok = lex.next_token();
    if (tok.type != IDENT)
        throw runtime_error("loaddb filename");

    if (list_table.find(tok.value) != list_table.end())
        throw runtime_error(tok.value + " already exists");

    vector<Token> tok_vec = lex.tokenize();
    if (tok_vec.size() == 0)
        throw runtime_error("Please enter some integers");
    for (size_t i=0; i < tok_vec.size(); i++)
        if (tok_vec[i].type != INTEGER)
            throw runtime_error("Please enter integers only");
    
    list_table[tok.value] = loaddb(tok_vec);
}

/**
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 */
void _cmd(Lexer lexer) 
{

}

/**
 * -----------------------------------------------------------------------------
 * terminates the program, ignores all parameters
 * -----------------------------------------------------------------------------
 */
void bye(Lexer lexer) 
{
    if (lexer.has_more_token()) {
        throw runtime_error("Syntax error: use bye/exit/quit");
    } else {
        exit(0);
    }
}

/**                                                                             
 * -----------------------------------------------------------------------------
 * print the list                                                               
 * -----------------------------------------------------------------------------
 */                                                                             
void print_list(Node* ptr) {
	cout << term_cc(CYAN);                                                      
    while (ptr != NULL) {                                                       
        cout << ptr->key << " ";                                                
        ptr = ptr->next;                                                        
    }                                                                           
    cout << endl << term_cc();                                                  
} 

/**
 * -----------------------------------------------------------------------------
 * just print a prompt.
 * -----------------------------------------------------------------------------
 */
void prompt() 
{
    cout << term_cc(BLUE) << "> " << term_cc() << flush;
}
