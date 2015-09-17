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
void printNode( Node* node, string gridName, int distance, int isDebuggingNode );
void printSolution( Node node );



//---------------------------------------------
// Debugging tools
//
bool print_debug_grid = true;



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
    Node node( state, NULL ) ;
  
    //AS( node );
    BrFS( node );

//    switch ( algorithm_number )
//    {
//        case 1:
//            if ( BrFS( node ) )
//            {
//                time = clock() - time;
//                cout << "Time completing Breadth-First Search: " << ( double ) time / CLOCKS_PER_SEC << " seconds"<< endl;
//            }
//            break;
//            
//        
//        case 5:
//            if ( AS( node ) )
//            {
//                time = clock() - time;
//                cout << "Time completing A* Search: " << ( double ) time / CLOCKS_PER_SEC << " seconds"<< endl;
//            }
//            break;
//            
//        default:
//            break;
//    }
    
    
    return 0;
    
}

//
// !Main
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// A* Search
//
struct ASqueueComparison // this sets the priority of a Node to its Manhattan distance for use in A* search
{
    bool operator() ( Node &node1, Node &node2 )
    {
        return node1.state.manhattan_distance > node2.state.manhattan_distance;
    }
};

typedef priority_queue<Node, vector<Node>, ASqueueComparison> ASqueue; // define ASqueue type



bool AS( Node node )
{
    ASqueue AS_queue;
    State current_state;
    Node* current_node;
    vector<Node> parent_nodes;  // store parent nodes since priority queue rearrange
    int parent_node_index;      // nodes' order, making it hard to track where the parent is
    
    current_node    = &node;
    current_state   = current_node->state;
    
    AS_queue.push( *current_node );
    
    
    parent_node_index = 0;
    parent_nodes.push_back( *current_node );

    
    
    
    while ( !AS_queue.empty() )
    {
        printNode( current_node, "Current node", current_state.manhattan_distance, 1 );
        AS_queue.pop();

        
        if ( current_state.canMove( Up ) && current_state.previousMove() != Down )
        {
            Node n = Node( State( current_state, Up ), &parent_nodes.at( parent_node_index ) );
            AS_queue.push( n );
            
            
            
            cout << "----------" << endl;

            
            printNode( &n, "Up", n.state.manhattan_distance, 1 );
            
            
            printNode( n.parent, "Up's Parent", -5, 1 );
//            Node t;
//            t = AS_queue.top();
//            printNode( &t, "Up's Top", -1, 1 );
            cout << "----------" << endl;

            
            
            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }

        }
        
        
        if ( current_state.canMove( Down ) && current_state.previousMove() != Up )
        {
            Node n = Node( State( current_state, Down ), &parent_nodes.at( parent_node_index ) );
            AS_queue.push( n );
            
    
            
            cout << "----------" << endl;
            
    
            printNode( &n, "Down", n.state.manhattan_distance, 1 );
            
            
            printNode( n.parent, "Down's Parent", -5, 1 );
            //            Node t;
            //            t = AS_queue.top();
            //            printNode( &t, "Down's Top", -1, 1 );
            cout << "----------" << endl;
            
            
            
            
            if ( AS_queue.size() > 1 )
            {
                cout << "Down's Parent F2" << endl;
                for ( int i : { 0, 1, 2 } )
                {
                    for ( int j : { 0, 1, 2 } )
                        cout << n.parent->parent->state.grid[i][j] << " ";
                    cout << endl;
                }
                cout << endl;
            }
            

            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }
        }
        
        
        if ( current_state.canMove( Left ) && current_state.previousMove() != Right )
        {
            Node n = Node( State( current_state, Left ), &parent_nodes.at( parent_node_index ) );
            AS_queue.push( n );
            
            
            
            
            cout << "----------" << endl;
            
            
            printNode( &n, "Left", n.state.manhattan_distance, 1 );
            
            
            printNode( n.parent, "Left's Parent", -5, 1 );
            //            Node t;
            //            t = AS_queue.top();
            //            printNode( &t, "Left's Top", -1, 1 );
            cout << "----------" << endl;
            
            
            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }
            
        }
        
        
        if ( current_state.canMove( Right ) && current_state.previousMove() != Left )
        {
            Node n = Node( State( current_state, Right ), &parent_nodes.at( parent_node_index ) );
            AS_queue.push( n );
            
            
            
            
            cout << "----------" << endl;
            
            
            printNode( &n, "Right", n.state.manhattan_distance, 1 );
            
            
            printNode( n.parent, "Right's Parent", -5, 1 );
            //            Node t;
            //            t = AS_queue.top();
            //            printNode( &t, "Right's Top", -1, 1 );
            cout << "----------" << endl;
            
            
            

            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }

        }
        
        // Debugging
        Node t;
        t = AS_queue.top();
        printNode( &t, "Top after expansion", -1, 1 );
        // !Debugging

        
        
        
        // boo = &foo : boo is pointing at memory location of foo
        // *boo = foo : replace the content of whatever boo is pointing at to foo
        *current_node = AS_queue.top();
        current_state = current_node->state;
     
        
        ++parent_node_index;
        parent_nodes.push_back( AS_queue.top() );
        
        
        
        
         // Debugging
         cout << "-------------------------" << parent_nodes.size() << endl;
         cout << endl;
         // !Debugging
        
    }
    
    
    return false;
}

