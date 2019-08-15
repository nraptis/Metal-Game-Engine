//
//  GameTestEditorOverlay.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameTestEditorOverlay.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameTestEditorOverlay *gGameTestEditorOverlay = NULL;

GameTestEditorOverlay::GameTestEditorOverlay() {
    
    gGameTestEditorOverlay = this;
    
    mName = "{{Game TEST Overlay}}";
}

GameTestEditorOverlay::~GameTestEditorOverlay() {
    
}

void GameTestEditorOverlay::Layout() {
    if (mParent != NULL) {
        SetFrame(0.0f, 0.0f, mParent->mWidth, mParent->mHeight);
    }
}

void GameTestEditorOverlay::Update() {
    
}

void GameTestEditorOverlay::Draw() {
    
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

void GameTestEditorOverlay::TouchDown(float pX, float pY, void *pData) {
    
}

void GameTestEditorOverlay::TouchMove(float pX, float pY, void *pData) {
    
}

void GameTestEditorOverlay::TouchUp(float pX, float pY, void *pData) {
    
}

void GameTestEditorOverlay::TouchFlush() {
    
}

void GameTestEditorOverlay::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (pKey == __KEY__E) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    
}

void GameTestEditorOverlay::KeyUp(int pKey) {
    
}

void GameTestEditorOverlay::Notify(void *pSender, const char *pNotification) {
    
}
