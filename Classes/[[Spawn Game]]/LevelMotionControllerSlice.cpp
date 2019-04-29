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

LevelMotionControllerSliceOscillateGeneric::LevelMotionControllerSliceOscillateGeneric() {
    mOscillateSin = 0.0f;
    
    mIsPaused = false;
    mPauseSide = 0;
    mPauseTimer = 0;
    
    mLinearTimer = 90;
    mLinearTime = 180;
    mLinearDir = 1;
    
    mLinear = false;
    mPause1 = 0;
    mPause2 = 0;
}

LevelMotionControllerSliceOscillateGeneric::~LevelMotionControllerSliceOscillateGeneric() {
    
}

void LevelMotionControllerSliceOscillateGeneric::Update() {
    
    
    if (mPauseTimer > 0) {
        mPauseTimer -= 1;
        return;
    }
    
    if (mLinear == false) {
        
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
        
        mOscillateSin += aSpeed;
        if (mOscillateSin >= 360.0f) {
            mOscillateSin -= 360.0f;
            mPauseSide = 0;
        }
        if (mPauseSide == 0 && mPause1 > 0) {
            if (mOscillateSin >= 90.0f) {
                mOscillateSin = 90.0f;
                mPauseSide = 1;
                mPauseTimer = mPause1;
            }
        }
        if (mPauseSide == 1 && mPause2 > 0) {
            if (mOscillateSin >= 270.0f) {
                mOscillateSin = 270.0f;
                mPauseSide = 2;
                mPauseTimer = mPause2;
            }
        }
    } else {
        if (mLinearDir > 0) {
            mLinearTimer += 1;
            if (mLinearTimer >= mLinearTime) {
                mLinearDir = -1;
                mLinearTimer = mLinearTime;
                if (mPause1 > 0) {
                    mPauseTimer = mPause1;
                }
            }
        } else {
            mLinearTimer -= 1;
            if (mLinearTimer <= 0) {
                mLinearDir = 1;
                mLinearTimer = 0;
                if (mPause2 > 0) {
                    mPauseTimer = mPause2;
                }
            }
        }
    }
}

float LevelMotionControllerSliceOscillateGeneric::GetPercent() {
    
    if (mLinear == false) {
        float aSin = Sin(mOscillateSin);
        if (mSpeedNegateAlways == true) { aSin = -aSin; }
        else if (mSpeedNegateRandomly == true && mSpeedNegateRandomlyFlag == true) { aSin = -aSin; }
        return aSin;
    } else {
        
        if (mLinearTime > 0) {
            float aResult = -1.0f + ((float)mLinearTimer * 2.0f) / ((float)mLinearTime);
            
            //aResult = Clamp(aResult, -1.0f, 1.0f);
            
            if (mSpeedNegateAlways == true) { aResult = -aResult; }
            else if (mSpeedNegateRandomly == true && mSpeedNegateRandomlyFlag == true) { aResult = -aResult; }
            
            return aResult;
        }
        return 0.0f;
    }
    
    
}


//virtual void                        Update();

LevelMotionControllerSliceOscillateRotation::LevelMotionControllerSliceOscillateRotation() {
    mType = LEVEL_MOTION_SLICE_TYPE_OSCILLATE_ROTATION;
}

LevelMotionControllerSliceOscillateRotation::~LevelMotionControllerSliceOscillateRotation() {
    
}

void LevelMotionControllerSliceOscillateRotation::Apply(float pReferenceX, float pReferenceY, float *pX, float *pY) {
    if (pX != NULL && pY != NULL) {
        FVec2 aPos = FVec2(*pX, *pY);
        FVec2 aCenter = FVec2(pReferenceX, pReferenceY);
        aPos = PivotPoint(aPos, 60.0f, aCenter);
        *pX = aPos.mX;
        *pY = aPos.mY;
    }
    
}

void LevelMotionControllerSliceOscillateRotation::Update() {
    LevelMotionControllerSliceOscillateGeneric::Update();
    
}

LevelMotionControllerSliceOscillateVertical::LevelMotionControllerSliceOscillateVertical() {
    mType = LEVEL_MOTION_SLICE_TYPE_OSCILLATE_VERTICAL;
    mRadius = 32.0f;
}

LevelMotionControllerSliceOscillateVertical::~LevelMotionControllerSliceOscillateVertical() {
    
}

void LevelMotionControllerSliceOscillateVertical::Apply(float pReferenceX, float pReferenceY, float *pX, float *pY) {
    if (pX != NULL && pY != NULL) {
        
        *pX = *pX;
        *pY = *pY + GetPercent() * mRadius;
    }
}

void LevelMotionControllerSliceOscillateVertical::Update() {
    
    LevelMotionControllerSliceOscillateGeneric::Update();
    
}
