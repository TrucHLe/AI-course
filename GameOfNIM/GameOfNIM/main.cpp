//
//  main.cpp
//  GameOfNIM
//
//  Created by Truc Le on 9/2/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include <iostream>
#include <array>        // array
#include <iomanip>      // setw
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

using namespace std;



//-------------------------------------------
// Print instruction
//
void printInstruction( array<int, 3> valid_moves )
{
    cout << "---------- Game of NIM ----------" << endl;
    cout << "Instruction: You can take ";
    
    for ( int i = 0; i < valid_moves.size(); ++i )
    {
        if ( i < valid_moves.size() - 1 )
            cout << valid_moves[i] << ", ";
        else
            cout << "or " << valid_moves[i] << " sticks from pile in each turn." << endl;
    }
    
    cout << endl;
    cout << setw(15) << left << "PILE" << setw(5) << "MOVES" << endl;
    
}



//-------------------------------------------
// Return the number of sticks that computer takes
//
int computeMove( int available_sticks, array<int, 3> valid_moves )
{
    
    // ----- Winning Strategy for Static NIM (1-pile Game of NIM) -----
    //
    // - Divide the number of sticks available by the
    //      sum of the maximum sticks that a player
    //      can take (which is 3 + 1 = 4 in this case).
    // - The remainder is the number of sticks that
    //      the first player (which is the computer)
    //      should take.
    // - If the remainder is 0, the first player has
    //      no way to win unless the second player
    //      makes a mistake. Hence, let computer take
    //      a random number of sticks in this case.
    //
    
    
    
    bool debugging = false;
    int max_sticks = valid_moves[ valid_moves.size()-1 ];
    int remainder = available_sticks % ( max_sticks + 1 );
    int sticks_computer_takes;
    
    
    
    if ( debugging )
    {
        cout << "Max Sticks         = " << max_sticks << endl;
        cout << "Available Sticks   = " << available_sticks << endl;
        cout << "Remainder          = " << remainder << endl;
    } // !debugging:
    
    
    
    if ( remainder != 0 )
        sticks_computer_takes = remainder;
    else
    {
        // Find the index of the max valid move.
        // Use that index to set range of valid
        // moves that computer can take.
        //
        int max_moves_index = 0;
        for ( int i = 0; i < valid_moves.size(); ++i )
        {
            if ( valid_moves[i] <= available_sticks )
            {
                if ( ( i == valid_moves.size() - 1 ) || ( available_sticks == valid_moves[i] ) )
                {
                    max_moves_index = i;
                    break;
                }
                
                continue;
            }
            
            else if ( i != 0 )
            {
                max_moves_index = i - 1;
                break;
            }
        }
        
        
        
        if ( debugging )
        {
            cout << "Valid moves range  = ";
            
            for ( int j = 0; j < max_moves_index + 1; ++j )
                cout << valid_moves[j] << " ";
            
            cout << endl;
        } // !debugging
        
        
        
        if ( max_moves_index != 0 )
            sticks_computer_takes = valid_moves[ rand() % max_moves_index ];
        else
            sticks_computer_takes = valid_moves[0];
        
    }
    
    
    
    return sticks_computer_takes;
}



//-------------------------------------------
// Validify the number of sticks that user takes
//
int validifyMove( int available_sticks, array<int, 3> valid_moves, int sticks_user_takes )
{
    while ( ( find( begin(valid_moves), end(valid_moves), sticks_user_takes ) == end(valid_moves) )
            || ( sticks_user_takes > available_sticks ) )
    {
        cout << endl;
        cout << "(!) Invalid move, try again" << endl;
        cout << setw(15) << left << available_sticks << setw(5) << "I take ";
        cin >> sticks_user_takes;
    }
    
    
    
    return sticks_user_takes;
}


//-------------------------------------------
// Main
//
int main(int argc, const char * argv[])
{
    
    srand( time( NULL ) );
    int available_sticks = 10; //rand() % 10 + 1; // random available sticks range [1-10]
    int sticks_computer_takes;
    int sticks_user_takes = 0;
    array<int, 3> valid_moves { 1, 2, 3 };
    
    
    
    printInstruction( valid_moves );
    
    
    
    while ( available_sticks > 0 )
    {
        
        sticks_computer_takes = computeMove( available_sticks, valid_moves );
        
        cout << setw(15) << left << available_sticks << setw(5) << "Mac takes " << sticks_computer_takes << endl;
        available_sticks -= sticks_computer_takes;
        
        
        if ( available_sticks == 0 )
        {
            cout << "---------- Mac wins!   ----------" << endl;
            return 0;
        }
        
        
        //-------------------------------------------
        
        
        cout << setw(15) << left << available_sticks << setw(5) << "I take ";
        cin >> sticks_user_takes;
        
        sticks_user_takes = validifyMove( available_sticks, valid_moves, sticks_user_takes );
        available_sticks -= sticks_user_takes;
        
        
        if ( available_sticks == 0 )
        {
            cout << "---------- You win!    ----------" << endl;
            return 0;
        }
        
    }
    
    
    
    return 0;
}
