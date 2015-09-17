//
//  Search.cpp
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//


#include <fstream>  // ifstream
#include <iostream> // cin, cout
#include <queue>    // queue
#include <stack>    // stack
#include <time.h>   // clock_t

#include "FileManager.h"
#include "Search.h"
#include "State.h"
#include "Node.h"

using namespace std;



//---------------------------------------------
// Function headers
//
bool BrFS( Node node );
bool DFS( Node node );
bool IDS( Node node );
bool BeFS( Node node );
bool AS( Node node );
void printGrid( string girdName, int grid[3][3], int printDebugGrid );
void printSolution( Node node );



//---------------------------------------------
// Debugging tools
//
bool print_debug_grid = false;



//===----------------------------------------------------------------------===//
// Main
//
int main(int argc, const char * argv[])
{
    clock_t time = clock();
    
    //---------------------------------------------
    // User Input
    //
    FileManager file_manager = FileManager();
    int algorithm_number;
    int DFS_depth;
    int grid[3][3];
    
    
    algorithm_number = file_manager.algorithm_number;
    DFS_depth = file_manager.DFS_depth;
    
    for ( int i : { 0, 1, 2 } )
        for ( int j : { 0, 1, 2 } )
            grid[i][j] = file_manager.grid[i][j];

    
    //
    // !User Input
    //---------------------------------------------
    
    
    State state( grid );
    Node node( state, NULL) ;

    switch ( algorithm_number )
    {
        case 1:
            if ( BrFS( node ) )
            {
                time = clock() - time;
                cout << "Time completing Breadth-First Search: " << ( double ) time / CLOCKS_PER_SEC << " seconds"<< endl;
            }
            break;
            
        default:
            break;
    }
    
    
    return 0;
    
}

//
// !Main
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Breadth-First Search
//
bool BrFS( Node node )
{
    queue<Node> BFSqueue;
    State current_state;
    Node* current_node;
    
    current_node    = &node; //point current node to node's value
    current_state   = current_node->state;
    
    BFSqueue.push( *current_node );
    
    
    // Debugging
    
    // cout << BFSqueue.front().state.grid[i][j] << " ";
    // current_node->state.grid[i][j]

    // !Debugging
    
    
    while ( !BFSqueue.empty() )
    {
        printGrid( "Current Node", current_node->state.grid, 1 );
        
        
        if ( current_node->state.canMove( Up ) && current_node->state.previousMove() != Down )
        {
            Node n = Node( State( current_state, Up ), current_node );
            BFSqueue.push( n );
            
            printGrid( "Up", n.state.grid, 1 );
            
            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }
        }
        
        
        if ( current_node->state.canMove( Down ) && current_node->state.previousMove() != Up )
        {
            Node n = Node( State( current_state, Down ), current_node );
            BFSqueue.push( n );

            printGrid( "Down", n.state.grid, 1 );
            
            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }

        }
        
        
        if ( current_node->state.canMove( Left ) && current_node->state.previousMove() != Right )
        {
            Node n = Node( State( current_state, Left ), current_node );
            BFSqueue.push( n );

            printGrid( "Left", n.state.grid, 1 );

            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }

        }
        
        
        if ( current_node->state.canMove( Right ) && current_node->state.previousMove() != Left )
        {
            Node n = Node( State( current_state, Right ), current_node );
            BFSqueue.push( n );

            printGrid( "Up", n.state.grid, 1 );

            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }

        }
        

        BFSqueue.pop();
        
        current_node    = &BFSqueue.front();
        current_state   = current_node->state;
        
        
        /*
        // Debugging tools
        cout << "-------------------------" << BFSqueue.size() << endl;
        cout << endl;
        // !Debugging tools
        */
    }

    
    return false;
}

//
// !Breadth-First Search
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Print solution
//
void printSolution( Node node )
{
    vector<Directions> directions;
    stack<string> solution;
    Node* current_node;
    
    current_node = &node;

    
    while ( current_node->parent != NULL )
    {
        printGrid( "Parent", current_node->state.grid, 1 );
        
        directions.push_back( current_node->state.previousMove() );
        current_node = current_node->parent;
    }
    
    
    for ( Directions direction : directions )
    {
        switch ( direction ) {
            case Up:
                solution.push( "Up " );
                break;
                
            case Down:
                solution.push( "Down " );
                break;
                
            case Left:
                solution.push( "Left " );
                break;
                
            case Right:
                solution.push( "Right " );
                break;
                
            case None:
                break;
                
        }
    }
    
    
    cout << endl;
    printGrid( "Puzzle", current_node->state.grid, 0 ); // at this time, current_node is
                                                        // pointing at the original puzzle
                                                        // since solution reads backwards
    
    
    cout << "Solution: ";
    while ( !solution.empty() )
    {
        cout << solution.top();
        solution.pop();
    }
    cout << endl;
    
}

//
// !printSolution
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Print grid
//
void printGrid( string gridName, int grid[3][3], int printDebugGrid )
{
    if ( printDebugGrid == 1 )
    {
        if ( print_debug_grid )
        {
            cout << gridName << endl;
            for ( int i : { 0, 1, 2 } )
            {
                for ( int j : { 0, 1, 2 } )
                    cout << grid[i][j] << " ";
                cout << endl;
            }
            cout << endl;
        }
    }
    else
    {
        cout << gridName << endl;
        for ( int i : { 0, 1, 2 } )
        {
            for ( int j : { 0, 1, 2 } )
                cout << grid[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    
}

//
// !printGrid
//===---------------------------------------===//