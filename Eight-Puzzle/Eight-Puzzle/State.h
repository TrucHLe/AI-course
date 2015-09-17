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
#include <stdlib.h> // abs
#include <tuple>    // pair<T, T>

using namespace std;


enum Directions { Up, Down, Left, Right, None };


class State
{
    
public:
    int grid[3][3];
    pair<int, int> blank_tile;
    Directions previous_move;

    
    State();
    State( int g[3][3] ); //init State and find the blank tile
    State( State s, Directions d ); // for creating child state
    
    bool isGoal();
    bool canMove( Directions direction );
    Directions previousMove();
    void setBlank( int x, int y );
    void moveBlank( Directions direction );
    
    pair<int, int> tilePosition( int tileValue );
    int distance( pair<int, int> tile1, pair<int, int> tile2 );
    int ManhattanDistance();
    
};

#endif /* defined(__Eight_Puzzle__State__) */
