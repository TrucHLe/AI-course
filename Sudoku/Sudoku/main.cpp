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
#include <algorithm>//find
#include "FileManager.h"

using namespace std;


vector<int> sudoku;
vector<string> digits;
vector<string> rows;
vector<string> cols;
vector<string> squares;							//each square of the sudoku
vector<vector<string> > unitlist;				//all possible units
map<string, vector<vector<string> > > units;	//map each square to its units
map<string, vector<string> > peers;				//map each square to its peers





//===------------------------------===//
// Print sudoku
//===------------------------------===//
void print() {
	cout << endl;
	for (int s = 1; s < sudoku.size() + 1; ++s) {
		cout << sudoku.at(s - 1) << " ";
		
		if (s % 27 == 0 && s % 81 != 0) {
			cout << endl;
			cout << "------+------+------" << endl;
		}
		else if (s % 9 == 0) {
			cout << endl;
		}
		else if (s % 3 == 0) {
			cout << "|";
		}
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
	
	
	
	for (string s : squares) {
		vector<vector<string> > corresponding_unitlist;
		vector<string> corresponding_peers;
		
		
		//----------------
		// Units
		for (vector<string> vStr : unitlist) {
			for (string str : vStr) {
				if (s.compare(str) == 0) {
					corresponding_unitlist.push_back(vStr);
					break;
				}
			}
		}
		pair<string, vector<vector<string> > > unit(s, corresponding_unitlist);
		units.insert(unit);
		
		
		//----------------
		// Peers
		for (vector<string> vStr : corresponding_unitlist) {
			for (string str : vStr) {
				if (s.compare(str) != 0 && find(corresponding_peers.begin(), corresponding_peers.end(), str) == corresponding_peers.end()) {
					corresponding_peers.push_back(str);
				}
			}
		}
		pair<string, vector<string> > peer(s, corresponding_peers);
		peers.insert(peer);
	}
}





//===------------------------------===//
// Main
// /Users/Bamboo/Developer/AI-course/Sudoku/Sudoku/easy.txt
//===------------------------------===//
int main(int argc, const char * argv[]) {

	FileManager file = FileManager();
	sudoku = file.sudoku;
	initGlobalVar();
	print();


	
	
	
	

	
    return 0;
}

