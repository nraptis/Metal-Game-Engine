//
//  ConstraintBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ConstraintBlueprint_hpp
#define ConstraintBlueprint_hpp

#define X_CONSTRAINT_NONE 0
#define X_CONSTRAINT_TARGET 1000
#define X_CONSTRAINT_LEFT_SPAWN 1
#define X_CONSTRAINT_LEFT_PEEK 2
#define X_CONSTRAINT_LEFT_QUARTER 3
#define X_CONSTRAINT_CENTER 4
#define X_CONSTRAINT_RIGHT_QUARTER 5
#define X_CONSTRAINT_RIGHT_PEEK 6
#define X_CONSTRAINT_RIGHT_SPAWN 7

#define Y_CONSTRAINT_NONE 0
#define Y_CONSTRAINT_TARGET 1000
#define Y_CONSTRAINT_TOP_SPAWN 1
#define Y_CONSTRAINT_TOP_PEEK 2
#define Y_CONSTRAINT_TOP_QUARTER 3
#define Y_CONSTRAINT_CENTER 4
#define Y_CONSTRAINT_BOTTOM_QUARTER 5
#define Y_CONSTRAINT_BOTTOM 6

class Constraint {
public:
    Constraint();
    ~Constraint();
    
    int                             mTypeX;
    int                             mTypeY;
    
    float                           mOffsetX;
    float                           mOffsetY;
    
    int                             mTargetX;
    int                             mTargetY;
    
};

#endif /* ConstraintBlueprint_hpp */
