//
//  FileManager.h
//  Sudoku
//
//  Created by Truc Le on 10/5/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef __Sudoku__FileManager__
#define __Sudoku__FileManager__

#include <stdio.h>
#include <iostream> //cin, cout
#include <fstream>  //ifstream
#include <vector>	//vector

using namespace std;

class FileManager {
    
private:
    ifstream input;
    int line_number;
    int column_number;
    string current_line;

public:
    FileManager();
    vector<string> grid;
    
    ifstream getFile();
    char getCurrentChar();
    void advance();
    void getGrid();
    
};

#endif /* defined(__Sudoku__FileManager__) */
