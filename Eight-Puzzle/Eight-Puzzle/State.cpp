//
//  State.cpp
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "State.h"
#include <iostream>

using namespace std;



//===----------------------------------------------------------------------===//
// Constructors
//
State::State()
{
    
}


State::State( int g[3][3] )
{
    for ( int i : { 0, 1, 2 } ) // Use loops since C++ arrays aren't assignable
        for ( int j : { 0, 1, 2 } )
        {
            grid[i][j] = g[i][j];
            
            if ( grid[i][j] == 0 )
                blank_tile = make_pair( i, j );
        }
}

//
// !Constructors
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Check whether current state is the goal
//
bool State::isGoal()
{
    if ( grid[0][0] == 1 && grid[0][1] == 2 && grid[0][2] == 3 &&
         grid[1][0] == 8 && grid[1][1] == 0 && grid[1][2] == 4 &&
         grid[2][0] == 7 && grid[2][1] == 6 && grid[2][2] == 5 )
        return true;
    else
        return false;
}

//
// !isGoal
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Check whether the blank tile can move to the specified direction
//
bool State::blankCanMove( Directions direction )
{
    int tile_x = get<0>( blank_tile );
    int tile_y = get<1>( blank_tile );
    
    switch ( direction )
    {
        case Up:
            if ( tile_x > 0 )
                return true;
            else
                return false;
            break;
        
        case Down:
            if ( tile_x < 2 )
                return true;
            else
                return false;
            break;
            
        case Left:
            if ( tile_y > 0 )
                return true;
            else
                return false;
            break;
            
        case Right:
            if ( tile_y < 2 )
                return true;
            else
                return false;
            break;
    }
}

//
// !blankCanMove
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Check and move the blank tile to the specified direction
//
void State::moveBlank( Directions direction )
{
    if ( blankCanMove( direction ) )
    {
        int tile_x = get<0>( blank_tile );
        int tile_y = get<1>( blank_tile );

        
        switch ( direction )
        {
            case Up:
                grid[ tile_x ][ tile_y ]        = grid[ tile_x - 1 ][ tile_y ];
                grid[ tile_x - 1 ][ tile_y ]    = 0;
                break;
                
            case Down:
                grid[ tile_x ][ tile_y ]        = grid[ tile_x + 1 ][ tile_y ];
                grid[ tile_x + 1 ][ tile_y ]    = grid[ tile_x ][ tile_y ];
                break;
                
            case Left:
                grid[ tile_x ][ tile_y ]        = grid[ tile_x ][ tile_y - 1 ];
                grid[ tile_x ][ tile_y - 1 ]    = grid[ tile_x ][ tile_y ];
                break;
                
            case Right:
                grid[ tile_x ][ tile_y ]        = grid[ tile_x ][ tile_y + 1 ];
                grid[ tile_x ][ tile_y + 1 ]    = grid[ tile_x ][ tile_y ];
                break;
        }
    }
    
    // Recheck to see if I need to throw error when blank can't move to d
}

//
// !moveBlank
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Get the specified tile's position
//
pair<int, int> State::tilePosition( int tileValue )
{
    for ( int i : { 0, 1, 2 } )
        for ( int j : { 0, 1, 2 } )
            if ( grid[i][j] == tileValue )
                return make_pair( i, j );
    
    return make_pair( NULL, NULL );
}

//
// !tilePosition
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Calculate the distance between the 2 specified tiles
//
int State::distance( pair<int, int> tile1, pair<int, int> tile2 )
{
    return abs( get<0>( tile1 ) - get<0>( tile2 ) ) + abs( get<1>( tile1 ) - get<1>( tile2 ) );
}

//
// !Distance
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Calculate Manhattan distance, aka distances
// between every tile and where it is supposed to be
//
int State::ManhattanDistance()
{
    int Manhattan_distance = distance( make_pair( 0, 0 ), tilePosition( 1 ) ) +
                             distance( make_pair( 0, 1 ), tilePosition( 2 ) ) +
                             distance( make_pair( 0, 2 ), tilePosition( 3 ) ) +
                             distance( make_pair( 1, 0 ), tilePosition( 8 ) ) +
                             distance( make_pair( 1, 1 ), tilePosition( 0 ) ) +
                             distance( make_pair( 1, 2 ), tilePosition( 4 ) ) +
                             distance( make_pair( 2, 0 ), tilePosition( 7 ) ) +
                             distance( make_pair( 2, 1 ), tilePosition( 6 ) ) +
                             distance( make_pair( 2, 2 ), tilePosition( 5 ) );
    
    return Manhattan_distance;
}

//
// !ManhattanDistance
//===---------------------------------------===//