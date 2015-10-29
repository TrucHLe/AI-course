//
//  FileManager.h
//  ReinforcementLearningNIM
//
//  Created by Truc Le on 10/28/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef __ReinforcementLearningNIM__FileManager__
#define __ReinforcementLearningNIM__FileManager__

#include <iostream> //cin, cout
#include <fstream>  //ifstream
#include <vector>	//vector
#include <array>	//array
#include <string>	//string
#include <limits>	//numeric_limits
#include "Constants.h"

using namespace std;

class FileManager {
	
private:
	ifstream input;
	int line_number;
	int column_number;
	string current_line;
	string current_lexeme;
	vector<int> input_data;
	
	
public:
	FileManager();
	array<array<int, 10>, 3> learned_moves;
	
	ifstream getFile();
	char getCurrentChar();
	void advance();
	int getNextState( int currentState, char currentChar );
	int getTerminalState();
	int next();
	
	void getLearnedMoves();
	void updateLearnedMoves(array<array<int, 10>, 3> updatedMoves); //finish later
	
};


#endif /* defined(__ReinforcementLearningNIM__FileManager__) */
