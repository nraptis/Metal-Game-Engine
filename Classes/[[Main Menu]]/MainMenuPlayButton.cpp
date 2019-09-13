//
//  MainMenuPlayButton.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "MainMenuPlayButton.hpp"
#include "GFXApp.hpp"


MainMenuPlayButton::MainMenuPlayButton() {
    
    //mResumeButton = new FButton();
    //AddChild(mResumeButton);
    
    SetUp(&gWadGameInterface.mGameMenuGenericButtonUp, &gWadGameInterface.mGameMenuGenericButtonUp, &gWadGameInterface.mGameMenuGenericButtonDown);
    AddOverlay(&gWadGameInterface.mGameMenuButtonTextResume);
    
    
}

MainMenuPlayButton::~MainMenuPlayButton() {
    
}


void MainMenuPlayButton::Layout() {
    FButton::Layout();
    
}

void MainMenuPlayButton::Update() {
    FButton::Update();
    
}

void MainMenuPlayButton::Draw() {
    FButton::Draw();
    
}

void MainMenuPlayButton::TouchDown(float pX, float pY, void *pData) {
    FButton::TouchDown(pX, pY, pData);
    
}

void MainMenuPlayButton::TouchMove(float pX, float pY, void *pData) {
    FButton::TouchMove(pX, pY, pData);
    
}

void MainMenuPlayButton::TouchUp(float pX, float pY, void *pData) {
    FButton::TouchUp(pX, pY, pData);
    
}

void MainMenuPlayButton::TouchFlush() {
    FButton::TouchFlush();
    
}
