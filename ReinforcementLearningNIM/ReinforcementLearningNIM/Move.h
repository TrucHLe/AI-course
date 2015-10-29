//
//  Move.h
//  ReinforcementLearningNIM
//
//  Created by Truc Le on 10/28/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//

#ifndef ReinforcementLearningNIM_Move_h
#define ReinforcementLearningNIM_Move_h

struct Move
{
	int row;
	int column;
	int value;
	
	Move(int r, int c);
	void setValue(int v);
};

#endif
