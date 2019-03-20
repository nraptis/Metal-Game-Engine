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
#define X_CONSTRAINT_TARGET 100
#define X_CONSTRAINT_LEFT_SPAWN 200
#define X_CONSTRAINT_LEFT_PEEK 300
#define X_CONSTRAINT_LEFT_QUARTER 400
#define X_CONSTRAINT_CENTER 500
#define X_CONSTRAINT_RIGHT_QUARTER 600
#define X_CONSTRAINT_RIGHT_PEEK 700
#define X_CONSTRAINT_RIGHT_SPAWN 800

#define Y_CONSTRAINT_NONE 0
#define Y_CONSTRAINT_TARGET 100
#define Y_CONSTRAINT_TOP_SPAWN 200
#define Y_CONSTRAINT_TOP_PEEK 300
#define Y_CONSTRAINT_TOP_QUARTER 400
#define Y_CONSTRAINT_CENTER 500
#define Y_CONSTRAINT_BOTTOM_QUARTER 600
#define Y_CONSTRAINT_BOTTOM 800

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
    
    bool                            HasX();
    bool                            HasY();
    
    float                           GameX(bool pOffset);
    float                           GameY(bool pOffset);
    
    
};

#endif /* ConstraintBlueprint_hpp */
