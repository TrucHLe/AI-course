//
//  main.cpp
//  Sudoku
//
//  Created by Truc Le on 10/5/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include <iostream>	//cin, cout
#include <map>		//map
#include <string.h>	//strcat
#include <algorithm>//remove char from string
#include "FileManager.h"

using namespace std;


//===------------------------------===//
// Global variables
vector<string> grid;							//original Sudoku grid
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
map<string, string> eliminate(map<string, string> &values, string square, string digit);
map<string, string> assign(map<string, string> &values, string square, string digit);
map<string, string> gridValues(vector<string> gr);
map<string, string> parseGridToValues(vector<string> gr);
void printValues(map<string, string> values);




//===------------------------------===//
// Print values
//===------------------------------===//
void printValues(map<string, string> values) {
	
	int width = 0;
	for (string sq : squares) {
		if (values.at(sq).size() > width) {
			width = (int) values.at(sq).size();
		}
	}
	++width;
	
	
	map<string, string>::iterator it;
	int c = 1;
	cout << endl;
	for (it = values.begin(); it != values.end(); ++it) {
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
		else if (c % 9 == 0) {
			cout << endl;
		}
		else if (c % 3 == 0) {
			cout << "|";
		}
		
		++c;
	}
}



//===------------------------------===//
// Parse grid into map of each square
// and its possible values
//===------------------------------===//
map<string, string> parseGridToValues(vector<string> gr) {

	map<string, string> values;
	
	//assign values 1-9 to every square
	for (string sq : squares) {
		values.insert(pair<string, string>(sq, "123456789"));
	}
	
	
	for (pair<string, string> p : gridValues(gr)) {
		if (find(digits.begin(), digits.end(), get<1>(p)) != digits.end()) {
			assign(values, get<0>(p), get<1>(p));
		}
	}
	
	return values;
}



//===------------------------------===//
// Map each square to its original value
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
map<string, string> assign(map<string, string> &values, string s, string d) {
	
	string other_values = values.at(s);
	other_values.erase(remove(other_values.begin(), other_values.end(), d[0]), other_values.end());
	
	
	for (int i = 0; i < other_values.size(); ++i) {
		string val(1, other_values.at(i));
		eliminate(values, s, val);
	}

	return values;
}



//===------------------------------===//
// Eliminate a digit from a square's
// string of possible values
//===------------------------------===//
map<string, string> eliminate(map<string, string> &values, string s, string d) {
	string* val = &values.at(s);
	
	
	if (val->find(d) == string::npos) { //d is already eliminated
		return values;
	}

	
	
	val->erase(remove(val->begin(), val->end(), d[0]), val->end());
	
	if (val->size() == 0) {
		cout << "(!) A Sudoku square cannot be assigned any value" << endl;
		exit(1); //error, we removed the last node
	}
	else if (val->size() == 1) {
		string* d1 = val;
		
		//Check value of s against its PEERS,
		//if s has 1 mapped value (d1),
		//eliminate d1 from its peers
		for (string p : peers.at(s)) {
			
			eliminate(values, p, *d1);
		}
	}
	
		
	//Check the above eliminated value d
	//against UNITS of s, if there's a unit
	//that was reduced to 1 possibility, put d there
	for (vector<string> vStr : units.at(s)) {
		vector<string> places_of_d;
		
		
		//find squares that have d as a possibility
		for (string str : vStr) {
			if (values.at(str).find(d) != string::npos) {
				places_of_d.push_back(str);
			}
		}
		if (places_of_d.size() == 0) {
			cout << "(!) Cannot assign computed value to Sudoku" << endl;
			exit(1); //error, no square can hold d
		}
		else if (places_of_d.size() == 1) {
			assign(values, places_of_d.at(0), d); //assign d to the only square left that can hold d
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
// Concatenate each of 2 vectors' elements
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
}



//===------------------------------===//
// Main
// /Users/Bamboo/Developer/AI-course/Sudoku/Sudoku/easy.txt
//===------------------------------===//
int main(int argc, const char * argv[]) {

	FileManager file = FileManager();
	grid = file.grid;
	initGlobalVar();
	
	printGrid();
	printValues(parseGridToValues(grid));

	
	
	
	

	
    return 0;
}

