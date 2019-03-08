//
//  LevelSelectorScreen.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "LevelSelectorScreen.hpp"
#include "core_includes.h"
#include "LightConfigurationScene.hpp"

LevelSelectorScreen::LevelSelectorScreen() {
    
    float aWidth = gDeviceWidth;
    float aHeight = gDeviceHeight * 0.75f;
    
    mScrollEnabledVertical = false;
    mScrollEnabledHorizontal = false;
    
    mPage1 = new LightConfigurationScene();
    //mPage1->mColor = FColor(1.0f, 0.0f, 0.25f, 0.0f);
    mPage1->SetFrame(0.0f, 0.0f, aWidth, gDeviceHeight);
    mPage1->mConsumesTouches = false;
    AddChild(mPage1);
    
    mPage2 = new FCanvas();
    //mPage2->mColor = FColor(0.0f, 1.0f, 0.25f, 0.25f);
    mPage2->SetFrame(aWidth, 0.0f, aWidth, aHeight);
    mPage2->mConsumesTouches = false;
    AddChild(mPage2);
    
    mPage3 = new FCanvas();
    //mPage3->mColor = FColor(0.25f, 0.0f, 1.0f, 0.77f);
    mPage3->SetFrame(aWidth * 2.0, 0.0f, aWidth, aHeight);
    mPage3->mConsumesTouches = false;
    AddChild(mPage3);
    
    SetPageCount(3, 1);
}

LevelSelectorScreen::~LevelSelectorScreen() {
    
    
}




