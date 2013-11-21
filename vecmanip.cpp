// ============================================================================ 
// vecmanip.cpp
// ~~~~~~~~~~~~~
//Sean Frischmann
// implement the missing functions
// ============================================================================ 

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <queue>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "Lexer.h"
#include "term_control.h"

using namespace std; // BAD PRACTICE

extern const string usage_msg = "Vector Manipulation Toy. Version 0.1\n"
                                "Author: Sean Frischmann\n"
                                "Report bugs to seanfris@buffalo.edu";

/*
 * This method checks to see if file can be openned.
 *
 * Arguments: String fileName
 * Return: bool
 */
bool canOpenFile(const string& x){
	ifstream ifs;
	ifs.open(x.c_str());
	bool open = !ifs.fail();
	ifs.close();
	return open;
}

/*
 * This method stores content from a file into a vector.
 *
 * Arguments: const string$ fileName
 * Return: vector<string>
 */
vector< vector<Token> > storeContent(const string& x){
	Lexer lexer;
	vector< vector<Token> > contents;
	string line;
	ifstream ifs;
	ifs.open(x.c_str());
	while(getline(ifs, line)){
		lexer.set_input(line);
		contents.push_back(lexer.tokenize());
	}
	ifs.close();
	return contents;
}
/**
 * -----------------------------------------------------------------------------
 * This method Loads the file we are going to be manipulating and does the
 * following:
 *  -opens file and tokenizes the contents
 *  -converts tokens into integers and sorts them
 *  -returns a vector of vectors containg the integers
 * -----------------------------------------------------------------------------
 */
vector< vector<int> > loaddb(const vector<Token>& tok_vec){
	vector< vector<Token> > contents;
	vector< vector<int> > ret;
	string line;
	for(size_t i=0;i<tok_vec.size();i++){
		line += tok_vec.at(i).value;
	}
	cout << "Loading File: " << line << endl;
	if(canOpenFile(line)){
		contents = storeContent(line);
		for(size_t i=0;i<contents.size();i++){
			vector<int> intVec;
			for(size_t j=0;j<contents.at(i).size();j++){
				intVec.push_back(atoi(contents.at(i).at(j).value.c_str()));
			}
			sort(intVec.begin(), intVec.end());
			ret.push_back(intVec);
		}
		return ret;
	}else{
		cerr << "Cannot Open File" << endl;
		return ret;
	}
}

/**
 * -----------------------------------------------------------------------------
 * This method finds the common numbers in each vector and either prints it to
 * the console or stores the output in a file.
 * -----------------------------------------------------------------------------
 */
void slow_intersect(const vector< vector<int> >& contents, bool outputfile){
	string output;
	if(contents.size() > 1){
		for(size_t i=0; i<contents.at(0).size(); i++){
			int number_to_compare=contents.at(0).at(i);
			size_t counter=1;
			for(size_t j=1; j<contents.size(); j++){
				bool occurs = false;
				for(size_t k=0; k<contents.at(j).size(); k++){
					if(contents.at(j).at(k) == number_to_compare){
						occurs = true;
						break;
					}
				}
				if(occurs){
					counter++;
				}
			}
			if(counter == contents.size()){
				ostringstream ostr;
				ostr << number_to_compare;
				output += ostr.str();
				output += " ";
			}
		}
		if(outputfile){
			cout << "Saved output to: " << "slow_intersect_outputfile.txt" << endl;
			ofstream myfile;
			myfile.open("slow_intersect_outputfile.txt");
			if(output == ""){
				myfile << "There are no intersections";
			}else{
				myfile << output;
			}
			myfile.close();
		}else{
			if(output == ""){
				cout << "There are no intersections" << endl;
			}else{
				cout << output << endl;
			}
		}
	}else{
		cerr << "There is only one line, therefore nothing to intersect" << endl;
	}
}

/**
 * -----------------------------------------------------------------------------
 * This method combines all the contents of the vector into one line and either
 * prints it in the console or writes it to a file.
 * -----------------------------------------------------------------------------
 */
