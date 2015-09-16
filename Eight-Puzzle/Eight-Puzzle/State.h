//
//  State.h
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef __Eight_Puzzle__State__
#define __Eight_Puzzle__State__

#include <stdio.h>
#include <fstream>  // ifstream

using namespace std;


class State
{
    
private:
    int grid[3][3];
    
public:
    State( ifstream& i );
    
};

#endif /* defined(__Eight_Puzzle__State__) */
