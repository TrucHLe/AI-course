//
//  Search.h
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef __Eight_Puzzle__Search__
#define __Eight_Puzzle__Search__

#include <stdio.h>
#include <fstream>      // ifstream

using namespace std;



class Search
{
private:
    ifstream& inputFile;
    
public:
    Search( ifstream& i );
};

#endif /* defined(__Eight_Puzzle__Search__) */
