//
//  GamePathEditor.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//


#include "core_includes.h"
#include "GamePathEditor.hpp"
#include "GameEditor.hpp"
#include "FAnimation.h"

GamePathEditor::GamePathEditor(GameEditor *pEditor) {
    
    mEditor = pEditor;
    
    
    mPathMode = PATH_MODE_EDIT;
    
    mSelectedIndex = 1;
    mSelectedTouch = NULL;
    
    mName = "[GamePathEditor]";
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    
    mSelectPathStartX = 0.0f;
    mSelectPathStartY = 0.0f;
    
    mSelectTouchStartX = 0.0f;
    mSelectTouchStartY = 0.0f;
    
    
    
    mMenuPaths = new EditorMenuPath(this);
    AddChild(mMenuPaths);
    mMenuPaths->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 40.0f, 360.0f, 500.0f);
    
    
    mMenuControls = new EditorMenuPathControl(this);
    AddChild(mMenuControls);
    mMenuControls->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 16.0f + 360.0f), gSafeAreaInsetTop + 40.0f, 360.0f, 108.0f);
    mMenuControls->mResizeDragAllowed = false;
    
}

GamePathEditor::~GamePathEditor() {
    
}



void GamePathEditor::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    FCanvas::SetFrame(pX, pY, pWidth, pHeight);
    
}

void GamePathEditor::Layout() {
    
    FPoint aSpawnZone1 = FPoint(gGame->mSpawnZoneLeft, gGame->mSpawnZoneTop);
    aSpawnZone1 = FCanvas::Convert(aSpawnZone1, gGame, this);
    
    FPoint aSpawnZone2 = FPoint(gGame->mSpawnZoneRight, gGame->mSpawnZoneBottom);
    aSpawnZone2 = FCanvas::Convert(aSpawnZone2, gGame, this);
    
    mSpawnZoneTop = aSpawnZone1.mY;
    mSpawnZoneRight = aSpawnZone2.mX;
    mSpawnZoneLeft = aSpawnZone1.mX;
    mSpawnZoneBottom = aSpawnZone2.mY;
}

void GamePathEditor::Update() {
    
}

void GamePathEditor::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    
    Graphics::SetColor(0.6f, 0.6f, 0.6f, 0.5f);
    mPath.DrawEdgesOpen(1.0f);
    
    Graphics::SetColor(0.85f, 0.85f, 0.85f, 0.5f);
    for (int i=0;i<mPath.mCount;i++) {
        if (i == mSelectedIndex) {
            Graphics::DrawPoint(mPath.mX[i], mPath.mY[i], 8.0f);
        } else {
            Graphics::DrawPoint(mPath.mX[i], mPath.mY[i], 4.0f);
        }
    }
    
    for (int i=0;i<mPath.mCount;i++) {
        if (i == mSelectedIndex) {
            Graphics::SetColor(0.985f, 0.945f, 0.125f, 0.5f);
            Graphics::DrawPoint(mPath.mX[i], mPath.mY[i], 6.0f);
        } else {
            Graphics::SetColor(0.125f, 0.125f, 0.85f, 0.5f);
            Graphics::DrawPoint(mPath.mX[i], mPath.mY[i], 2.0f);
        }
    }

    
    
}

void GamePathEditor::TouchDown(float pX, float pY, void *pData) {
    
    
    if (mPathMode == PATH_MODE_CREATE) {
        mPath.Add(pX, pY);
    } else if (mPathMode == PATH_MODE_EDIT) {
        
        if (mSelectedTouch == NULL) {
            float aDist = 50.0f * 50.0f;
            int aIndex = mPath.GetClosestIndex(pX, pY, aDist);
            if (aIndex != -1) {
                mSelectedTouch = pData; mSelectedIndex = aIndex;
                mSelectPathStartX = mPath.mX[aIndex]; mSelectPathStartY = mPath.mY[aIndex];
                mSelectTouchStartX = pX; mSelectTouchStartY = pY;
            }
        }
    } else if (mPathMode == PATH_MODE_SELECT) {
        if (mSelectedTouch == NULL) {
            float aDist = 50.0f * 50.0f;
            int aIndex = mPath.GetClosestIndex(pX, pY, aDist);
            if (aIndex != -1) {
                mSelectedTouch = pData; mSelectedIndex = aIndex;
                mSelectPathStartX = mPath.mX[aIndex]; mSelectPathStartY = mPath.mY[aIndex];
                mSelectTouchStartX = pX; mSelectTouchStartY = pY;
            }
        }
    }
    
    //FPoint aPos = FPoint(pX, pY);
    //aPos = FCanvas::Convert(aPos, this, gGame);
    //gGame->mEditorCursorX = aPos.mX;
    //gGame->mEditorCursorY = aPos.mY;
    
    
}

void GamePathEditor::TouchMove(float pX, float pY, void *pData) {
    if (mPathMode == PATH_MODE_EDIT) {
        if (mSelectedTouch == pData) {
            mPath.Set(mSelectedIndex,
                      mSelectPathStartX + (pX - mSelectTouchStartX),
                      mSelectPathStartY + (pY - mSelectTouchStartY));
        }
    }
    
}

void GamePathEditor::TouchUp(float pX, float pY, void *pData) {
    
    if (mSelectedTouch == pData) {
        mSelectedTouch = NULL;
    }
    
}

void GamePathEditor::TouchFlush() {
    
}

void GamePathEditor::KeyDown(int pKey) {
    
}

void GamePathEditor::KeyUp(int pKey) {
    
}

void GamePathEditor::Notify(void *pSender, const char *pNotification) {
    
}

void GamePathEditor::Load() {
    
}

void GamePathEditor::Close() {
    
    
    printf("Close Editor...\n");
    
    
    printf("Hand-off the Path...\n");
    
    
    
    
    mEditor->ClosePathEditor();
}

