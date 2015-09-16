//
//  Node.cpp
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "Node.h"



Node::Node()
{
    value   = 0;
    up      = NULL;
    down    = NULL;
    left    = NULL;
    right   = NULL;
}



//===----------------------------------------------------------------------===//
// Setters
//===----------------------------------------------------------------------===//

void Node::setValue( int v )
{
    value = v;
}

void Node::setUp( Node* u )
{
    if ( u == NULL )
        up = NULL;
    else
        up = u;
}

void Node::setDown( Node* d )
{
    if ( d == NULL )
        down = NULL;
    else
        down = d;
}

void Node::setLeft( Node* l )
{
    if ( l == NULL )
        left = NULL;
    else
        left = l;
}

void Node::setRight( Node* r )
{
    if ( r == NULL )
        right = NULL;
    else
        right = r;
}

//
// !Setters
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
// Getters
//===----------------------------------------------------------------------===//

int Node::getValue()
{
    return value;
}

Node* Node::getUp()
{
    return up;
}

Node* Node::getDown()
{
    return down;
}

Node* Node::getLeft()
{
    return left;
}

Node* Node::getRight()
{
    return right;
}

//
// Getters
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
// Check Node existance
//===----------------------------------------------------------------------===//

bool Node::hasUp()
{
    if ( up != NULL )
        return true;
    else
        return false;
}

bool Node::hasDown()
{
    if ( down != NULL )
        return true;
    else
        return false;
}

bool Node::hasLeft()
{
    if ( left != NULL )
        return true;
    else
        return false;
}

bool Node::hasRight()
{
    if ( right != NULL )
        return true;
    else
        return false;
}

//
// Check Node existance
//===----------------------------------------------------------------------===//

