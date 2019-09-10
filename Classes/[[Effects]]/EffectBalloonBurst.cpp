//
//  EffectBalloonBurst.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EffectBalloonBurst.hpp"
#include "GFXApp.hpp"

EffectBalloonBurst::EffectBalloonBurst() {
    
    mMainMode = 0;
    mMainKill = 0;
    mMainScale = 0.5f;
    mMainScaleSpeed = 0.17f;
    mMainScaleDownAccel = 0.0f;
    mMainRotation = gRand.GetFloat(-4.0f, 4.0f);
    mMainRotationSpeed = gRand.GetFloat(0.4f, 0.525f, true);
    mMainRotationAccel = 0.825f;
    
    
    for (int i=0;i<BALLOON_BURST_SLICE_COUNT;i++) {
        
        mSliceKill[i] = 0;
        
        mSliceOffsetX[i] = gRand.GetFloat(-1.0f, 1.0f) * gSpriteDrawScale;
        mSliceOffsetY[i] = gRand.GetFloat(-1.0f, 1.0f) * gSpriteDrawScale;
        mSliceRotation[i] = gRand.GetFloat(15.0f, 75.0f);
        mSliceScale[i] = 0.25f;
        mSliceScaleSpeed[i] = 1.0f;
        
        
    }
    
   
    
    
}

EffectBalloonBurst::~EffectBalloonBurst() {
    
    
}

void EffectBalloonBurst::Update() {
    
    mMainRotation += mMainRotationSpeed;
    mMainRotationSpeed *= mMainRotationAccel;
    
    if (mMainMode == 0) {
        
        mMainScale += mMainScaleSpeed;
        mMainScaleSpeed -= 0.013f;
        if (mMainScaleSpeed <= 0.0f) {
            mMainMode = 1;
            mMainScaleSpeed = 0.0f;
        }
    } else {
        
        mMainScale += mMainScaleSpeed;
        
        mMainScaleSpeed -= mMainScaleDownAccel;
        mMainScaleDownAccel += 0.0002f;
        
        if (mMainScale <= 0.0f) {
            mMainScale = 0.0f;
            mMainKill = 1;
        }
    }
    
    
    int aSliceSeed = gRand.Get(3);
    
    float aSliceRotation = gRand.GetFloat(15.0f, 75.0f);
    float aSliceRotationOffset = 0.0f;
    if (aSliceSeed == 1) {
        aSliceRotationOffset = 90.0f;
    }
    if (aSliceSeed == 2) {
        aSliceRotationOffset = 180.0f;
    }
    
    
    
    for (int i=0;i<BALLOON_BURST_SLICE_COUNT;i++) {
        
        
        mSliceRotation[i] = fmodf(aSliceRotation + aSliceRotationOffset, 360.0f);
        
        aSliceRotation += gRand.GetFloat(15.0f, 30.0f);
        if (aSliceRotation > 75.0f) { aSliceRotation -= (75.0f - 15.0f); }
    }
    
    
    for (int i=0;i<BALLOON_BURST_SLICE_COUNT;i++) {
        
        
    }
    
    if (mMainKill != 0) {
        
    }
    
}


void EffectBalloonBurst::Draw() {
    
    if (mMainKill == 0) {
        gWadGameEffects.mBalloonPopMark.Draw(mX, mY, mMainScale, mMainRotation);
        for (int i=0;i<BALLOON_BURST_SLICE_COUNT;i++) {
            if (mSliceKill[i] == 0) {
                gWadGameEffects.mBalloonPopMarkSmall.Draw(mX + mSliceOffsetX[i], mY + mSliceOffsetY[i], mMainScale,  mSliceRotation[i]);
            }
        }
    }
    
    
    
    
    
}


