//
//  StuckDart.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "StuckDart.hpp"
#include "Dart.hpp"
#include "Game.hpp"

StuckDart::StuckDart() {
    
    mDelete = false;
    
    mDidStartFadeout = false;
    
    mDart = NULL;
    mStartDartRotation = 0.0f;
    mStartReferenceRotation = 0.0f;
    mStartXDiff = 0.0f;
    mStartYDiff = 0.0f;
    
    mWaitTimer = 100 + gRand.Get(30);
    mWaitTimer = 500000;
    
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
    
    if (mDidStartFadeout == false) {
        mDidStartFadeout = true;
        gGame->StuckDartBeginFadeOut(mDart);
    }
    
    mFadeoutTimer++;
    if (mFadeoutTimer >= mFadeoutTime) {
        gGame->StuckDartFinishFadeOut(mDart);
        gGame->DisposeObject(mDart);
        
        mDart = NULL;
        mDelete = true;
    } else {
        float aPercent = ((float)mFadeoutTimer) / ((float)mFadeoutTime);
        mDart->mTransform.mOffsetScale = (1.0f - aPercent);
    }
}

void StuckDart::Draw() {
    
}

