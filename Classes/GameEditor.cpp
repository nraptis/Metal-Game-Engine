//
//  GameEditorEditor.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameEditor.hpp"
#include "FAnimation.h"

GameEditor *gEditor = NULL;

GameEditor::GameEditor(Game *pGame) {
    
    gEditor = this;
    mGame = pGame;
    
    mName = "[GameEditor]";
    gEditor = this;
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    mOverlay = NULL;
    
    mToolContainer = new FCanvas();
    mToolContainer->mName = "Tool Container";
    AddChild(mToolContainer);
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    mPathEditor = new GamePathEditor(this);
    mPathEditor->mName = "Path Editor";
    AddChild(mPathEditor);
    mPathEditor->Deactivate();
    
    mMenuSections = new EditorMenuSections(this);
    mToolContainer->AddChild(mMenuSections);
    mMenuSections->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 40.0f, 360.0f, 500.0f);
    
    
    
    
    SetOverlay(mToolContainer);
}

GameEditor::~GameEditor() {
    if (gEditor == this) {
        gEditor = NULL;
    }
}




void GameEditor::Layout() {
    
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mPathEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    FPoint aSpawnZone1 = FPoint(gGame->mSpawnZoneLeft, gGame->mSpawnZoneTop);
    aSpawnZone1 = FCanvas::Convert(aSpawnZone1, gGame, this);
    
    FPoint aSpawnZone2 = FPoint(gGame->mSpawnZoneRight, gGame->mSpawnZoneBottom);
    aSpawnZone2 = FCanvas::Convert(aSpawnZone2, gGame, this);
    
    mSpawnZoneTop = aSpawnZone1.mY;
    mSpawnZoneRight = aSpawnZone2.mX;
    mSpawnZoneLeft = aSpawnZone1.mX;
    mSpawnZoneBottom = aSpawnZone2.mY;
}

void GameEditor::Update() {
    
}

void GameEditor::Draw() {
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor();
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor(1.0f, 0.0f, 0.0f);
    
    Graphics::PipelineStateSetShape2DNoBlending();
    Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 2.0f);

    
    
    
    
    
    Graphics::DrawLine(mSpawnZoneLeft, mSpawnZoneTop, mSpawnZoneRight, mSpawnZoneTop);
    Graphics::DrawLine(mSpawnZoneLeft, mSpawnZoneTop, mSpawnZoneLeft, mSpawnZoneBottom);
    Graphics::DrawLine(mSpawnZoneRight, mSpawnZoneTop, mSpawnZoneRight, mSpawnZoneBottom);
    
    
    
    
    
    
    
    
}

void GameEditor::TouchDown(float pX, float pY, void *pData) {
    
    if (gRand.GetBool()) {
        gApp->mSound1.Play();
    } else {
        gApp->mSound2.Play();
    }
    
    FPoint aPos = FPoint(pX, pY);
    aPos = FCanvas::Convert(aPos, this, gGame);
    gGame->mEditorCursorX = aPos.mX;
    gGame->mEditorCursorY = aPos.mY;
    
    
}

void GameEditor::TouchMove(float pX, float pY, void *pData) {
    
}

void GameEditor::TouchUp(float pX, float pY, void *pData) {

    
}

void GameEditor::TouchFlush() {
    
}

void GameEditor::KeyDown(int pKey) {
    
}

void GameEditor::KeyUp(int pKey) {
    
}

void GameEditor::Notify(void *pSender, const char *pNotification) {
    if (FString("slider_update") == pNotification) {
        
    }
    if (FString("button_click") == pNotification) {

        
    }
}

void GameEditor::Load() {
    
}

void GameEditor::SetOverlay(FCanvas *pCanvas) {
    
    if (mOverlay) {
        if (mOverlay == pCanvas) {
            return;
        }
        
        mOverlay->Deactivate();
        mOverlay = NULL;
        //mOverlay->
    }
    if (pCanvas) {
        mOverlay = pCanvas;
        mOverlay->Activate();
    }
    
}

void GameEditor::OpenPathEditor() {
    SetOverlay(mPathEditor);
}

void GameEditor::ClosePathEditor() {
    SetOverlay(mToolContainer);
}




