//
//  ConstraintBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Constraint.hpp"
#include "Game.hpp"

Constraint::Constraint() {
    
    mTypeX = X_CONSTRAINT_NONE;
    mTypeY = Y_CONSTRAINT_NONE;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    
    mTargetX = -1;
    mTargetY = -1;
}

Constraint::~Constraint() {
    
}


bool Constraint::HasX() {
    
    if (gGame) {
        if (mTypeX == X_CONSTRAINT_LEFT_EXIT) { return true; }
        if (mTypeX == X_CONSTRAINT_LEFT_SPAWN) { return true; }
        if (mTypeX == X_CONSTRAINT_LEFT_PEEK) { return true; }
        if (mTypeX == X_CONSTRAINT_LEFT_QUARTER) { return true; }
        if (mTypeX == X_CONSTRAINT_CENTER) { return true; }
        if (mTypeX == X_CONSTRAINT_RIGHT_QUARTER) { return true; }
        if (mTypeX == X_CONSTRAINT_RIGHT_PEEK) { return true; }
        if (mTypeX == X_CONSTRAINT_RIGHT_SPAWN) { return true; }
        if (mTypeX == X_CONSTRAINT_RIGHT_EXIT) { return true; }
        
        
        
    }
    return false;
}

bool Constraint::HasY() {
    
    if (gGame) {
        if (mTypeY == Y_CONSTRAINT_TOP_EXIT) { return true; }
        if (mTypeY == Y_CONSTRAINT_TOP_SPAWN) { return true; }
        if (mTypeY == Y_CONSTRAINT_TOP_PEEK) { return true; }
        if (mTypeY == Y_CONSTRAINT_TOP_QUARTER) { return true; }
        if (mTypeY == Y_CONSTRAINT_CENTER) { return true; }
        if (mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) { return true; }
        if (mTypeY == Y_CONSTRAINT_BOTTOM) { return true; }
    }
    
    return false;
}

float Constraint::GameX(bool pOffset) {
    if (gGame) {
        if (pOffset) {
            if (mTypeX == X_CONSTRAINT_LEFT_EXIT) { return gGame->mExitZoneLeft + mOffsetX; }
            if (mTypeX == X_CONSTRAINT_LEFT_SPAWN) { return gGame->mSpawnZoneLeft + mOffsetX; }
            if (mTypeX == X_CONSTRAINT_LEFT_PEEK) { return gGame->mPeekZoneLeft + mOffsetX; }
            if (mTypeX == X_CONSTRAINT_LEFT_QUARTER) { return gGame->mQuarterZoneLeft + mOffsetX; }
            if (mTypeX == X_CONSTRAINT_CENTER) { return gGame->mWidth2 + mOffsetX; }
            if (mTypeX == X_CONSTRAINT_RIGHT_QUARTER) { return gGame->mQuarterZoneRight + mOffsetX; }
            if (mTypeX == X_CONSTRAINT_RIGHT_PEEK) { return gGame->mPeekZoneRight + mOffsetX; }
            if (mTypeX == X_CONSTRAINT_RIGHT_SPAWN) { return gGame->mSpawnZoneRight + mOffsetX; }
            if (mTypeX == X_CONSTRAINT_RIGHT_EXIT) { return gGame->mExitZoneRight + mOffsetX; }
        } else {
            
            if (mTypeX == X_CONSTRAINT_LEFT_EXIT) { return gGame->mExitZoneLeft; }
            if (mTypeX == X_CONSTRAINT_LEFT_SPAWN) { return gGame->mSpawnZoneLeft; }
            if (mTypeX == X_CONSTRAINT_LEFT_PEEK) { return gGame->mPeekZoneLeft; }
            if (mTypeX == X_CONSTRAINT_LEFT_QUARTER) { return gGame->mQuarterZoneLeft; }
            if (mTypeX == X_CONSTRAINT_CENTER) { return gGame->mWidth2; }
            if (mTypeX == X_CONSTRAINT_RIGHT_QUARTER) { return gGame->mQuarterZoneRight; }
            if (mTypeX == X_CONSTRAINT_RIGHT_PEEK) { return gGame->mPeekZoneRight; }
            if (mTypeX == X_CONSTRAINT_RIGHT_SPAWN) { return gGame->mSpawnZoneRight; }
            if (mTypeX == X_CONSTRAINT_RIGHT_EXIT) { return gGame->mExitZoneRight; }
        }
    }
    return 0.0f;
}
float Constraint::GameY(bool pOffset) {
    if (gGame) {
        if (pOffset) {
            if (mTypeY == Y_CONSTRAINT_TOP_EXIT) { return gGame->mExitZoneTop + mOffsetY; }
            if (mTypeY == Y_CONSTRAINT_TOP_SPAWN) { return gGame->mSpawnZoneTop + mOffsetY; }
            if (mTypeY == Y_CONSTRAINT_TOP_PEEK) { return gGame->mPeekZoneTop + mOffsetY; }
            if (mTypeY == Y_CONSTRAINT_TOP_QUARTER) { return gGame->mQuarterZoneTop + mOffsetY; }
            if (mTypeY == Y_CONSTRAINT_CENTER) { return (gGame->mPlayAreaBottom + gGame->mPlayAreaTop) / 2.0f + mOffsetY; }
            if (mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) { return gGame->mQuarterZoneBottom + mOffsetY; }
            if (mTypeY == Y_CONSTRAINT_BOTTOM) { return gGame->mPlayAreaBottom + mOffsetY; }
        } else {
            if (mTypeY == Y_CONSTRAINT_TOP_EXIT) { return gGame->mExitZoneTop; }
            if (mTypeY == Y_CONSTRAINT_TOP_SPAWN) { return gGame->mSpawnZoneTop; }
            if (mTypeY == Y_CONSTRAINT_TOP_PEEK) { return gGame->mPeekZoneTop; }
            if (mTypeY == Y_CONSTRAINT_TOP_QUARTER) { return gGame->mQuarterZoneTop; }
            if (mTypeY == Y_CONSTRAINT_CENTER) { return (gGame->mPlayAreaBottom + gGame->mPlayAreaTop) / 2.0f; }
            if (mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) { return gGame->mQuarterZoneBottom; }
            if (mTypeY == Y_CONSTRAINT_BOTTOM) { return gGame->mPlayAreaBottom; }
        }
    }
    return 0.0f;
}



