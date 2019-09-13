//
//  Transition.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Transition.hpp"
#include "GFXApp.hpp"

Transition::Transition() {
    
    mMode = TRANSITION_MODE_ANIMATE_IN;
    
    mModeTimeAnimateIn = 240;
    mModeTimeWaitIn = 80;
    mModeTimeSwap = 50;
    mModeTimeWaitOut = 80;
    mModeTimeAnimateOut = 250;
    
    
    mModeTimeAnimateIn = 32;
    mModeTimeWaitIn = 1;
    mModeTimeSwap = 1;
    mModeTimeWaitOut = 1;
    mModeTimeAnimateOut = 32;
    
    
    mTime = 100;
    mTimer = 0;
    mPercent = 0.0f;
}

Transition::~Transition() {
    printf("Transition::~Transition()\n");

}


void Transition::Layout() {
    
}

//virtual void                                Update() override;
//virtual void                                Draw() override;


void Transition::Update() {
    
    if (mMode == TRANSITION_MODE_COMPLETE) {
        return;
    }
    
    if (mMode == TRANSITION_MODE_PENDING) {
        mMode = TRANSITION_MODE_ANIMATE_IN;
        mTime = mModeTimeAnimateIn;
    }
    
    mTimer++;
    
    int aTime = mTime;
    if (aTime < 1) { aTime = 1; }
    
    mPercent = ((float)mTimer) / ((float)aTime);
    if (mPercent < 0.0f) { mPercent = 0.0f; }
    if (mPercent > 1.0f) { mPercent = 1.0f; }
    
    if (mTimer >= mTime) {
        mTimer = 0;
        
        if (mMode == TRANSITION_MODE_ANIMATE_IN) {
            mMode = TRANSITION_MODE_WAIT_IN;
            mTime = mModeTimeWaitIn;
            
        } else if (mMode == TRANSITION_MODE_WAIT_IN) {
            mMode = TRANSITION_MODE_SWAP;
            mTime = mModeTimeSwap;
            
        } else if (mMode == TRANSITION_MODE_SWAP) {
            mMode = TRANSITION_MODE_WAIT_OUT;
            mTime = mModeTimeWaitOut;
            gNotify.Post(this, "transition_swap");
            
        } else if (mMode == TRANSITION_MODE_WAIT_OUT) {
            mMode = TRANSITION_MODE_ANIMATE_OUT;
            mTime = mModeTimeAnimateOut;
            
        } else if (mMode == TRANSITION_MODE_ANIMATE_OUT) {
            mMode = TRANSITION_MODE_COMPLETE;
            mTime = 0;
            gNotify.Post(this, "transition_complete");
        }
    }
    
    if ((mMode == TRANSITION_MODE_SWAP) || (mMode == TRANSITION_MODE_WAIT_OUT) || (mMode == TRANSITION_MODE_WAIT_IN)) {
        mPercent = 1.0f;
    } else if (mMode == TRANSITION_MODE_ANIMATE_OUT) {
        mPercent = (1.0f - mPercent);
    }
}

void Transition::Draw() {
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.65f, 0.55f, 0.35f, mPercent);
    Graphics::DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
}
