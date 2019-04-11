//
//  GameContainerContainer.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//
#include "core_includes.h"
#include "GameContainer.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameContainer *gGameContainer = NULL;

GameContainer::GameContainer() {
    
    mName = "{{Game Container}}";
    
    
    SetWidth(1000.0f);
    SetHeight(1000.0f);
    
    mInterfaceLeftWidth = 4.0f;
    mInterfaceRightWidth = 4.0f;
    mInterfaceTopHeight = 4.0f;
    mInterfaceBottomHeight = 12.0f;
    
    mContainer = new FCanvas();
    //mContainer->mColor = FColor(0.25f, 1.0f, 1.0f, 0.66f);
    mContainer->SetTransformAnchor(0.5f, 0.5f);
    //mContainer->SetTransformRotation(2.0f);
    
    AddChild(mContainer);
    mContainer->mName = "{Container}";
    
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
        float aGameAreaWidth = mWidth - (mInterfaceLeftWidth + mInterfaceRightWidth);
        float aGameAreaHeight = mHeight - (mInterfaceTopHeight + mInterfaceBottomHeight);
        
        FRect aFrame = FRect(0.0f, 0.0f, aGameAreaWidth, aGameAreaHeight);
        FRect aFit = FRect::FitAspectFit(aFrame, mGame->mWidth, mGame->mHeight, 0.0f, aScale);
        float aContainerWidth = round(aGameAreaWidth / aScale);
        float aContainerHeight = round(aGameAreaHeight / aScale);
        mContainer->SetTransformScale(aScale);
        mContainer->SetFrame(round(-(aContainerWidth / (2.0f))), - round((aContainerHeight / (2.0f))), aContainerWidth, aContainerHeight);
        //mContainer->SetTransformTranslate(mWidth2 + mInterfaceLeftWidth * aScale, mHeight2 + mInterfaceTopHeight * aScale);
        
        //mContainer->SetTransformTranslate(mWidth2, mHeight2);
        
        mContainer->SetTransformTranslate(mWidth2 - (mInterfaceRightWidth - mInterfaceLeftWidth) / 2.0f, mHeight2 - (mInterfaceBottomHeight - mInterfaceTopHeight) / 2.0f);
        
        mGame->mRenderShiftX = -((mInterfaceRightWidth - mInterfaceLeftWidth) / 2.0f) / aScale;
        mGame->mRenderShiftY = -((mInterfaceBottomHeight - mInterfaceTopHeight) / 2.0f) / aScale;
        
        
        float aGameX = round(mContainer->mWidth2 - mGame->mWidth2);
        float aGameY = round(mContainer->mHeight2 - mGame->mHeight2);
        mGame->SetX(aGameX);
        mGame->SetY(aGameY);
        
        
        
        
        
    }
}

void GameContainer::Update() {
    
}

void GameContainer::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    
    /*
    Graphics::SetColor(1.0f, 0.0f, 0.25f, 0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mInterfaceLeftWidth, mHeight);
    
    Graphics::SetColor(0.0f, 0.125f, 1.0f, 0.25f);
    Graphics::DrawRect(mWidth - mInterfaceRightWidth, 0.0f, mInterfaceRightWidth, mHeight);
    

    
    Graphics::SetColor(0.5f, 0.75f, 0.5f, 0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mInterfaceTopHeight);
    
    Graphics::SetColor(1.0f, 0.5f, 0.0f, 0.25f);
    Graphics::DrawRect(0.0f, mHeight - mInterfaceBottomHeight, mWidth, mInterfaceBottomHeight);
    */
     
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

