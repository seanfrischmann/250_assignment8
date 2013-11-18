// ============================================================================ 
// listmanip.h
// ~~~~~~~
// Hung Q. Ngo
// - singly linked list node structure
// - prototypes for a couple of functions manipulating singly linked lists
// - DO NOT MODIFY THIS FILE
// *****************************************************************************

#ifndef LIST_SORT_H_
#define LIST_SORT_H_

#include <cstddef> // this header defines NULL
#include <vector>
#include "Lexer.h"

// *****************************************************************************
// the following two functions are already implemented in listmanip.cpp
// *****************************************************************************
void  print_list(vector< vector<Token> > vec); // print all nodes starting from ptr

// *****************************************************************************
// below are the functions you are asked to implement
// *****************************************************************************
vector< vector<Token> > sort_list(vector< vector<Token> > vec);  // sort & return new head to sorted list
vector< vector<Token> > loaddb(const std::vector<Token>&);   // create a new list 
vector< vector<Token> > merge_lists(vector< vector<Token> > vec, vector< vector<Token> > vec2); // merge two sorted lists
vector< vector<Token> > remove_duplicates(vector< vector<Token> > vec);   // remove duplicate elements from list
vector< vector<Token> > keep_common(vector< vector<Token> > vec, vector< vector<Token> > vec2);  // keep only common elements

#endif
