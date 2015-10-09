//
//  main.cpp
//  Sudoku
//
//  Created by Truc Le on 10/5/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//	Based on Peter Norvig's techniques
//

#include <iostream>	//cin, cout
#include <map>		//map
#include <string.h>	//strcat
#include <algorithm>//remove char from string
#include <stack>	//stack for DFS
#include <time.h>	//clock_t
#include "FileManager.h"

using namespace std;


//===------------------------------===//
// Global variables
vector<string> grid;							//original grid
vector<string> digits;
vector<string> rows;
vector<string> cols;
vector<string> squares;							//all 1x1 Sudoku's squares
vector<vector<string> > unitlist;				//27 possible units (9 columns + 9 rows + 9 3x3 squares)
map<string, vector<vector<string> > > units;	//map each square to its 3 corresponding units
map<string, vector<string> > peers;				//map each square to its 20 corresponding peers




//===------------------------------===//
// Function headers
void printGrid();
vector<string> cross(vector<string> A, vector<string> B);
vector<string> cross(string a, vector<string> B);
vector<string> cross(vector<string> A, string b);
void initGlobalVar();
map<string, string> gridValues(vector<string> gr);

void printValues(pair<bool, map<string, string> > values);



//each returned map has a bool goes with it so that DFS search knows which map is worth searching deeper
pair<bool, map<string, string> > parseGridToValues(vector<string> gr);
pair<bool, map<string, string> > solve(vector<int> grid);

pair<bool, map<string, string> > eliminate(pair<bool, map<string, string> >& values, string square, string digit);
pair<bool, map<string, string> > assign(pair<bool, map<string, string> >& values, string square, string digit);
pair<bool, map<string, string> > DFS(pair<bool, map<string, string> > values); //depth first search



//===------------------------------===//
// Solve Sudoku
//===------------------------------===//
pair<bool, map<string, string> > solve(vector<string> grid) {
	return DFS(parseGridToValues(grid));
}



//===------------------------------===//
// Recursively search for solution
// by trying all leftover possiblities
// from constraint propagation
//===------------------------------===//
struct CompareValuesSize {
	bool operator() (const pair<string, string>& first, const pair<string, string>& second) {
		return get<1>(first).size() < get<1>(second).size();
	}
};


pair<bool, map<string, string> > DFS(pair<bool, map<string, string> > values) {
	
	
	//Return values if solved in constraint propagation
	bool solved = true;
	for (pair<string, string> val : get<1>(values)) {
		if (get<1>(val).size() > 1) {
			solved = false;
			break;
		}
	}
	if (solved) { return values; }
	
	
	
	//DFS search if values is an unsolved valid map
	if (get<0>(values)) {
		
		pair<bool, map<string, string> >* current_map;
		pair<bool, map<string, string> > val = values;
		stack<pair<bool, map<string, string> > > DFS_stack;
		
		DFS_stack.push(val);
		current_map = &DFS_stack.top();
		
		
		while (!DFS_stack.empty()) {
			
			bool solved = true;
			for (pair<string, string> v : get<1>(*current_map)) {
				if (get<1>(v).size() > 1) {
					solved = false;
					break;
				}
			}
			if (solved) {
				cout << endl;
				cout << "------ SOLVED ------" << endl;
				return *current_map;
			}
			
			
			map<string, string> values_copy = get<1>(*current_map);
			DFS_stack.pop();
			
			//find a square with the least possibilities
			vector<pair<string, string> > sorted_values;
			CompareValuesSize compare;
			for (pair<string, string> val : values_copy) {
				sorted_values.push_back(val);
			}
			sort(sorted_values.begin(), sorted_values.end(), compare);
			
			
			//get this square and its possibilities
			string square;
			string possible_digits;
			for (pair<string, string> sVal: sorted_values) {
				if (get<1>(sVal).size() > 1) {
					square = get<0>(sVal);
					possible_digits = get<1>(sVal);
					break;
				}
			}
			
			
			
			
			for (char digit_char : possible_digits) {
				string digit = string(1, digit_char);
				pair<bool, map<string, string> > potential_val(true, values_copy);
				
				//cout << square << ": " << possible_digits << ": " << digit << endl;
				
				assign(potential_val, square, digit);
				
				if (get<0>(potential_val)) {
					DFS_stack.push(potential_val);
				}
				//printValues(DFS_stack.top());
			}
			
			current_map = &DFS_stack.top();
			
			
		}
		
		
	}
	
	return values;
}



