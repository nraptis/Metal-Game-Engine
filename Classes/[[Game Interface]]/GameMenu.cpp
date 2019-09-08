//
//  GameMenu.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/7/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameMenu.hpp"
#include "core_includes.h"
#include "GameContainer.hpp"
#include "Game.hpp"

GameMenu::GameMenu() {
    
    mOptionsButton = NULL;
    mMainMenuButton = NULL;
    mResumeButton = NULL;
    
    mName = "[Game Pause Menu]";
    
    //SetTransformAnchor(0.5f, 0.5f);
    
    mResumeButton = new FButton();
    AddChild(mResumeButton);
    mResumeButton->SetUp(&gWadGameInterface.mGameMenuGenericButtonUp, &gWadGameInterface.mGameMenuGenericButtonUp, &gWadGameInterface.mGameMenuGenericButtonDown);
    mResumeButton->AddOverlay(&gWadGameInterface.mGameMenuButtonTextResume);
    gNotify.Register(this, mResumeButton, "button_click");
    
    mOptionsButton = new FButton();
    AddChild(mOptionsButton);
    mOptionsButton->SetUp(&gWadGameInterface.mGameMenuGenericButtonUp, &gWadGameInterface.mGameMenuGenericButtonUp, &gWadGameInterface.mGameMenuGenericButtonDown);
    mOptionsButton->AddOverlay(&gWadGameInterface.mGameMenuButtonTextOptions);
    gNotify.Register(this, mOptionsButton, "button_click");
    
    mMainMenuButton = new FButton();
    AddChild(mMainMenuButton);
    mMainMenuButton->SetUp(&gWadGameInterface.mGameMenuGenericButtonUp, &gWadGameInterface.mGameMenuGenericButtonUp, &gWadGameInterface.mGameMenuGenericButtonDown);
    mMainMenuButton->AddOverlay(&gWadGameInterface.mGameMenuButtonTextMainMenu);
    gNotify.Register(this, mMainMenuButton, "button_click");
    
    
    
    
    
    //FButton                                     *mOptionsButton;
    //FButton                                     *mMainMenuButton;
    //FButton                                     *mResumeButton;
    
    
    
    //mGameMenuBack.Kill();
    
    //mGameMenuGenericButtonUp.Kill();
    //mGameMenuGenericButtonDown.Kill();
    
    //mGameMenuButtonTextMainMenu.Kill();
    //mGameMenuButtonTextLevelSelect.Kill();
    //mGameMenuButtonTextOkay.Kill();
    //mGameMenuButtonTextCancel.Kill();
    //mGameMenuButtonTextOptions.Kill();
    //mGameMenuButtonTextResume.Kill();
    
}

GameMenu::~GameMenu() {
    printf("GameMenu::~GameMenu()\n");
    
}

void GameMenu::Layout() {
    //float aWidth = gWadGameInterface.mGameMenuBack.mWidth + 20.0f;
    //float aHeight = gWadGameInterface.mGameMenuBack.mHeight + 20.0f;
    //SetFrame(-aWidth / 2.0f, -aHeight / 2.0f, aWidth, aHeight);
    
    float aWidgetWidth = gWadGameInterface.mGameMenuBack.mWidth + 20.0f;
    float aWidgetHeight = gWadGameInterface.mGameMenuBack.mHeight + 20.0f;
    
    float aButtonWidth = gWadGameInterface.mGameMenuGenericButtonUp.mWidth;
    float aButtonHeight = gWadGameInterface.mGameMenuGenericButtonUp.mHeight;
    
    if (mMainMenuButton != NULL) {
        mMainMenuButton->SetFrame(aWidgetWidth / 2.0f - aButtonWidth / 2.0f, aWidgetHeight - (aButtonHeight + 30.0f * gSpriteDrawScale), aButtonWidth, aButtonHeight);
    }
    
    if (mOptionsButton != NULL) {
        mOptionsButton->SetFrame(aWidgetWidth / 2.0f - aButtonWidth / 2.0f, aWidgetHeight - (aButtonHeight * 2.0f + 36.0f * gSpriteDrawScale), aButtonWidth, aButtonHeight);
    }
    
    if (mResumeButton != NULL) {
        mResumeButton->SetFrame(aWidgetWidth / 2.0f - aButtonWidth / 2.0f, aWidgetHeight - (aButtonHeight * 3.0f + 42.0f * gSpriteDrawScale), aButtonWidth, aButtonHeight);
    }
    
    
    
    //
    //mOptionsButton
    //mMainMenuButton
    
}

void GameMenu::Update() {
    
    if ((gGameContainer != NULL) && (gGameContainer->mPaused == true)) {
        return;
    }
}

void GameMenu::Draw() {
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor(0.6f);
    gWadGameInterface.mGameMenuBack.Center(mWidth2, mHeight2);
    Graphics::SetColor();
    
}

void GameMenu::TouchDown(float pX, float pY, void *pData) {
    
}

void GameMenu::TouchMove(float pX, float pY, void *pData) {
    
}

void GameMenu::TouchUp(float pX, float pY, void *pData) {
    
}

void GameMenu::TouchFlush() {
    
}

void GameMenu::Notify(void *pSender, const char *pNotification) {
    
    if (gGameContainer == NULL) {
        return;
    }
    
    
    if (gGameContainer->mGameMenuAnimation != NULL) {
        return;
    }
    
    if ((pSender == mOptionsButton) && (mOptionsButton != NULL)) {
        gGameContainer->UnpauseAndHideGameMenu();
    }
    
    if ((pSender == mResumeButton) && (mResumeButton != NULL)) {
        gGameContainer->UnpauseAndHideGameMenu();
    }
    
    if ((pSender == mMainMenuButton) && (mMainMenuButton != NULL)) {
        gGameContainer->UnpauseAndHideGameMenu();
    }
    
}