void slow_union(const vector< vector<int> >& contents, bool outputfile){
	string output;
	vector<int> output_vec;
	int last;
	for(size_t i=0; i<contents.size(); i++){
		for(size_t j=0; j<contents.at(i).size(); j++){
			output_vec.push_back(contents.at(i).at(j));
		}
	}
	sort(output_vec.begin(), output_vec.end());
	ostringstream ostr;
	ostr << output_vec.at(0);
	output += ostr.str();
	output += " ";
	last = output_vec.at(0);
	for(size_t i=1; i<output_vec.size(); i++){
		if(last != output_vec.at(i)){
			ostringstream ostr1;
			ostr1 << output_vec.at(i);
			output += ostr1.str();
			output += " ";
		}
		last = output_vec.at(i);
	}
	if(outputfile){
		cout << "Saved output to: " << "slow_union_outputfile.txt" << endl;
		ofstream myfile;
		myfile.open("slow_union_outputfile.txt");
		myfile << output;
		myfile.close();
	}else{
		cout << output << endl;
	}

}

/**
 * -----------------------------------------------------------------------------
 * This method finds the numbers common in all the vector in a faster approach
 * than the above method.
 * -----------------------------------------------------------------------------
 */
size_t binary_search(const vector<int>& sorted_vec, const int& key){
	size_t mid, left=0;
	size_t right=sorted_vec.size()-1;
	while(left<right){
		mid=left + (right - left) / 2;
		if(mid > sorted_vec.size()){
			return sorted_vec.size()+1;
		}
		if(sorted_vec.at(mid) < key){
			left = mid +1;
		}
		if(sorted_vec.at(mid) > key){
			right = mid-1;
		}
		if(sorted_vec.at(mid) == key){
			return mid;
		}
	}
	return left;
}

void fast_intersect(const vector< vector<int> >& contents, bool outputfile){
	string output;
	size_t current_index=0;
	vector<size_t> index;
	for(size_t i=0; i<contents.size(); i++){
		index.push_back(contents.at(i).size());
	}
	size_t current_set=0;
	int current_element=contents.at(current_set).at(current_index);
	int max_in_others=current_element;
	int max_set;
	bool end_search = false;
	while(current_index < index.at(current_set)){
		size_t number_found = 0;
		for(size_t i=0; i < contents.size(); i++){
			if(i != current_set){
				size_t value = binary_search(contents.at(i), current_element);
				if((value >= index.at(i)) || (current_index >= index.at(i))){
					end_search = true;
					break;
				}
				if(contents.at(i).at(value) != current_element){
					if(contents.at(i).at(value) >= max_in_others){
						max_in_others = contents.at(i).at(value);
						max_set = i;
					}
				}else{
					number_found++;
					max_in_others = current_element;
				}
			}
		}
		if(end_search){
			break;
		}
		if((max_in_others == current_element) || (number_found == contents.size()-1)){
			ostringstream ostr;
			ostr << current_element;
			output += ostr.str();
			output += " ";
			current_index++;
			if(current_index >= index.at(current_set)){
				break;
			}
			current_element = contents.at(current_set).at(current_index);
		}else{
			current_element = max_in_others;
			current_set = max_set;
			current_index++;
		}
	}
	if(outputfile){
		cout << "Saved output to: " << "fast_intersect_outputfile.txt" << endl;
		ofstream myfile;
		myfile.open("fast_intersect_outputfile.txt");
		if(output == ""){
			myfile << "There are no intersections";
		}else{
			myfile << output;
		}
		myfile.close();
	}else{
		if(output == ""){
			cout << "There are no intersections" << endl;
		}else{
			cout << output << endl;
		}
	}
}

/**
 * -----------------------------------------------------------------------------
 * In this method we are combining the elements from all the vectors faster than
 * in slow_union above.
 * -----------------------------------------------------------------------------
 */

void fast_union(const vector< vector<int> >& contents, bool outputfile){
	priority_queue<int, vector<int>, greater<int> > output_queue;
	int last;
	for(size_t i=0; i<contents.size(); i++){
		for(size_t j=0; j<contents.at(i).size(); j++){
			output_queue.push(contents.at(i).at(j));
		}
	}
	if(outputfile){
		cout << "Saved output to: " << "fast_union_outputfile.txt" << endl;
		ofstream myfile;
		myfile.open("fast_union_outputfile.txt");
		myfile << output_queue.top();
		last = output_queue.top();
		output_queue.pop();
		while(!output_queue.empty()){
			if(output_queue.top() == last){
				output_queue.pop();
			}else{
				myfile << " " << output_queue.top();
				last = output_queue.top();
				output_queue.pop();
			}
		}
		myfile.close();
	}else{
		cout << output_queue.top();
		last = output_queue.top();
		output_queue.pop();
		while(!output_queue.empty()){
			if(output_queue.top() == last){
				output_queue.pop();
			}else{
				cout << " " << output_queue.top();
				last = output_queue.top();
				output_queue.pop();
			}
		}
		cout << endl;
	}
}
