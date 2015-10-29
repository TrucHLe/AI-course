//
//  main.cpp
//  ReinforcementLearningNIM
//
//  Created by Truc Le on 10/28/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include <iostream>
#include <fstream>		// fstream
#include <array>        // array
#include <iomanip>      // setw
#include "FileManager.h"

using namespace std;


void updateLearnedMoves();


//===----------------------------------------------------------------------===//
// Print instruction
//===----------------------------------------------------------------------===//
void printInstruction()
{
	cout << "---------- Game of NIM ----------" << endl;
	cout << "Instruction: You can take 1, 2, or 3 sticks from the pile in each turn." << endl;
	cout << setw(15) << left << "PILE" << setw(5) << "MOVES" << endl;
}



//===----------------------------------------------------------------------===//
// Check and return user's move
//===----------------------------------------------------------------------===//
int checkUsersMove( int sticks_user_takes, int available_sticks )
{
	while ( sticks_user_takes > 4 || sticks_user_takes < 1 || sticks_user_takes > available_sticks )
	{
		cout << endl;
		cout << "(!) Invalid move, try again" << endl;
		cout << setw(15) << left << available_sticks << setw(5) << "I take ";
		cin >> sticks_user_takes;
	}
	
	return sticks_user_takes;
}



//===----------------------------------------------------------------------===//
// Main
//===----------------------------------------------------------------------===//
int main(int argc, const char * argv[])
{
	printInstruction();
	FileManager file;
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			cout << file.learned_moves[i][j] << " ";
		}
		cout << endl;
	}
	
	
	int available_sticks = 10;
	int sticks_computer_takes;
	int sticks_user_takes = 0;


	
    return 0;
}



