//
//  Node.cpp
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "Node.h"



//===----------------------------------------------------------------------===//
// Constructors
//
Node::Node()
{
    
}


Node::Node( State s, Node* p )
{
    state = s;
    parent = p;
}


Node::Node( State s, Node* p, int i )
{
    state = s;
    parent = p;
    parent_AS_queue_index = i;
}

//
// !Constructors
//===---------------------------------------===//
