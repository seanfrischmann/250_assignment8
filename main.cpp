// ============================================================================ 
// main.cpp
// ~~~~~~~~
// Hung Q. ngo
// Sean Frischmann
// ****************************************************************************
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>  // for exit()
#include <algorithm>

#include "vecmanip.h"
#include "Lexer.h"
#include "error_handling.h"
#include "term_control.h"

using namespace std;

// -----------------------------------------------------------------------------
// prototypes, typedefs, and global variables
// -----------------------------------------------------------------------------
typedef void (*cmd_t)(Lexer);
void loaddb_cmd(Lexer);
void slow_union_cmd(Lexer);
//void fast_union_outputfile_cmd(Lexer);
//void fast_union_cmd(Lexer);
void slow_intersect_cmd(Lexer);
void fast_intersect_cmd(Lexer);
void bye(Lexer);    // simply quit
void prompt();
extern const string usage_msg;
vector< vector<int> > input;

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
    //cmd_map["fastunion"] = &fast_union_cmd;
    //cmd_map["fastunion outputfile"] = &fast_union_outputfile_cmd;
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
 *Process slowintersect cmd
 * -----------------------------------------------------------------------------
 */
void slow_intersect_cmd(Lexer lex){
	vector<Token> vec= lex.tokenize();
	bool outputfile = false, skip = true;
	if(input.empty()){
		skip = false;
		cerr << "Nothing to intersect" << endl;
	}
	if(!vec.empty()){
		if(vec.at(0).value == "outputfile"){
			outputfile = true;
		}else{
			cerr << "Error: wrong command" << endl;
			skip = false;
		}
	}
	if(skip){
		slow_intersect(input, outputfile);
	}
}

/**
 * -----------------------------------------------------------------------------
 * process command 'fastintersect'
 * -----------------------------------------------------------------------------
 */
void fast_intersect_cmd(Lexer lex){
	vector<Token> vec= lex.tokenize();
	bool outputfile = false, skip = true;
	if(input.empty()){
		skip = false;
		cerr << "Nothing to intersect" << endl;
	}
	if(!vec.empty()){
		if(vec.at(0).value == "outputfile"){
			outputfile = true;
		}else{
			cerr << "Error: wrong command" << endl;
			skip = false;
		}
	}
	if(skip){
		fast_intersect(input, outputfile);
	}
}


/**
 * -----------------------------------------------------------------------------
 * process command 'slowunion'
 * -----------------------------------------------------------------------------
 */
void slow_union_cmd(Lexer lex){
	vector<Token> vec= lex.tokenize();
	bool outputfile = false, skip = true;
	if(input.empty()){
		skip = false;
		cerr << "Nothing to union" << endl;
	}
	if(!vec.empty()){
		if(vec.at(0).value == "outputfile"){
			outputfile = true;
		}else{
			cerr << "Error: wrong command" << endl;
			skip = false;
		}
	}
	if(skip){
		slow_union(input, outputfile);
	}
}

/**
 * -----------------------------------------------------------------------------
 * process command 'fastunion vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
/*void fast_union_output_cmd(Lexer lex){
	fast_union_outputfile(vector< vector<Token> > vec);
}
/**
 * -----------------------------------------------------------------------------
 * process command 'fastunion vecname1 vecname2'
 * -----------------------------------------------------------------------------
 */
/*void fast_union_cmd(Lexer lex){
	fast_union(vector< vector<Token> > vec);
}
/**
 * -----------------------------------------------------------------------------
 * process command 'loaddb vecname'
 * -----------------------------------------------------------------------------
 */
void loaddb_cmd(Lexer lex){
	input.erase(input.begin(), input.end());
	input = loaddb(lex.tokenize());
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
