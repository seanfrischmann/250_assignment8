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
 * create a new singly linked list containing keys which are integers from 
 * a given vector of tokens
 * return the pointer to the head of the newly created list
 * -----------------------------------------------------------------------------
 */
Node* new_list(const vector<Token>& tok_vec)
{
    // YOUR CODE GOES HERE
	Node* head;
	istringstream str1(tok_vec.at(tok_vec.size()-1).value);
	int num1;
	str1 >> num1;
	head = new Node(num1);
	if(!tok_vec.empty()){
		for(int i=(tok_vec.size()-2); i>=0;i--){
			string temp = tok_vec.at(i).value;
			istringstream str2(temp);
			int num2;
			str2 >> num2;
			head =new Node(num2,head);
		}
	}
    return head; // and don't return NULL unless you have to
}

/**
 * -----------------------------------------------------------------------------
 * sort the list pointed to by 'head'
 * return the pointer to the head of the new list
 * DO NOT modify the keys, just manipulate the pointers
 * -----------------------------------------------------------------------------
 */
Node* sort_list(Node* head) 
{
	Node *prevsmall, *prevhead=NULL, *current, *copyofhead=head, *smallest;
	while(copyofhead->next != NULL){
		current=copyofhead;
		smallest=copyofhead;
		while(current->next != NULL){
			if(smallest->key > current->next->key){
				prevsmall= current;
				smallest = current->next;
			}
			current = current->next;
		}
		if(smallest != copyofhead){
			if(prevhead==NULL){
				head = smallest;
			}
			else{
				prevhead->next=smallest;
			}
			prevsmall->next=smallest->next;
			smallest->next=copyofhead;
		}
		prevhead = smallest;
		copyofhead = smallest->next;
	}
    return head; // and don't return NULL unless you have to
}

/**
 * -----------------------------------------------------------------------------
 * given the pointers to the heads of two singly linked lists
 * modify (only the pointers of) the first list so that only the common elements
 * remain. 
 * - return the head pointer to the resulting first list
 * - assume the two input list are already sorted and each of them has no
 *   duplicate key. 
 * - if any of of them is not sorted or has duplicate keys, then throw a
 *   runtime_error() with the appropriate message
 * - do remember to free-up the space of the deleted elements
 * -----------------------------------------------------------------------------
 */
Node* keep_common(Node* head1, Node* head2)
{
	sort_list(head1);
	sort_list(head2);
	remove_duplicates(head1);
	remove_duplicates(head2);
    // YOUR CODE GOES HERE
	Node *prev=head1, *current=head1, *copyofhead2;
	while(prev->next != NULL){
		bool exists = false;
		copyofhead2 = head2;
		while(copyofhead2 != NULL){
			if(copyofhead2->key == current->key){
				exists = true;
			}
			copyofhead2 = copyofhead2->next;
		}
		if(!exists){
			if(prev==current){
				prev = prev->next;
				current->next = NULL;
				current = prev;
				head1 = current;
			}
			else{
				prev->next = current->next;
				current->next = NULL;
				current = prev->next;
			}
		}
		else{
			prev=current;
			current=prev->next;
		}
	}
    return head1;
}


/**
 * -----------------------------------------------------------------------------
 * given the pointer to the head of a singly linked list, remove the duplicate
 * elements and return the pointer to the head of the new list
 * return the head pointer to the resulting list
 * - assumes that the given list (pointed to by head) is sorted in
 *   non-decreasing order
 * - if not, throw a runtime_error exception stating the error
 * -----------------------------------------------------------------------------
 */
Node* remove_duplicates(Node* head)
{
	sort_list(head);
    // YOUR CODE GOES HERE
	Node *next, *prev, *current;
	next = head;
	current = head;
	while(current->next != NULL){
		next=current->next;
		if(current->key==next->key){
			current->next=next->next;
			next->next = NULL;
			
		}
		if(current->next !=NULL){
			prev=current;
			current=current->next;
		}
		else{break;}
		if(prev->key==current->key){
			prev->next=current->next;
			current = prev;
		}
	}
    return head;
}

/**
 * -----------------------------------------------------------------------------
 * merge two sorted lists pointed to by head1 and head2
 * throw runetime_error("Please give me two sorted lists") if any one of them
 * is not already sorted
 * return pointer to the head of the merged list
 * only modify pointers. DONOT modify the key of any node
 * -----------------------------------------------------------------------------
 */
Node* merge_lists(Node* head1, Node* head2) 
{
	sort_list(head1);
	sort_list(head2);
    // YOUR CODE GOES HERE
	Node *prev, *current, *copy=head2, *copyprev=head2;
	while(copyprev != NULL){
		bool exit = false;
		current=head1;
		prev=head1;
		while(!exit){
			if((current == NULL) || (current->key > copy->key)){
				if(prev == current){
					copy = copy->next;
					copyprev->next = current;
					head1 = copyprev;
					copyprev = copy;
					break;
				}
				else{
					copy = copy->next;
					prev->next = copyprev;
					copyprev->next = current;
					copyprev = copy;
					break;
				}
			}
			else{
				prev = current;
				current = current->next;
			}
		}
	}
    return head1; 
}

// *****************************************************************************
// DO NOT MODIFY THIS FILE BEYOND THIS POINT
// *****************************************************************************

/**
 * -----------------------------------------------------------------------------
 * free the memory of all nodes starting from ptr down
 * -----------------------------------------------------------------------------
 */
void free_list(Node* ptr) {
    Node* temp;
    while (ptr != NULL) {
        temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
}
