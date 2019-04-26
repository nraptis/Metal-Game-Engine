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

void LevelMotionControllerSliceRotate::Apply(float pReferenceX, float pReferenceY, GameObject *pObject) {
    
    
    if (pObject != NULL && pObject->mKill == 0) {
        
        
        FVec2 aPos = FVec2(pObject->mTransform.mX, pObject->mTransform.mY);
        FVec2 aCenter = FVec2(pReferenceX, pReferenceY);
        
        aPos = PivotPoint(aPos, mRotation, aCenter);
        
        pObject->mTransform.mX = aPos.mX;
        pObject->mTransform.mY = aPos.mY;
    }
    
}

void LevelMotionControllerSliceRotate::Update() {
    
    //mRotation
    
    
}

