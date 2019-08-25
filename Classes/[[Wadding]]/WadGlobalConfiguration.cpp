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
