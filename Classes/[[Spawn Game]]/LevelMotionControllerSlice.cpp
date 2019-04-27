//
//  LevelMotionControllerSlice.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelMotionControllerSlice.hpp"
#include "LevelPath.hpp"
#include "FMath.hpp"

LevelMotionControllerSlice::LevelMotionControllerSlice() {
    mType = LEVEL_MOTION_SLICE_TYPE_NONE;
    mSpeedClass = SPEED_CLASS_MEDIUM;
    
    mSpeedNegateAlways = false;
    mSpeedNegateRandomly = false;
    
    mSpeedNegateRandomlyFlag = gRand.GetBool();
    
    mKillTimer = 8;
}

LevelMotionControllerSlice::~LevelMotionControllerSlice() {
    
}

LevelMotionControllerSliceRotate::LevelMotionControllerSliceRotate() {
    mType = LEVEL_MOTION_SLICE_TYPE_ROTATE;
    
    mPivotOffsetX = 0.0f;
    mPivotOffsetY = 0.0f;
    
    mRotation = 0.0f;
    
}

LevelMotionControllerSliceRotate::~LevelMotionControllerSliceRotate() {
    
}

void LevelMotionControllerSliceRotate::Apply(float pReferenceX, float pReferenceY, float *pX, float *pY) {
    
    if (pX != NULL && pY != NULL) {
        
        FVec2 aPos = FVec2(*pX, *pY);
        FVec2 aCenter = FVec2(pReferenceX + mPivotOffsetX, pReferenceY + mPivotOffsetY);
        
        aPos = PivotPoint(aPos, mRotation, aCenter);
        
        *pX = aPos.mX;
        *pY = aPos.mY;
    }
    
}

void LevelMotionControllerSliceRotate::Update() {
    
    
    float aSpeed = 1.0f;
    
    if (mSpeedClass == SPEED_CLASS_EXTRA_SLOW) {
        aSpeed = 0.25f;
    } else if (mSpeedClass == SPEED_CLASS_SLOW) {
        aSpeed = 0.35f;
    } else if (mSpeedClass == SPEED_CLASS_MEDIUM_SLOW) {
        aSpeed = 0.60f;
    } else if (mSpeedClass == SPEED_CLASS_MEDIUM_FAST) {
        aSpeed = 1.5f;
    } else if (mSpeedClass == SPEED_CLASS_FAST) {
        aSpeed = 2.25f;
    } else if (mSpeedClass == SPEED_CLASS_EXTRA_FAST) {
        aSpeed = 3.0f;
    } else if (mSpeedClass == SPEED_CLASS_INSANE) {
        aSpeed = 5.5f;
    }
    
    if (mSpeedNegateAlways == true) {
        aSpeed = -fabsf(aSpeed);
    }
    
    if (mSpeedNegateRandomly == true && mSpeedNegateRandomlyFlag == true) {
        aSpeed = -fabsf(aSpeed);
    }
    
    mRotation += aSpeed;
    if (mRotation >= 360.0f) { mRotation -= 360.0f; }
    if (mRotation < 0.0f) { mRotation += 360.0f; }
    
}

