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
#include "Move.h"

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
int checkUsersMove(int user_take, int sticks)
{
	while ( user_take > 4 || user_take < 1 || user_take > sticks )
	{
		cout << endl;
		cout << "(!) Invalid move, try again" << endl;
		cout << setw(15) << left << sticks << setw(5) << "I take ";
		cin >> user_take;
	}
	
	return user_take;
}



//===----------------------------------------------------------------------===//
// Play game :)
//===----------------------------------------------------------------------===//
void play()
{
	FileManager file;
	array<array<int, 10>, 3> learned_moves = file.learned_moves;
	vector<Move> moves;
	
	int sticks = 10;
	int computer_take;
	int user_take = 0;
	
	while (sticks > 0)
	{
		// Check for a cell with highest reward
		// and assign that cell's move + 1 (which is
		// also its row index) to computer
		int highest_reward = 2;
		for (int i = 0; i < 3; ++i)
			if (learned_moves[i][sticks - 1] > learned_moves[highest_reward][sticks - 1])
				highest_reward = i;
		
		computer_take = highest_reward + 1;
		Move move = Move(highest_reward, sticks - 1);
		moves.push_back(move);
		

		
		cout << setw(15) << left << sticks << setw(5) << "Mac takes " << computer_take << endl;
		sticks -= computer_take;

		
		if (sticks == 0)
		{
			for (Move m : moves)
				learned_moves[m.row][m.column] += 1;
			
			file.updateLearnedMoves(learned_moves);
			
			cout << "---------- Mac wins!   ----------" << endl;
			break;
		}
		
		
		
		//-------------------------------------------
		
		
		
		cout << setw(15) << left << sticks << setw(5) << "I take ";
		cin >> user_take;
		
		user_take = checkUsersMove(user_take, sticks);
		sticks -= user_take;
		
		
		if (sticks == 0)
		{
			for (Move m : moves)
				learned_moves[m.row][m.column] -= 1;
			
			file.updateLearnedMoves(learned_moves);
			
			cout << "---------- You win!    ----------" << endl;
			break;
		}
	
	}
}



//===----------------------------------------------------------------------===//
// Main
//===----------------------------------------------------------------------===//
int main(int argc, const char * argv[])
{
	printInstruction();
	play();

    return 0;
}



