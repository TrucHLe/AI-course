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
void printBrFSsolution( Node node, int nodesExpanded );
void printASsolution( Node node, vector<Node> parents, int nodesExpanded );



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
    Node node( state, NULL )  ;
  


    switch ( algorithm_number )
    {
        case 1:
            cout << endl;
            printNode( &node, "Puzzle", -1, 0 );
            
            if ( BrFS( node ) )
            {
                time = clock() - time;
                cout << "Breadth-First Search time: " << ( double ) time / CLOCKS_PER_SEC << " seconds"<< endl;
            }
            break;
            
        
        case 2:
            cout << endl;
            printNode( &node, "Puzzle", -1, 0 );
            
            if ( AS( node ) )
            {
                time = clock() - time;
                cout << "A* Search time: " << ( double ) time / CLOCKS_PER_SEC << " seconds"<< endl;
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
    int nodes_expanded = 0;
    
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
            Node n = Node( State( current_state, Up ), &parent_nodes.at( parent_node_index ), parent_node_index );
            AS_queue.push( n );
            ++nodes_expanded;
            
            
            printNode( &n, "Up", n.state.manhattan_distance, 1 );
            
            if ( n.state.isGoal() )
            {
                printASsolution( n, parent_nodes, nodes_expanded );
                return true;
            }

        }
        
        
        if ( current_state.canMove( Down ) && current_state.previousMove() != Up )
        {
            Node n = Node( State( current_state, Down ), &parent_nodes.at( parent_node_index ), parent_node_index );
            AS_queue.push( n );
            ++nodes_expanded;
            
    
            printNode( &n, "Down", n.state.manhattan_distance, 1 );
            
            if ( n.state.isGoal() )
            {
                printASsolution( n, parent_nodes, nodes_expanded );
                return true;
            }
        }
        
        
        if ( current_state.canMove( Left ) && current_state.previousMove() != Right )
        {
            Node n = Node( State( current_state, Left ), &parent_nodes.at( parent_node_index ), parent_node_index );
            AS_queue.push( n );
            ++nodes_expanded;
            

            printNode( &n, "Left", n.state.manhattan_distance, 1 );
            
            if ( n.state.isGoal() )
            {
                printASsolution( n, parent_nodes, nodes_expanded );
                return true;
            }
            
        }
        
        
        if ( current_state.canMove( Right ) && current_state.previousMove() != Left )
        {
            Node n = Node( State( current_state, Right ), &parent_nodes.at( parent_node_index ), parent_node_index );
            AS_queue.push( n );
            ++nodes_expanded;
            

            printNode( &n, "Right", n.state.manhattan_distance, 1 );
            
            if ( n.state.isGoal() )
            {
                printASsolution( n, parent_nodes, nodes_expanded );
                return true;
            }

        }

        
        
        
        // boo = &foo : boo is pointing at memory location of foo
        // *boo = foo : replace the content of whatever boo is pointing at to foo
        *current_node = AS_queue.top();
        current_state = current_node->state;
     
        
        ++parent_node_index;
        parent_nodes.push_back( AS_queue.top() );
        
        
        
        /*
        // Debugging
        cout << "-------------------------" << parent_nodes.size() << endl;
        cout << endl;
        // !Debugging
        */
    }
    
    
    return false;
}

//
// !A* Search
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Print A* search solution by matching current node's parent index
// to AS_queue. Didn't use pointers like printBrFSsolution because
// the typedef ASqueue is constant and doesn't allow access to a node's parent
//
void printASsolution( Node node, vector<Node> parents, int nodesExpanded )
{
    vector<Node> AS_queue;
    vector<Directions> directions;
    stack<string> solution;
    int steps;
    Node current_parent_node;
    int current_parent_index;

    
    
    AS_queue = parents;
    directions.push_back( node.state.previous_move );
    current_parent_index = node.parent_AS_queue_index;
    
    
    while ( current_parent_index != 0 )
    {
        current_parent_node = AS_queue.at( current_parent_index );
        directions.push_back( current_parent_node.state.previous_move );
        current_parent_index = current_parent_node.parent_AS_queue_index;
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
    
    steps = ( int ) solution.size();
    
    
    cout << "Solution: ";
    while ( !solution.empty() )
    {
        cout << solution.top();
        solution.pop();
    }
    cout << endl;
    cout << "Steps: " << steps << endl;
    cout << "Nodes expanded: " << nodesExpanded << endl;
    
}

//
// !printASsolution
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Breadth-First Search
//
bool BrFS( Node node )
{
    queue<Node> BFS_queue;
    State current_state;
    Node* current_node;
    int nodes_expanded = 0;
    
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
            ++nodes_expanded;
            
            printNode( &n, "Up", -1, 1 );
            
            
            if ( n.state.isGoal() )
            {
                printBrFSsolution( n, nodes_expanded );
                return true;
            }
        }
        

        if ( current_state.canMove( Down ) && current_state.previousMove() != Up )
        {
            Node n = Node( State( current_state, Down ), current_node );
            BFS_queue.push( n );
            ++nodes_expanded;
            
            printNode( &n, "Down", -1, 1 );
            
            
            if ( n.state.isGoal() )
            {
                printBrFSsolution( n, nodes_expanded );
                return true;
            }

        }
        
        
        if ( current_state.canMove( Left ) && current_state.previousMove() != Right )
        {
            Node n = Node( State( current_state, Left ), current_node );
            BFS_queue.push( n );
            ++nodes_expanded;

            printNode( &n, "Left", -1, 1 );

            
            if ( n.state.isGoal() )
            {
                printBrFSsolution( n, nodes_expanded );
                return true;
            }

        }
        
        
        if ( current_state.canMove( Right ) && current_state.previousMove() != Left )
        {
            Node n = Node( State( current_state, Right ), current_node );
            BFS_queue.push( n );
            ++nodes_expanded;

            printNode( &n, "Up", -1, 1 );

            
            if ( n.state.isGoal() )
            {
                printBrFSsolution( n, nodes_expanded );
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
// Print breadth-first search solution
//
void printBrFSsolution( Node node, int nodesExpanded )
{
    vector<Directions> directions;
    stack<string> solution;
    int steps;
    Node* current_node;

    current_node = &node;


    while ( current_node->parent )
    {
        printNode( current_node, "Current", -1, 1 );
        directions.push_back( current_node->state.previous_move );
        current_node = current_node->parent;
    }

    
    
    for ( Directions direction : directions )
    {
        switch ( direction )
        {
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
    
    steps = ( int ) solution.size();
    
    
    cout << "Solution: ";
    while ( !solution.empty() )
    {
        cout << solution.top();
        solution.pop();
    }
    cout << endl;
    cout << "Steps: " << steps << endl;
    cout << "Nodes expanded: " << nodesExpanded << endl;
    
}

//
// !printBrFSsolution
//===---------------------------------------===//



//===----------------------------------------------------------------------===//
// Print node
//
void printNode( Node* node, string gridName, int distance, int isDebuggingNode )
{
    
    if ( isDebuggingNode == 1 )
    {
        if ( print_debug_grid )
        {
            cout << gridName << endl;
            for ( int i : { 0, 1, 2 } )
            {
                for ( int j : { 0, 1, 2 } )
                    cout << node->state.grid[i][j] << " ";
                cout << endl;
            }
            cout << endl;
        }
    }
    else if ( isDebuggingNode == 0 )
    {
        cout << gridName << endl; //<< " --- " << distance
        for ( int i : { 0, 1, 2 } )
        {
            for ( int j : { 0, 1, 2 } )
                cout << node->state.grid[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    
}

//
// !printNode
//===---------------------------------------===//