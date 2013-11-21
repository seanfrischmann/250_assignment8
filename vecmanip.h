// ============================================================================ 
// // vecmanip.h
// // Sean Frischmann
// // ~~~~~~~
// // *****************************************************************************
//
#ifndef LIST_SORT_H_
#define LIST_SORT_H_

#include <cstddef> // this header defines NULL
#include <vector>
#include "Lexer.h"
using namespace std;
//
// // *****************************************************************************
// // Below are functions called in main.cpp and defined in vecmanip.cpp
// // *****************************************************************************
vector< vector<int> > loaddb(const vector<Token>& tok_vec);
void slow_intersect(const vector< vector<int> >& contents, bool outputfile);
void slow_union(const vector< vector<int> >& contents, bool outputfile);
void fast_intersect(const vector< vector<int> >& contents, bool outputfile);
void fast_union(const vector< vector<int> >& contents, bool outputfile);
#endif
