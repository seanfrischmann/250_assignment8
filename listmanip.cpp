// ============================================================================ 
// listmanip.cpp
// ~~~~~~~~~~~~~
//Sean Frischmann
// implement the missing functions
// ============================================================================ 

#include <iostream>
#include <stdexcept>
#include <sstream>
#include "listmanip.h"
#include "Lexer.h"
#include "term_control.h"

using namespace std; // BAD PRACTICE

extern const string usage_msg = "List Manipulation Toy. Version 0.1\n"
                                "Author: Sean Frischmann\n"
                                "Report bugs to seanfris@buffalo.edu";
/**
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 */
vector< vector<Token> > loaddb(const vector<Token>& tok_vec)
{

}

/**
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 */
vector< vector<Token> > sort_list(vector< vector<Token> > vec) 
{

}

/**
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 */
vector< vector<Token> > keep_common(vector< vector<Token> > vec1, vector< vector<Token> > vec2)
{

}


/**
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 */
vector< vector<Token> > remove_duplicates(vector< vector<Token> > vec)
{

}

/**
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 */
vector< vector<Token> > merge_lists(vector< vector<Token> > vec1, vector< vector<Token> > vec2) 
{

}

// *****************************************************************************
// DO NOT MODIFY THIS FILE BEYOND THIS POINT
// *****************************************************************************

/**
 * -----------------------------------------------------------------------------
 * free the memory of all nodes starting from ptr down
 * -----------------------------------------------------------------------------
 
void free_list(vector< vector<Token> > ptr) {
    vector< vector<Token> > temp;
    while (ptr != NULL) {
        temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
}

