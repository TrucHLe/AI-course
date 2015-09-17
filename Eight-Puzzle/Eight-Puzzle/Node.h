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
    
private:
    State state;
    Node* parent;
    Node* child;
    vector<Node*> children;
    
    
public:
    Node();
    Node( State s, Node* p );
    
};



#endif /* defined(__Eight_Puzzle__Node__) */
