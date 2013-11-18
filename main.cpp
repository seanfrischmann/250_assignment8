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

#include "listmanip.cpp"
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
void slow_union_outputfile_cmd(Lexer);
void fast_union_outputfile_cmd(Lexer);
void fast_union_cmd(Lexer);
void slow_intersect_cmd(Lexer);
void slow_intersect_outputfile_cmd(Lexer);
void fast_intersect_outputfile_cmd(Lexer);
void fast_intersect_cmd(Lexer);
void bye(Lexer);    // simply quit
void prompt();
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
    cmd_map["slowunion"] = &slow_union_cmd;
    cmd_map["slowunion outputfile"] = &slow_union_outputfile_cmd;
    cmd_map["fastunion"] = &fast_union_cmd;
    cmd_map["fastunion outputfile"] = &fast_union_outputfile_cmd;
    cmd_map["slowintersect"] = &slow_intersect_cmd;
    cmd_map["slowintersect outputfile"] = &slow_intersect_outputfile_cmd;
    cmd_map["fastintersect"] = &fast_intersect_cmd;
    cmd_map["fastintersect outputfile"] = &fast_intersect_output_cmd;

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
void fast_intersect_outputfile_cmd(){
	fast_intersect_outputfile(vector< vector<Token> > vec);
}


/**
 * -----------------------------------------------------------------------------
 * process command 'print vecname'
 * -----------------------------------------------------------------------------
 */
void slow_intersect_outputfile_cmd(){
	slow_intersect_outputfile(vector< vector<Token> > vec);
}


/**
 * -----------------------------------------------------------------------------
 * process command 'slowintersect vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void slow_intersect_cmd(){
	slow_intersect(vector< vector<Token> > vec);
}

/**
 * -----------------------------------------------------------------------------
 * process command 'fastintersect vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void fast_intersect_cmd(){
	fast_intersect(vector< vector<Token> > vec);
}

/**
 * -----------------------------------------------------------------------------
 * process command 'slowunion vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void slow_union_outputfile_cmd(){
	slow_union_outputfile(vector< vector<Token> > vec);
}
/**
 * -----------------------------------------------------------------------------
 * process command 'slowunion vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void slow_union_cmd(){
	slow_union(vector< vector<Token> > vec);
}

/**
 * -----------------------------------------------------------------------------
 * process command 'fastunion vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void fast_union_output_cmd(){
	fast_union_outputfile(vector< vector<Token> > vec);
}
/**
 * -----------------------------------------------------------------------------
 * process command 'fastunion vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
void fast_union_cmd(){
	fast_union(vector< vector<Token> > vec);
}
/**
 * -----------------------------------------------------------------------------
 * process command 'loaddb vecname'
 * -----------------------------------------------------------------------------
 */
void loaddb_cmd(Lexer lex){
	loaddb(vector<Token> vec);
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
 * just print a prompt.
 * -----------------------------------------------------------------------------
 */
void prompt() 
{
    cout << term_cc(BLUE) << "> " << term_cc() << flush;
}
