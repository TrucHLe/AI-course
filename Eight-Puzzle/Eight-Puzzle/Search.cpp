//
//  Search.cpp
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//


#include <iostream>
#include <string>   // string
#include <fstream>  // ifstream
#include <iostream> // cin, cout
#include "Search.h"
#include "State.h"
#include "Node.h"

using namespace std;



//===----------------------------------------------------------------------===//
// Get file
//===----------------------------------------------------------------------===//
ifstream getFile()
{
    ifstream input_file;
    string file_path;
    
    cout << "---------- Eight-Puzzle Solver ----------" << endl;
    cout << "This program will solve the eight-puzzle problem using either an uninformed or an informed search algorithm." << endl;
    cout << endl;
    cout << "Enter a file path of a text file that contains an eight-puzzle:" << endl;
    cout << "$ ";
    
    
    cin >> file_path;
    input_file.open( file_path );
    
    while ( input_file.fail() )
    {
        cout << "(!) Cannot find " << file_path << ", try again." << endl;
        cout << "$ ";
        cin >> file_path;
        input_file.open( file_path );
    }
    
    return input_file;
}

//
// !Get file
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
// Get current character
//===----------------------------------------------------------------------===//
char getCurrentCharacter( int column_number, string current_line, ifstream& input_file )
{
    if ( column_number <= current_line.size() )
        // Still within current line
        return current_line[ column_number - 1 ];
    
    else if ( input_file )
        // At the end of current line
        // but input is still valid
        return '\n';
    
    else
        // Past end of input
        return char_traits<char>::eof();
}

//
// !Get current character
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
// Advance to the next character
//===----------------------------------------------------------------------===//
void advance( int& column_number, int& line_number, string& current_line, ifstream& input_file )
{
    if ( column_number <= current_line.size() )
        // Still within current line
        ++column_number;
    
    else if ( input_file )
    {
        // At the end of current line,
        // attempt to read another line
        current_line.clear();
        getline( input_file, current_line );
        ++line_number;
        column_number = 1;
    }
    
    else {} // At EOF, do nothing
}

//
// !Advance to the next character
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
// Check and get grid
//===----------------------------------------------------------------------===//
void checkAndGetGrid( ifstream& input_file, int grid[3][3] ) // don't know why grid is automatically pass-by-reference
{
    int line_number;
    int column_number;
    int digit_counter;
    string current_line;
    char current_character;
    
    
    line_number     = 1;
    column_number   = 1;
    digit_counter   = 0;
    
    
    getline( input_file, current_line ); // Set first line to be current line

    
    while ( digit_counter < 9 )
    {
        current_character = getCurrentCharacter( column_number, current_line, input_file );

        
        if ( isalpha( current_character ) )
        {
            cout << "(!) Invalid eight-puzzle." << endl;
            exit( 1 );
        }
        
        else if ( isdigit( current_character ) )
        {
            int grid_row    = line_number - 1;
            int grid_column = digit_counter % 3;
            
            grid[ grid_row ][ grid_column ] = current_character - 48; //-48 to convert from ASCII to int
            
            ++digit_counter;
        }
        
        advance( column_number, line_number, current_line, input_file);
    }
    
    
    cout << endl;
    cout << "-- Puzzle --" << endl;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            cout << grid[i][j] << "     ";
        }
        
        cout << endl;
    }

}

//
// !Check and get grid
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
// Get algorithm number
//===----------------------------------------------------------------------===//
int getAlgorithmNumber()
{
    int algorithm_number;

    
    cout << endl;
    cout << "Search Algorithms:" << endl;
    cout << "   1. Breadth-First Seach" << endl;
    cout << "   2. Depth-First Search" << endl;
    cout << "   3. Iterative Deepening Depth First Search" << endl;
    cout << "   4. Best-First Search" << endl;
    cout << "   5. A* Search" << endl;
    cout << endl;
    cout << "Enter a search algorithm's number:" << endl;
    cout << "$ ";
    
    
    
    while ( !( cin >> algorithm_number ) ) // this calls and checks cin respectively
    {
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        cout << "(!) Invalid algorithm number, try again." << endl;
        cout << "Algorithm Number: ";
    }
    
    while ( algorithm_number < 1 || algorithm_number > 5 )
    {
        cout << "(!) Invalid algorithm number, try again." << endl;
        cout << "Algorithm Number: ";
        cin >> algorithm_number;
    }
    

    return algorithm_number;
    
}

//
// !Get algorithm number
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
// Main
//===----------------------------------------------------------------------===//
int main(int argc, const char * argv[])
{
    
    //--------------------------------------------------
    // User Input
    //
    ifstream input_file;
    int algorithm_number;
    int DFS_depth;
    int grid[3][3];
    
    input_file = getFile();
    
    checkAndGetGrid( input_file, grid );
    

    
    
    algorithm_number = getAlgorithmNumber();
    
    if ( algorithm_number == 2 )
    {
        cout << "Depth limit for Depth-First Search: ";
        cin >> DFS_depth;
    }
    

    //
    // !User Input
    //--------------------------------------------------




    
    

    
    
    
    
    
    return 0;
    
    
    
    /*
     // Construction: Make sure user enters a digit w/o delay glitch
     while ( !( cin >> algorithmNum ) )
     {
     cin.clear();
     cin.ignore( numeric_limits<streamsize>::max(), '\n' );
     cout << "(!) Invalid algorithm number, try again." << endl;
     cout << "Algorithm Number: ";
     }
     //! Construction
     */
}