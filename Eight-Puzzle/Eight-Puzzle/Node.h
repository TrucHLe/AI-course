//
//  Node.h
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef __Eight_Puzzle__Node__
#define __Eight_Puzzle__Node__

#include <stdio.h>
#include <vector>
#include "State.h"


class Node
{
    
public:
    State state;
    Node* parent;
    int parent_AS_queue_index;
    
    Node();
    Node( State s, Node* p );
    Node( State s, Node* p, int i ); // dummy boolean to distinguish from top constructor
};



#endif /* defined(__Eight_Puzzle__Node__) */
