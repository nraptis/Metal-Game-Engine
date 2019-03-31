//
//  GameFormationEditor.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameFormationEditor.hpp"
#include "GameEditor.hpp"
#include "FAnimation.h"

GameFormationEditor *gFormationEditor = NULL;

GameFormationEditor::GameFormationEditor(GameEditor *pEditor) {
    
    gFormationEditor = this;
    
    mEditor = pEditor;
    
    mGameAreaTop = pEditor->mGameAreaTop;
    mGameAreaRight = pEditor->mGameAreaRight;
    mGameAreaBottom = pEditor->mGameAreaBottom;
    mGameAreaLeft = pEditor->mGameAreaLeft;
    
    mCenterX = (float)((int)(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft) / 2.0f + 0.5f));
    mCenterY = (float)((int)(mGameAreaTop + (mGameAreaBottom - mGameAreaTop) / 2.0f + 0.5f));
    
    
    mFormation = NULL;
    mLoadedFormation = false;
    
    
    
    mName = "[GameFormationEditor]";
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    
    
    mMenuFormation = new EditorMenuFormation(this);
    AddChild(mMenuFormation);
    mMenuFormation->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 20.0f, 400.0f, 680.0f);
    
    mMenuUtils = new EditorMenuFormationUtilities(this);
    AddChild(mMenuUtils);
    mMenuUtils->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f), gSafeAreaInsetTop + 20.0f, 400.0f, 480.0f);
}

GameFormationEditor::~GameFormationEditor() {
    
    if (gFormationEditor == this) {
        gFormationEditor = NULL;
    }
    
    if (mFormation != NULL && mLoadedFormation == false) {
        delete mFormation;
        mFormation = NULL;
    }
    
    
    
    
}

void GameFormationEditor::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    FCanvas::SetFrame(pX, pY, pWidth, pHeight);
    
}

void GameFormationEditor::Layout() {
    
}

void GameFormationEditor::Update() {
    
    
}

void GameFormationEditor::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.7f, 0.25f, 0.085f, 0.75f);
    Graphics::DrawRect(0.0f, 0.0f, mGameAreaLeft, gDeviceHeight);
    Graphics::DrawRect(mGameAreaLeft, 0.0f, mGameAreaRight - mGameAreaLeft, mGameAreaTop);
    Graphics::DrawRect(mGameAreaLeft, mGameAreaBottom, mGameAreaRight - mGameAreaLeft, gDeviceHeight - mGameAreaBottom);
    Graphics::DrawRect(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft), 0.0f, gDeviceWidth - (mGameAreaLeft + (mGameAreaRight - mGameAreaLeft)), gDeviceHeight);
    
    
    
    
    
    
    
    
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.98f, 0.85f, 0.085f, 0.75f);
    Graphics::DrawPoint(mCenterX, mCenterY, 4.0f);
}

void GameFormationEditor::TouchDown(float pX, float pY, void *pData) {
    
    
}

void GameFormationEditor::TouchMove(float pX, float pY, void *pData) {

    
}

void GameFormationEditor::TouchUp(float pX, float pY, void *pData) {
    
    
}

void GameFormationEditor::TouchFlush() {
    
}

void GameFormationEditor::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (mFormation == NULL) { return; }
    if (gEditor == NULL) { return; }
    if (gGame == NULL) { return; }
    
    
    if (pKey == __KEY__P) {
        
    }
    
    
    if (pKey == __KEY__DELETE) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            
        }
    }
    
    if (pKey == __KEY__ESCAPE) {
        if (aShift == false && aCtrl == false && aAlt == false) { Close(); }
    }
    

    
        if (pKey == __KEY__LEFT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
            }
        }
        if (pKey == __KEY__RIGHT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
            }
        }
        if (pKey == __KEY__UP) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
            }
        }
        if (pKey == __KEY__DOWN) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
            }
        }
    
}

void GameFormationEditor::KeyUp(int pKey) {
    
}

void GameFormationEditor::Notify(void *pSender, const char *pNotification) {
    
}

void GameFormationEditor::Close() {
    mEditor->ClosePathEditor();
}

void GameFormationEditor::SetUp(LevelWaveSpawnFormation *pFormation) {
    
    if (gEditor != NULL) {
        mGameAreaTop = gEditor->mGameAreaTop;
        mGameAreaRight = gEditor->mGameAreaRight;
        mGameAreaBottom = gEditor->mGameAreaBottom;
        mGameAreaLeft = gEditor->mGameAreaLeft;
        
        mCenterX = (float)((int)(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft) / 2.0f + 0.5f));
        mCenterY = (float)((int)(mGameAreaTop + (mGameAreaBottom - mGameAreaTop) / 2.0f + 0.5f));
        
        
    }
    
    if (pFormation != NULL) {
        mLoadedFormation = true;
        mFormation = pFormation;
    } else {
        mLoadedFormation = false;
        mFormation = new LevelWaveSpawnFormation();
    }
}

void GameFormationEditor::Refresh() {
    
}

