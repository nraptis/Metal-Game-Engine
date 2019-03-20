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
    
    mCurrentSection = new LevelSectionBlueprint();
    
    
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
    
    
    WaveAdd();
    
    //OpenPathEditor();
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
    
    
    FPoint aPeekZone1 = FPoint(gGame->mPeekZoneLeft, gGame->mPeekZoneTop);
    aPeekZone1 = FCanvas::Convert(aPeekZone1, gGame, this);
    FPoint aPeekZone2 = FPoint(gGame->mPeekZoneRight, gGame->mPeekZoneBottom);
    aPeekZone2 = FCanvas::Convert(aPeekZone2, gGame, this);
    mPeekZoneTop = aPeekZone1.mY;
    mPeekZoneRight = aPeekZone2.mX;
    mPeekZoneLeft = aPeekZone1.mX;
    mPeekZoneBottom = aPeekZone2.mY;
    
    
    
    FPoint aQuarterZone1 = FPoint(gGame->mQuarterZoneLeft, gGame->mQuarterZoneTop);
    aQuarterZone1 = FCanvas::Convert(aQuarterZone1, gGame, this);
    FPoint aQuarterZone2 = FPoint(gGame->mQuarterZoneRight, gGame->mQuarterZoneBottom);
    aQuarterZone2 = FCanvas::Convert(aQuarterZone2, gGame, this);
    mQuarterZoneTop = aQuarterZone1.mY;
    mQuarterZoneRight = aQuarterZone2.mX;
    mQuarterZoneLeft = aQuarterZone1.mX;
    mQuarterZoneBottom = aQuarterZone2.mY;
    
    
    
    FPoint aPlayZone = FPoint(gGame->mPlayAreaTop, gGame->mPlayAreaBottom);
    aPlayZone = FCanvas::Convert(aPlayZone, gGame, this);
    mPlayZoneBottom = aPlayZone.mY;
    
    FPoint aCenter = FPoint((gGame->mPlayAreaLeft + gGame->mPlayAreaRight) / 2.0f,
                            (gGame->mPlayAreaTop + gGame->mPlayAreaBottom) / 2.0f);
    aCenter = FCanvas::Convert(aCenter, gGame, this);
    mCenterH = aCenter.mX;
    mCenterV = aCenter.mY;
    
    
    
    
    
    
    
}

void GameEditor::Update() {
    
}

void GameEditor::Draw() {
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor();
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    

    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    
    float aMarkerMult = 1.0f;
    float aMarkerOpacity = 1.0f;
    
    Graphics::SetColor(1.0f * aMarkerMult, 0.0f * aMarkerMult, 0.0f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mSpawnZoneLeft, mSpawnZoneTop, mSpawnZoneRight, mSpawnZoneTop);
    Graphics::DrawLine(mSpawnZoneLeft, mSpawnZoneTop, mSpawnZoneLeft, mSpawnZoneBottom);
    Graphics::DrawLine(mSpawnZoneRight, mSpawnZoneTop, mSpawnZoneRight, mSpawnZoneBottom);
    
    Graphics::SetColor(0.65f * aMarkerMult, 0.45f * aMarkerMult, 0.75f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mPeekZoneLeft, mPeekZoneTop, mPeekZoneRight, mPeekZoneTop);
    Graphics::DrawLine(mPeekZoneLeft, mPeekZoneTop, mPeekZoneLeft, mPeekZoneBottom);
    Graphics::DrawLine(mPeekZoneRight, mPeekZoneTop, mPeekZoneRight, mPeekZoneBottom);
    
    Graphics::SetColor(0.25f * aMarkerMult, 0.25f * aMarkerMult, 0.25f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mCenterH, mSpawnZoneTop, mCenterH, mSpawnZoneBottom);
    Graphics::DrawLine(mSpawnZoneLeft, mCenterV, mSpawnZoneRight, mCenterV);
    
    
    Graphics::SetColor(1.0f * aMarkerMult, 1.0f * aMarkerMult, 0.015f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneTop, mQuarterZoneRight, mQuarterZoneTop);
    Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneBottom, mQuarterZoneRight, mQuarterZoneBottom);
    Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneTop, mQuarterZoneLeft, mQuarterZoneBottom);
    Graphics::DrawLine(mQuarterZoneRight, mQuarterZoneTop, mQuarterZoneRight, mQuarterZoneBottom);

    
    
    
    Graphics::SetColor();
    
    if (mCurrentSection) {
        mCurrentSection->Draw();
    }
    
    
    
    
    
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
    
    if (pKey == __KEY__W) {
        
    }
    
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

void GameEditor::WaveAdd() {
    if (mCurrentSection == NULL) { printf("Must have mCurrentSection...\n"); return; }
    mCurrentSection->WaveAdd();
    OpenPathEditor();
}

void GameEditor::WaveRemove() {
    if (mCurrentSection == NULL) { printf("Must have mCurrentSection...\n"); return; }
    mCurrentSection->WaveRemove();
}

void GameEditor::WaveSelectNext() {
    if (mCurrentSection == NULL) { printf("Must have mCurrentSection...\n"); return; }
    mCurrentSection->WaveSelectNext();
}

void GameEditor::WaveSelectPrev() {
    if (mCurrentSection == NULL) { printf("Must have mCurrentSection...\n"); return; }
    mCurrentSection->WaveSelectPrev();
}

void GameEditor::WaveDeselect() {
    if (mCurrentSection == NULL) { printf("Must have mCurrentSection...\n"); return; }
    mCurrentSection->WaveDeselect();
}

void GameEditor::OpenPathEditor() {
    if (mCurrentSection == NULL) { printf("Must have mCurrentSection...\n"); return; }
    if (mCurrentSection->mCurrentWave == NULL) { printf("Must have wave...\n"); return; }
    
    mPathEditor->SetUp(mCurrentSection->mCurrentWave);
    
    SetOverlay(mPathEditor);
}

void GameEditor::ClosePathEditor() {
    SetOverlay(mToolContainer);
}




