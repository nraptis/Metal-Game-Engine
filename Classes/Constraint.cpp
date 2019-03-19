//
//  ConstraintBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Constraint.hpp"


Constraint::Constraint() {
    
    mTypeX = X_CONSTRAINT_NONE;
    mTypeY = Y_CONSTRAINT_NONE;
    
    mOffsetX;
    mOffsetY;
    
    mTargetX = -1;
    mTargetY = -1;
    
}

Constraint::~Constraint() {
    
}



