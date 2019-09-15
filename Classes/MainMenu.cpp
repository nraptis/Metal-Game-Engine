//
//  MainMenu.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "MainMenu.hpp"


//
//  MainMenuContainer.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//
#include "core_includes.h"
#include "MainMenu.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"
#include "GameEditor.hpp"

MainMenu *gMainMenu = NULL;

MainMenu::MainMenu() {
    
    gMainMenu = this;
    mPlayButton = NULL;
    mName = "(( ~ Main Menu ~ ))";
    
    
    
    mPlayButton = new MainMenuPlayButton();
    AddChild(mPlayButton);
    gNotify.Register(this, mPlayButton, "button_click");
    
    
    
}

MainMenu::~MainMenu() {
    
    if (gMainMenu == this) {
        gMainMenu = NULL;
    }
    
}

void MainMenu::Layout() {
    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    if (mPlayButton != NULL) {
        
        float aButtonWidth = mPlayButton->mWidth;
        float aButtonHeight = mPlayButton->mHeight;
        mPlayButton->SetFrame(mWidth2 - aButtonWidth / 2.0f, mHeight2 - aButtonHeight / 2.0f, aButtonWidth, aButtonHeight);
    }
    
    
    
}

void MainMenu::Update() {
    
}

void MainMenu::Draw() {
    
    
    
    //DrawTransform();
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(gRand.GetFloat(0.03f), gRand.GetFloat(0.03f), 0.65f, 0.75f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    Graphics::SetColor();
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    gWadModels.mDartRegularMap[0].DrawQuadRect(0.0f, 0.0f, mWidth, mHeight);
    
}

void MainMenu::Draw3D() {
    
}

void MainMenu::TouchDown(float pX, float pY, void *pData) {
    
}

void MainMenu::TouchMove(float pX, float pY, void *pData) {
    
}

void MainMenu::TouchUp(float pX, float pY, void *pData) {
    
}

void MainMenu::TouchFlush() {
    
}

void MainMenu::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    
    
}

void MainMenu::KeyUp(int pKey) {
    
}

void MainMenu::Notify(void *pSender, const char *pNotification) {
    
    if (pSender == mPlayButton) {
        
        printf("PLAY BUTTON CLICKED!!!\n");
        
        if (gApp->TransitionAllowed()) {
            gApp->TransitionToGame();
        }
        
        
    }
    
}
