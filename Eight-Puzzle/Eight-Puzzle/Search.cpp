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
#include "FileManager.cpp"
#include "Search.h"
#include "State.h"
#include "Node.h"

using namespace std;


//===----------------------------------------------------------------------===//
// Main
//
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

    
    State state( grid );
    Node node( state, NULL) ;

    
    return 0;

}

//
// !Main
//===---------------------------------------===//