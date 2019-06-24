//
//  GameTestOverlay.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameTestOverlay.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameTestOverlay *gGameTestOverlay = NULL;

GameTestOverlay::GameTestOverlay() {
    
    gGameTestOverlay = this;
    
    mName = "{{Game TEST Overlay}}";
}

GameTestOverlay::~GameTestOverlay() {

}

void GameTestOverlay::Layout() {
    
    /*
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
    */
    
}

void GameTestOverlay::Update() {
    
}

void GameTestOverlay::Draw() {
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    
    //Graphics::SetColor(1.0f, 1.0f, 0.25f, 0.25f);
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
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

void GameTestOverlay::TouchDown(float pX, float pY, void *pData) {
    
}

void GameTestOverlay::TouchMove(float pX, float pY, void *pData) {
    
}

void GameTestOverlay::TouchUp(float pX, float pY, void *pData) {
    
}

void GameTestOverlay::TouchFlush() {
    
}

void GameTestOverlay::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (pKey == __KEY__E) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    
}

void GameTestOverlay::KeyUp(int pKey) {
    
}

void GameTestOverlay::Notify(void *pSender, const char *pNotification) {
    
}
