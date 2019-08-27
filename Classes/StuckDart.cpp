//
//  StuckDart.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "StuckDart.hpp"
#include "Dart.hpp"

StuckDart::StuckDart() {
    
    mDelete = false;
    
    mDart = NULL;
    mStartDartRotation = 0.0f;
    mStartReferenceRotation = 0.0f;
    mStartXDiff = 0.0f;
    mStartYDiff = 0.0f;
    
    mWaitTimer = 200 + gRand.Get(30);
    
    mFadeoutTime = 20;
    mFadeoutTimer = 0;
}

StuckDart::~StuckDart() {
    
}

void StuckDart::Update() {
    
    if (mWaitTimer > 0) {
        mWaitTimer--;
        return;
    }
    
    if (mDart == NULL) {
        mDelete = true;
        return;
    }
    
    mFadeoutTimer++;
    if (mFadeoutTimer >= mFadeoutTime) {
        mDart->Kill();
        mDart = NULL;
        mDelete = true;
        
        //.Update();
        
        
    } else {
        float aPercent = ((float)mFadeoutTimer) / ((float)mFadeoutTime);
        mDart->mTransform.mOffsetScale = (1.0f - aPercent);
        //mDart->mTransform.mOffsetRotation = aPercent * 360.0f;
        //mDart->mTransform.mOffsetY = aPercent * 30.0f;
    }
    
}

void StuckDart::Draw() {
    
    
}

