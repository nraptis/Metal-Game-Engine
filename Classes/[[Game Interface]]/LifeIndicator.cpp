//
//  LifeIndicator.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/3/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LifeIndicator.hpp"
#include "core_includes.h"
#include "GFXApp.hpp"

LifeIndicator::LifeIndicator() {
    mConsumesTouches = false;
    mFull = false;
}

LifeIndicator::~LifeIndicator() {
    
}

void LifeIndicator::Update() {
    
}

void LifeIndicator::Draw() {
    
    FCanvas::Draw();
    
    Graphics::SetColor();
    Graphics::PipelineStateSetSpriteAlphaBlending();
    
    gWadGameInterface.mLivesIndicatorShadow.Draw(mWidth2, mHeight2, 1.0f, 0.0f);
    
    if (mFull) {
        gWadGameInterface.mLivesIndicatorFull.Draw(mWidth2, mHeight2, 1.0f, 0.0f);
    } else {
        gWadGameInterface.mLivesIndicatorEmpty.Draw(mWidth2, mHeight2, 1.0f, 0.0f);
    }
}

void LifeIndicator::BecomeFull() {
    
    //TODO: We want some kind of animation..
    
    printf("Life Inf, BECOME FULL\n");
    mFull = true;
}

void LifeIndicator::BecomeEmpty() {
    printf("Life Inf, BECOME EMPTY\n");
    mFull = false;
}
