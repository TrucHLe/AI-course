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

#include "FileManager.h"
#include "Search.h"
#include "State.h"
#include "Node.h"

using namespace std;








//---------------------------------------------
// Function headers
//
//void BrFS( Node node );
//void DFS( Node node );
//void IDS( Node node );
//void BeFS( Node node );
//void AS( Node node );
//void printSolution( Node node );



//===----------------------------------------------------------------------===//
// Main
//
int main(int argc, const char * argv[])
{
    
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
    
    
    //    State state( grid );
    //    Node node( state, NULL) ;
    
    
    //BrFS( node );
    
    return 0;
    
}

//
// !Main
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Print solution
//
void printSolution( Node node )
{
    vector<Directions> solution;
    Node* current_node;
    
    *current_node = node;
    
    while ( current_node->parent != NULL )
    {
        solution.push_back( current_node->parent->state.previousMove() );
        current_node = current_node->parent;
    }
    
    for ( Directions d : solution )
    {
        cout << d << endl;
    }
}

//
// !printSolution
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Breadth-First Search
//
void BrFS( Node node )
{
    queue<Node> BFSqueue;
    State current_state;
    Node* current_node;
    
    *current_node   = node; //point current node to node's value
    current_state   = current_node->state;
    
    BFSqueue.push( node );
    
    
    while ( !BFSqueue.empty() )
    {
        if ( current_node->state.canMove( Up ) && current_node->state.previousMove() != Down )
        {
            Node n = Node( State( current_state, Up ), current_node );
            BFSqueue.push( n );
            
            if ( n.state.isGoal() )
                printSolution( n );
        }
        
        
        if ( current_node->state.canMove( Down ) && current_node->state.previousMove() != Up )
        {
            Node n = Node( State( current_state, Down ), current_node );
            BFSqueue.push( n );
            
            if ( n.state.isGoal() )
                printSolution( n );
        }
        
        
        if ( current_node->state.canMove( Left ) && current_node->state.previousMove() != Right )
        {
            Node n = Node( State( current_state, Left ), current_node );
            BFSqueue.push( n );
            
            if ( n.state.isGoal() )
                printSolution( n );
        }
        
        
        if ( current_node->state.canMove( Right ) && current_node->state.previousMove() != Left )
        {
            Node n = Node( State( current_state, Right ), current_node );
            BFSqueue.push( n );
            
            if ( n.state.isGoal() )
                printSolution( n );
        }
        
        
        BFSqueue.pop();
        *current_node = BFSqueue.front();
        
    }
    
}

//
// !Breadth-First Search
//===---------------------------------------===//