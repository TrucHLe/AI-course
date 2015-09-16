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



class Node
{
    
private:
    int value;
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    
    
    
public:
    Node();
    
    void setValue( int v );
    void setUp( Node* u );
    void setDown( Node* d );
    void setLeft( Node* l );
    void setRight( Node* r );
    
    int getValue();
    Node* getUp();
    Node* getDown();
    Node* getLeft();
    Node* getRight();
    
    bool hasUp();
    bool hasDown();
    bool hasLeft();
    bool hasRight();
    
};



#endif /* defined(__Eight_Puzzle__Node__) */
