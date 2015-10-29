//
//  Move.cpp
//  ReinforcementLearningNIM
//
//  Created by Truc Le on 10/28/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#include "Move.h"

Move::Move(int r, int c)
{
	row		= r;
	column	= c;
}


void Move::setValue(int v)
{
	value = v;
}