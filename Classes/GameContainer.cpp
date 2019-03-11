//
//  GameContainerContainer.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//
#include "core_includes.h"
#include "GameContainer.hpp"
#include "FAnimation.h"
#include "Game.hpp"

GameContainer *gGameContainer = NULL;

GameContainer::GameContainer() {
    
    
    SetWidth(1000.0f);
    SetHeight(1000.0f);
    
    mContainer = new FCanvas();
    //mContainer->mColor = FColor(0.25f, 1.0f, 1.0f);
    mContainer->SetTransformAnchor(0.5f, 0.5f);
    //mContainer->SetTransformRotation(2.0f);
    
    AddChild(mContainer);
    
    
    mGame = new Game();
    mContainer->AddChild(mGame);
    
}

GameContainer::~GameContainer() {
    if (gGameContainer == this) {
        gGameContainer = NULL;
    }
    
    if (mGame) {
        delete mGame;
        mGame = NULL;
    }
    
}

void GameContainer::Layout() {

    if (mGame != NULL && mContainer != NULL) {
        
        float aScale = 1.0f;
        float aGameAreaWidth = mWidth - 20.0f;
        float aGameAreaHeight = mHeight - 20.0f;
        FRect aFrame = FRect(0.0f, 0.0f, aGameAreaWidth, aGameAreaHeight);
        FRect aFit = FRect::FitAspectFit(aFrame, mGame->mWidth, mGame->mHeight, 0.0f, aScale);
        float aContainerWidth = round(aGameAreaWidth / aScale);
        float aContainerHeight = round(aGameAreaHeight / aScale);
        mContainer->SetTransformScale(aScale);
        mContainer->SetFrame(round(-(aContainerWidth / (2.0f))), - round((aContainerHeight / (2.0f))), aContainerWidth, aContainerHeight);
        mContainer->SetTransformTranslate(mWidth2, mHeight2);
        float aGameX = round(mContainer->mWidth2 - mGame->mWidth2);
        float aGameY = round(mContainer->mHeight2 - mGame->mHeight2);
        mGame->SetX(aGameX);
        mGame->SetY(aGameY);
        
    }
    
    //float aWidth = mWidth;
    
    
    
}

void GameContainer::Update() {
    
}

void GameContainer::Draw() {
    
}

void GameContainer::Draw3D() {
    if (mGame) {
        mGame->Draw3D();
    }
    
}

void GameContainer::TouchDown(float pX, float pY, void *pData) {
    
}

void GameContainer::TouchMove(float pX, float pY, void *pData) {
    
}

void GameContainer::TouchUp(float pX, float pY, void *pData) {
    
}

void GameContainer::TouchFlush() {
    
}

void GameContainer::KeyDown(int pKey) {
    
}

void GameContainer::KeyUp(int pKey) {
    
}

void GameContainer::Notify(void *pSender, const char *pNotification) {
    
}

