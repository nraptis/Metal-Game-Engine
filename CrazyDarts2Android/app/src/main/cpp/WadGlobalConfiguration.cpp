//
//  WadGlobalConfiguration.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "WadGlobalConfiguration.hpp"
#include "core_includes.h"

WadGlobalConfiguration gWadConfiguration;

WadGlobalConfiguration::WadGlobalConfiguration() {

    mAssetScale = 1;
    mPrevAssetScale = 0;
    
    mSpriteScale = 1;
    mPrevSpriteScale = 0;
    
    mAutoScale = true;
}

WadGlobalConfiguration::~WadGlobalConfiguration() {
    
}

bool WadGlobalConfiguration::ShouldReload() {
    
    if (mSpriteScale != mPrevSpriteScale) { return true; }
    if (mAssetScale != mPrevAssetScale) { return true; }
    
    return false;
    
}

void WadGlobalConfiguration::NotifyReload() {
    mPrevAssetScale = mAssetScale;
    mPrevSpriteScale = mSpriteScale;
}

void WadGlobalConfiguration::NotifyVirtualFrameChange() {
    
    float aScreenWidth = gVirtualDevWidth;
    if (aScreenWidth < 100.0f) { aScreenWidth = 100.0f; }
    
    //TODO: This will be the magic number that determines our scale...
    float aExampleImageWidth = 400.0f;
    
    float aExpectScale = aScreenWidth / (aExampleImageWidth);
    int aScale = (int)(floorf(aExpectScale));
    
    printf("WadGlobalConfiguration::Expect Scale: %d (%f) VD(%f x %f)\n", aScale, aExpectScale, gVirtualDevWidth, gVirtualDevHeight);
    
    if (aScale < 1) { aScale = 1; }
    if (aScale > 4) { aScale = 4; }
    
    if (mAutoScale) {
        mSpriteScale = aScale;
        mAssetScale = os_getAssetScale();
        if (mAssetScale < mSpriteScale) {
            mAssetScale = mSpriteScale;
        }
    }
    
    if (mAssetScale != mPrevAssetScale) {
        printf("WadGlobalConfiguration::UPDATE Asset Scale: %d\n", mAssetScale);
    }
    
    if (mSpriteScale != mPrevSpriteScale) {
        printf("WadGlobalConfiguration::UPDATE Asset Scale: %d\n", mSpriteScale);
    }
    
}
                                                      

void WadGlobalConfiguration::SetAssetScale(int pScale) {
    mAssetScale = pScale;
}

void WadGlobalConfiguration::SetSpriteScale(int pScale) {
    mSpriteScale = pScale;
}

void WadGlobalConfiguration::Print() {
    Log("*** BEGIN WadGlobalConfiguration ***\n");
    
    
    
    Log("*** END WadGlobalConfiguration ***\n");
}