//
// !A* Search
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Breadth-First Search
//
bool BrFS( Node node )
{
    queue<Node> BFS_queue;
    State current_state;
    Node* current_node;
    
    current_node    = &node; //point current node to node's value
    current_state   = current_node->state;
    
    BFS_queue.push( *current_node );
    

    
    while ( !BFS_queue.empty() )
    {
        printNode( current_node, "Current Node", -1, 1 );

        
        
        if ( current_state.canMove( Up ) && current_state.previousMove() != Down )
        {
            Node n = Node( State( current_state, Up ), current_node );
            BFS_queue.push( n );
            
            printNode( &n, "Up", -1, 1 );
            
            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }
        }
        

        if ( current_state.canMove( Down ) && current_state.previousMove() != Up )
        {
            Node n = Node( State( current_state, Down ), current_node );
            BFS_queue.push( n );

            printNode( &n, "Down", -1, 1 );
            
            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }

        }
        
        
        if ( current_state.canMove( Left ) && current_state.previousMove() != Right )
        {
            Node n = Node( State( current_state, Left ), current_node );
            BFS_queue.push( n );

            printNode( &n, "Left", -1, 1 );

            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }

        }
        
        
        if ( current_state.canMove( Right ) && current_state.previousMove() != Left )
        {
            Node n = Node( State( current_state, Right ), current_node );
            BFS_queue.push( n );

            printNode( &n, "Up", -1, 1 );

            
            if ( n.state.isGoal() )
            {
                printSolution( n );
                return true;
            }

        }
        

        BFS_queue.pop();
        
        current_node    = &BFS_queue.front();
        current_state   = current_node->state;
        
        
        /*
        // Debugging
        cout << "-------------------------" << BFSqueue.size() << endl;
        cout << endl;
        // !Debugging
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


    while ( current_node->parent )
    {
        printNode( current_node, "Current", -1, 1 );
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
    printNode( current_node, "Puzzle", -1, 0 ); // at this time, current_node is
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
void printNode( Node* node, string gridName, int distance, int isDebuggingNode )
{
    
    if ( isDebuggingNode == 1 )
    {
        if ( print_debug_grid )
        {
            cout << gridName << " --- " << distance << endl;
            for ( int i = 0; i < 3; ++i )
            {
                for ( int j = 0; j < 3; ++j )
                    cout << node->state.grid[i][j] << " ";
                cout << endl;
            }
            cout << endl;
        }
    }
    else if ( isDebuggingNode == 0 )
    {
        cout << gridName << " --- " << distance << endl;
        for ( int i = 0; i < 3; ++i )
        {
            for ( int j = 0; j < 3; ++j )
                cout << node->state.grid[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    
}

//
// !printNode
//===---------------------------------------===//