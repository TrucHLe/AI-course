//
//  FileManager.h
//  Eight-Puzzle
//
//  Created by Truc Le on 9/16/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef __Eight_Puzzle__FileManager__
#define __Eight_Puzzle__FileManager__

#include <stdio.h>
#include <fstream>  // ifstream
#include <iostream> // cin, cout
#include <string>   // getline()

using namespace std;



class FileManager
{

public:
    FileManager();
    ifstream input_file;
    int grid[3][3];
    int algorithm_number;
    int DFS_depth;
    
    int column_number;
    int line_number;
    string current_line;
    

    ifstream getFile();
    char getCurrentCharacter();
    void advance();
    void checkAndGetGrid();
    void getAlgorithmNumber();
    
};
#endif /* defined(__Eight_Puzzle__FileManager__) */