//===------------------------------===//
// Print values
//===------------------------------===//
void printValues(pair<bool, map<string, string> > values) {
	
	if (get<0>(values)) {
		map<string, string> val = get<1>(values);
		
		int width = 0;
		for (string sq : squares) {
			if (val.at(sq).size() > width) {
				width = (int) val.at(sq).size();
			}
		}
		++width;
		
		
		map<string, string>::iterator it;
		int c = 1;
		cout << endl;
		for (it = val.begin(); it != val.end(); ++it) {
			cout << it->second;
			
			if ((it->second).size() < width) {
				for (int w = 0; w < width - (it->second).size(); ++w) { cout << " "; }
			}
			
			if (c % 27 == 0 && c % 81 != 0) {
				cout << endl;
				for (int w = 0; w < width * 3; ++w) { cout << "-"; }
				cout << "+";
				for (int w = 0; w < width * 3; ++w) { cout << "-"; }
				cout << "+";
				for (int w = 0; w < width * 3; ++w) { cout << "-"; }
				cout << endl;
			}
			else if (c % 9 == 0) { cout << endl; }
			else if (c % 3 == 0) { cout << "|"; }
			
			++c;
		}
	}
	else {
		cout << "(!) Can't solve Sudoku" << endl;
		exit(1);
	}
}



//===------------------------------===//
// Parse grid into a map that maps each
// square to its possible values
//===------------------------------===//
pair<bool, map<string, string> > parseGridToValues(vector<string> gr) {
	
	map<string, string> values; //map of each square and its possible values
	
	//assign values 1-9 to every square
	for (string sq : squares) {
		values.insert(pair<string, string>(sq, "123456789"));
	}
	
	
	pair<bool ,map<string, string> > val(true, values);
	for (pair<string, string> p : gridValues(gr)) {
		
		//if a square's value isn't 0, assign that value to that square
		if (find(digits.begin(), digits.end(), get<1>(p)) != digits.end()) {
			
			if (get<0>(val)) {
				assign(val, get<0>(p), get<1>(p));
			}
			else {
				//cout << "(!) PARSE GRID TO VALUES ERROR" << endl;
				get<0>(val) = false;
				return val;
			}
		}
	}
	
	return val;
}



//===------------------------------===//
// Map each square to its original value
// taken from the initial puzzle
//===------------------------------===//
map<string, string> gridValues(vector<string> gr) {
	map<string, string> grid_values;
	for (int i = 0; i < gr.size(); ++i) {
		grid_values.insert(pair<string, string>(squares.at(i), gr.at(i)));
	}
	
	return grid_values;
}



//===------------------------------===//
// Eliminate all other values (except d)
// from possible values of square s.
// Return fasle if found contradiction
//===------------------------------===//
pair<bool, map<string, string> > assign(pair<bool, map<string, string> >& values, string square, string digit) {
	
	//Don't reference other_values from values because we want to maintain other_values
	string other_values = get<1>(values).at(square);
	other_values.erase(remove(other_values.begin(), other_values.end(), digit[0]), other_values.end());
	
	
	
	for (int i = 0; i < other_values.size(); ++i) {
		string val(1, other_values.at(i));
		if(get<0>(values)) {
			eliminate(values, square, val);
		}
		else {
			return values;
		}
	}
	
	return values;
}



//===------------------------------===//
// Eliminate a digit from a square's
// string of possible values
//===------------------------------===//
pair<bool, map<string, string> > eliminate(pair<bool, map<string, string> >& values, string square, string digit) {
	string* val = &get<1>(values).at(square); //val is a reference to the values mapped to square
	
	
	if (val->find(digit) == string::npos) { //digit is already eliminated
		return values;
	}
	
	val->erase(remove(val->begin(), val->end(), digit[0]), val->end()); //eliminate digit
	
	
	if (val->size() == 0) {
		get<0>(values) = false; //(!) Error: removed last node
		return values;
	}
	else if (val->size() == 1) { //there's 1 possibility left
		string* assigned_digit = val;
		
		//Check value of square against its PEERS,
		//if square has 1 mapped value (assigned_digit),
		//eliminate assigned_digit from square's peers
		for (string peer : peers.at(square)) {
			if (get<0>(values)) {
				eliminate(values, peer, *assigned_digit);
			}
			else {
				return values;
			}
		}
	}
	
	
	//Check digit against UNITS of square, if there's a unit
	//that was reduced to 1 possibility, put digit there
	for (vector<string> vStr : units.at(square)) {
		vector<string> places_of_d;
		
		
		//find squares that have digit as a possibility
		for (string str : vStr) {
			if (get<1>(values).at(str).find(digit) != string::npos) {
				places_of_d.push_back(str);
			}
		}
		if (places_of_d.size() == 0) {
			get<0>(values) = false; //(!) Error: no place for d
			return values;
		}
		else if (places_of_d.size() == 1) {
			if (get<0>(values)) {
				assign(values, places_of_d.at(0), digit); //assign digit to the only leftover square that can hold digit
			}
			else {
				return values;
			}
		}
	}
	
	
	
	return values;
}



