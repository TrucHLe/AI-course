//
//  FileManager.cpp
//  Eight-Puzzle
//
//  Created by Truc Le on 9/16/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "FileManager.h"



//===----------------------------------------------------------------------===//
// Constructor
//
FileManager::FileManager()
{
    input_file = getFile();
    checkAndGetGrid();
    getAlgorithmNumber();
    
}

//
// !Constructor
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Get file
//
ifstream FileManager::getFile()
{
    ifstream file;
    string file_path;
    
    cout << "---------- Eight-Puzzle Solver ----------" << endl;
    cout << "This program will solve the eight-puzzle problem using either an uninformed or an informed search algorithm." << endl;
    cout << endl;
    cout << "Enter a file path of a text file that contains an eight-puzzle:" << endl;
    cout << "$ ";
    
    
    cin >> file_path;
    file.open( file_path );
    
    while ( file.fail() )
    {
        cout << "(!) Cannot find " << file_path << ", try again." << endl;
        cout << "$ ";
        cin >> file_path;
        file.open( file_path );
    }
    
    return file;
}

//
// !Get file
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Get current character
//
char FileManager::getCurrentCharacter()
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
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Advance to the next character
//
void FileManager::advance()
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
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Check and get grid
//
void FileManager::checkAndGetGrid() // don't know why grid is automatically pass-by-reference
{
    int digit_counter;
    char current_character;
    
    
    line_number     = 1;
    column_number   = 1;
    digit_counter   = 0;
    
    
    getline( input_file, current_line ); // Set first line to be current line
    
    while ( digit_counter < 9 )
    {
        current_character = getCurrentCharacter();

        
        if ( isalpha( current_character ) || line_number > 3 )
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
        
        advance();

    }
    
    
    cout << endl;
    cout << "Puzzle" << endl;
    
    for ( int i : { 0, 1, 2 } ) // Use loops since C++ arrays aren't assignable
    {
        for ( int j : { 0, 1, 2 } )
            cout << grid[i][j] << " ";
        
        cout << endl;
    }
    
}

//
// !Check and get grid
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Get algorithm number
//
void FileManager::getAlgorithmNumber()
{
    cout << endl;
    cout << "Search Algorithms:" << endl;
    cout << "   1. Breadth-First Seach" << endl;
    cout << "   2. Depth-First Search" << endl;
    cout << "   3. Iterative Deepening Depth First Search" << endl;
    cout << "   4. Best-First Search" << endl;
    cout << "   5. A* Search" << endl;
    cout << "   6. Run all search algorithms" << endl;
    cout << endl;
    cout << "Enter a search algorithm's number:" << endl;
    cout << "$ ";
    
    
    
    while ( !( cin >> algorithm_number ) ) // this calls and checks cin whether input is not a digit, respectively
    {
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        cout << "(!) Invalid algorithm number, try again." << endl;
        cout << "Algorithm Number: ";
    }
    
    while ( algorithm_number < 1 || algorithm_number > 6 )
    {
        cout << "(!) Invalid algorithm number, try again." << endl;
        cout << "Algorithm Number: ";
        cin >> algorithm_number;
    }
    
    
    if ( algorithm_number == 2 )
    {
        cout << "Depth limit for Depth-First Search: ";
        cin >> DFS_depth;
    }
    else
        DFS_depth = 0;
    
}

//
// !Get algorithm number
//===---------------------------------------===//