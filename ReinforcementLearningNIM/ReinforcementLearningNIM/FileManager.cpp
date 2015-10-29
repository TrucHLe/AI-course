//
//  FileManager.cpp
//  ReinforcementLearningNIM
//
//  Created by Truc Le on 10/28/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "FileManager.h"


//===------------------------------===//
// Constructor
//===------------------------------===//
FileManager::FileManager()
{
	input			= getFile();
	line_number		= 1;
	column_number	= 1;
	getline(input, current_line);
	getLearnedMoves();
}



//===------------------------------===//
// Get file
//===------------------------------===//
ifstream FileManager::getFile()
{
	ifstream file;
	//file.open("learned-moves.txt");
	file.open("/Users/Bamboo/Developer/AI-course/ReinforcementLearningNIM/ReinforcementLearningNIM/learned-moves.txt");
	
	while (file.fail())
	{
		string file_path;
		
		cout << "(!) Cannot find learned-moves.txt that contains the learned data." << endl;
		cout << "Please enter a file to use as learned data: ";
		cin >> file_path;
		
		file.open(file_path);
	}
	
	return file;
}



//===------------------------------===//
// Get current character
//===------------------------------===//
char FileManager::getCurrentChar()
{
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
void FileManager::advance()
{
	
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
// Get next state
//===------------------------------===//
int FileManager::getNextState( int currentState, char currentChar )
{
	int column;
	int state_transition_table[3][6] = {
	//	0		1		2		3		4		5
	//	-		D		CR		WS		EOF		OTHER
		1,		2,		0,		0,		102,	401,
		400,	1,		100,	100,	100,	100,
		101,	2,		101,	101,	101,	101
	};
	
	if (currentChar == '-')
		column = 0;
	else if (isdigit(currentChar))
		column = 1;
	else if (currentChar == '\n')
		column = 2;
	else if (isspace(currentChar))
		column = 3;
	else if (currentChar == EOF)
		column = 4;
	else
		column = 5;
	
	
	return state_transition_table[currentState][column];
}



//===------------------------------===//
// Get terminal state
//===------------------------------===//
int FileManager::getTerminalState()
{
	int current_state = 0;
	char current_char;
	
	do
	{
		current_char = getCurrentChar();
		current_lexeme = current_lexeme + current_char;
		
		
		// Erase all whitespaces if the whitespace
		// is the only thing in current lexeme
		if ( isspace( current_char ) )
			if ( current_lexeme.length() == 1 )
				current_lexeme.erase( current_lexeme.length() - 1, 1 );
				
		
		current_state = getNextState(current_state, current_char);
		advance();
		
		switch (current_state)
		{
			case NEG_INT:		return current_state;
			case POS_INT:		return current_state;
			case EOF_T:			return current_state;
			case INT_ERROR:		return current_state;
			case CHAR_ERROR:	return current_state;
		}
		
	} while (1);
}



//===------------------------------===//
// Get next string from input
//===------------------------------===//
int FileManager::next()
{
	int state = getTerminalState();
	int result;
	
	switch (state)
	{
		case NEG_INT:
			if (column_number > 1)
				--column_number;
			
			current_lexeme.erase(0, 1); //erase the negative mark
			current_lexeme.erase(current_lexeme.length() - 1, 1); //erase the lookahead
			result = -stoi(current_lexeme);
			current_lexeme = "";
			return result;
		
		case POS_INT:
			if (column_number > 1)
				--column_number;
			
			current_lexeme.erase(current_lexeme.length() - 1, 1);
			result = stoi(current_lexeme);
			current_lexeme = "";
			return result;
			
		case EOF_T:
			current_lexeme = "";
			return -987654321;
			
		case INT_ERROR:
			cout << "(!) Expected an integer after '-'" << endl;
			exit(1);
			
		case CHAR_ERROR:
			cout << "(!) Found invalid character" << endl;
			exit(1);
			
			
		// switch statement is exhaustive
		// This line is just to make Xcode happy.
		default:
			return -987654321;
	}
}



//===------------------------------===//
// Parse learned-moves.txt to a 2D array
//===------------------------------===//
void FileManager::getLearnedMoves()
{
	int token;
	int row = 0;
	int column = 0;
	int counter = 0;
	
	do
	{
		token = next();
		input_data.push_back(token);
		
		++counter;
		++column;
		
		if (column == 9)
		{
			column = 0;
			++row;
		}
		
	} while (counter < 30 || token % -987654321 != 0);
	
	
	if (counter < 30)
	{
		cout << "(!) Insufficient learned data" << endl;
		exit(1);
	}
	
	
	counter = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			learned_moves[i][j] = input_data.at(counter);
			++counter;
		}
	}
	
	
}