//===------------------------------===//
// Initialize global variables
//===------------------------------===//
void initGlobalVar() {
	digits = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	rows = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
	cols = digits;
	squares = cross(rows, digits);
	
	
	//----------------
	// Unitlist
	for (string c : cols) {
		unitlist.push_back(cross(rows, c));
	}
	for (string r : rows) {
		unitlist.push_back(cross(r, cols));
	}
	
	vector<vector<string> > colGroup = {{"A", "B", "C"}, {"D", "E", "F"}, {"G", "H", "I"}};
	vector<vector<string> > rowGroup = {{"1", "2", "3"}, {"4", "5", "6"}, {"7", "8", "9"}};
	for (vector<string> A : colGroup) {
		for (vector<string> B : rowGroup) {
			unitlist.push_back(cross(A, B));
		}
	}
	
	
	
	for (string sq : squares) {
		vector<vector<string> > corresponding_unitlist;
		vector<string> corresponding_peers;
		
		
		//----------------
		// Units
		for (vector<string> vStr : unitlist) {
			for (string str : vStr) {
				if (sq.compare(str) == 0) {
					corresponding_unitlist.push_back(vStr);
					break;
				}
			}
		}
		pair<string, vector<vector<string> > > unit(sq, corresponding_unitlist);
		units.insert(unit);
		
		
		//----------------
		// Peers
		for (vector<string> vStr : corresponding_unitlist) {
			for (string str : vStr) {
				if (sq.compare(str) != 0 && find(corresponding_peers.begin(), corresponding_peers.end(), str) == corresponding_peers.end()) {
					corresponding_peers.push_back(str);
				}
			}
		}
		pair<string, vector<string> > peer(sq, corresponding_peers);
		peers.insert(peer);
	}
}



//===------------------------------===//
// Concatenate each of the 2 vector<string>'s
// strings to generate Sudoku board
//===------------------------------===//
vector<string> cross(vector<string> A, vector<string> B) {
	vector<string> crossed;
	for (string a : A) {
		for (string b : B) {
			crossed.push_back(a + b);
		}
	}
	return crossed;
}


vector<string> cross(string a, vector<string> B) {
	vector<string> crossed;
	for (string b : B) {
		crossed.push_back(a + b);
	}
	return crossed;
}


vector<string> cross(vector<string> A, string b) {
	vector<string> crossed;
	for (string a : A) {
		crossed.push_back(a + b);
	}
	return crossed;
}



//===------------------------------===//
// Print grid, print values
//===------------------------------===//
void printGrid() {
	cout << endl;
	cout << "----- ORIGINAL -----" << endl;
	cout << endl;
	for (int g = 1; g < grid.size() + 1; ++g) {
		cout << grid.at(g - 1) << " ";
		
		if (g % 27 == 0 && g % 81 != 0) {
			cout << endl;
			cout << "------+------+------" << endl;
		}
		else if (g % 9 == 0) {
			cout << endl;
		}
		else if (g % 3 == 0) {
			cout << "|";
		}
	}
	cout << endl;
	cout << "(searching...)" << endl;
}



//===------------------------------===//
// Main
// /Users/Bamboo/Desktop/Sudo/Sudo/test2.txt
//===------------------------------===//
int main(int argc, const char * argv[]) {
	
	FileManager file = FileManager();
	
	clock_t time = clock();
	grid = file.grid;
	initGlobalVar();
	
	printGrid();
	printValues(solve(grid));
	
	time = clock() - time;
	cout << endl;
	cout << "(" << ( double ) time / CLOCKS_PER_SEC << " seconds)"<< endl;
	cout << endl;
	
	return 0;
}

