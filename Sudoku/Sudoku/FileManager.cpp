//
//  FileManager.cpp
//  Sudoku
//
//  Created by Truc Le on 10/5/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "FileManager.h"



//===------------------------------===//
// Constructor
// Let FileManager, not main.cpp, owns
// the file because need to print msg
// prompting user to enter filename
// before reading file
//===------------------------------===//
FileManager::FileManager() {
    input = getFile();
    getGrid();
}



//===------------------------------===//
// Get file
//===------------------------------===//
ifstream FileManager::getFile() {
	
    ifstream file;
    string file_path;
    
    cout << "---------- Sudoku ----------" << endl;
    cout << "Enter a relative file path of a Sudoku puzzle text file: ";
    
    
    cin >> file_path;
    file.open( file_path );
    
    while ( file.fail() )
    {
        cout << "(!) Cannot find " << file_path << ", try again: ";
        cin >> file_path;
        file.open( file_path );
    }
    
    return file;
}



//===------------------------------===//
// Get current character
//===------------------------------===//
char FileManager::getCurrentChar() {
    
    if (column_number <= current_line.size()) {
		return current_line[column_number-1];
    }
    else if (input) { //at the end of current line
        return '\n';
    }
    else {
        return char_traits<char>::eof();
    }
}



//===------------------------------===//
// Advance to next character
//===------------------------------===//
void FileManager::advance() {
	
    if (column_number <= current_line.size()) {
        ++column_number;
    }
    else if (input) { //at the end of current line, attempt to read next line
        current_line.clear();
        getline(input, current_line);
        ++line_number;
        column_number = 1;
    }
    else {}
}



//===------------------------------===//
// Parse file's digits to array of int
//===------------------------------===//
void FileManager::getGrid() {
	
    int digit_counter   = 0;
    line_number         = 1;
    column_number       = 1;
    getline(input, current_line);
	
	
    while (getCurrentChar() != EOF) {
		
		if (digit_counter == 81) {
			break;
		}
		else if (isalpha(getCurrentChar())) {
			cout << "(!) Sudoku shouldn't contain alphabetic character" << endl;
			exit(1);
		}
		else if (isdigit(getCurrentChar())) {
			grid.push_back(string(1, getCurrentChar()));
			++digit_counter;
		}
		
		advance();
    }
}