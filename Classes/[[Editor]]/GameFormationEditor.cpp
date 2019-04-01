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
    
    if (gGame) {
        mEditorFormation.mX = (float)((int)(gGame->mGameAreaLeft + (gGame->mGameAreaRight - gGame->mGameAreaLeft) / 2.0f + 0.5f));
        mEditorFormation.mY = (float)((int)(gGame->mGameAreaTop + (gGame->mGameAreaBottom - gGame->mGameAreaTop) / 2.0f + 0.5f));
    }
    
    mSelectedTouch = NULL;
    
    mSelectNodeStartX = 0.0f;
    mSelectNodeStartY = 0.0f;
    
    mSelectTouchStartX = 0.0f;
    mSelectTouchStartY = 0.0f;
    
    mTracerMode = FORMATION_MODE_MOVE_POINT;
    mFormationMode = FORMATION_MODE_ADD_POINT;
    
    mTracerEnabled = false;
    
    
    mGridEnabled = true;
    mGridType = FORMATION_GRID_TYPE_RECT;
    
    mGridRectWidth = 4;
    mGridRectHeight = 7;
    mGridRectSpacing = 22;
    
    mGridCircleCount = 14;
    mGridCircleRadius = 220;
    
    
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
    
    mFormation.Print();
    
}

void GameFormationEditor::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    FCanvas::SetFrame(pX, pY, pWidth, pHeight);
    
}

void GameFormationEditor::Layout() {
    
}

void GameFormationEditor::Update() {
    
    mFormation.Update();
    mEditorFormation.Update();
    
    
    
    if (mGridEnabled) {
        BuildGrid();
    }
    
    
    
    
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
    
    mFormation.Draw(true);
    
    
    Graphics::SetColor(1.0f, 0.5f, 0.75f, 0.65f);
    mGridList.DrawPoints(4.0f);
    
}

void GameFormationEditor::TouchDown(float pX, float pY, void *pData) {
    
    
    
    float aX = pX;
    float aY = pY;
    
    GridSnap(&aX, &aY);
    //TO
    
    
    if (mTracerEnabled == true) {
        
        printf("Tracer Stuff...\n");
        
    } else {
        
        
        if (mFormationMode == FORMATION_MODE_ADD_POINT) {
            
            mFormation.Add(aX, aY);
            mFormation.mSelectedIndex = mFormation.mNodeList.mCount - 1;
            
            Refresh();
            
        } else if (mFormationMode == FORMATION_MODE_MOVE_POINT) {
            if (mSelectedTouch == NULL) {
                float aDist = 50.0f * 50.0f;
                
                int aIndex = mFormation.GetClosestIndex(pX, pY, aDist);
                if (aIndex != -1) {
                    mSelectedTouch = pData;
                    mFormation.mSelectedIndex = aIndex;
                    mSelectNodeStartX = mFormation.GetX(aIndex);
                    mSelectNodeStartY = mFormation.GetY(aIndex);
                    mSelectTouchStartX = pX;
                    mSelectTouchStartY = pY;
                }
            } else {
                mSelectedTouch = NULL;
                mFormation.mSelectedIndex = -1;
            }
        } else if (mFormationMode == FORMATION_MODE_SELECT_POINT) {
            if (mSelectedTouch == NULL) {
                float aDist = 50.0f * 50.0f;
                int aIndex = mFormation.GetClosestIndex(pX, pY, aDist);
                if (aIndex != -1) {
                    mSelectedTouch = pData;
                    mFormation.mSelectedIndex = aIndex;
                    mSelectNodeStartX = mFormation.GetX(aIndex);
                    mSelectNodeStartY = mFormation.GetY(aIndex);
                    mSelectTouchStartX = pX; mSelectTouchStartY = pY;
                }
            } else {
                mSelectedTouch = NULL;
                mFormation.mSelectedIndex = -1;
            }
        }
        
    }
    
    
    
}

void GameFormationEditor::TouchMove(float pX, float pY, void *pData) {
    
    if (mTracerEnabled == true) {
        
        printf("Tracer Stuff...\n");
        
    } else {
        if (mFormationMode == PATH_MODE_EDIT) {
            if (mSelectedTouch == pData) {
                
                float aX = mSelectNodeStartX + (pX - mSelectTouchStartX);
                float aY = mSelectNodeStartY + (pY - mSelectTouchStartY);
                
                GridSnap(&aX, &aY);
                
                mFormation.Set(mFormation.mSelectedIndex, aX, aY);
            }
        }
    }
}

void GameFormationEditor::TouchUp(float pX, float pY, void *pData) {
    if (mSelectedTouch == pData) {
        mSelectedTouch = NULL;
    }
}

void GameFormationEditor::TouchFlush() {
    
}

void GameFormationEditor::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (gEditor == NULL) { return; }
    if (gGame == NULL) { return; }
    
    
    if (pKey == __KEY__P) { Print(); }
    
    if (pKey == __KEY__S) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            Save();
        }
    }
    
    if (pKey == __KEY__L) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            Load();
        }
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

void GameFormationEditor::SetUp(LevelWaveSpawnFormationBlueprint *pFormation) {
    if (gEditor != NULL) {
        mGameAreaTop = gEditor->mGameAreaTop;
        mGameAreaRight = gEditor->mGameAreaRight;
        mGameAreaBottom = gEditor->mGameAreaBottom;
        mGameAreaLeft = gEditor->mGameAreaLeft;
        
        mCenterX = (float)((int)(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft) / 2.0f + 0.5f));
        mCenterY = (float)((int)(mGameAreaTop + (mGameAreaBottom - mGameAreaTop) / 2.0f + 0.5f));
        
        if (gGame) {
            mEditorFormation.mX = (float)((int)(gGame->mGameAreaLeft + (gGame->mGameAreaRight - gGame->mGameAreaLeft) / 2.0f + 0.5f));
            mEditorFormation.mY = (float)((int)(gGame->mGameAreaTop + (gGame->mGameAreaBottom - gGame->mGameAreaTop) / 2.0f + 0.5f));
        }
    }
    
    if (pFormation != NULL) {
        FJSONNode *aLoadNode = pFormation->Save();
        if (aLoadNode != NULL) {
            mFormation.Load(aLoadNode);
        }
        delete aLoadNode;
    } else {
        Load();
    }
}

void GameFormationEditor::Close() {
    
    mFormation.Print();
    
    mFormation.Clear();
    mEditorFormation.Reset();
    mEditor->ClosePathEditor();
}

void GameFormationEditor::Clear() {
    printf("GameFormationEditor::Clear()\n");
    mFormation.Clear();
    Refresh();
}

void GameFormationEditor::Refresh() {
    mFormation.Build(&mEditorFormation);
    mEditorFormation.Spawn();
}

void GameFormationEditor::Save() {
    
    if (gEditor == NULL) { return; }
    
    FString aPath = gDirExport + FString("formation_export_") + FString(gEditor->mExportIndex) + FString(".json");
    
    FJSON aJSON;
    aJSON.mRoot = mFormation.Save();
    aJSON.Save(aPath.c());
}

void GameFormationEditor::Load() {
    
    if (gEditor == NULL) { return; }
    
    FString aPath = gDirExport + FString("formation_export_") + FString(gEditor->mExportIndex) + FString(".json");
    
    FJSON aJSON;
    aJSON.Load(aPath.c());
    mFormation.Load(aJSON.mRoot);
    Refresh();
}

void GameFormationEditor::Print() {
    
     mFormation.Print();
}

void GameFormationEditor::BuildGrid() {
    BuildRectGrid();
}

void GameFormationEditor::BuildRectGrid() {
    
    if (mGridRectWidth < 1) {
        mGridRectWidth = 1;
    }
    if (mGridRectHeight < 1) {
        mGridRectHeight = 1;
    }
    if (mGridRectSpacing < 0) {
        mGridRectSpacing = 0;
    }
    
    mGridList.RemoveAll();
    
    float aTotalWidth = mGridRectWidth * mGridRectSpacing;
    float aTotalHeight = mGridRectHeight * mGridRectSpacing;
    
    float aLeft = round(mCenterX - (aTotalWidth / 2.0f) + mGridRectSpacing / 2);
    float aTop = round(mCenterY - (aTotalHeight / 2.0f) + mGridRectSpacing / 2);
    
    for (int i=0;i<mGridRectWidth;i++) {
        
        float aX = aLeft + ((float)mGridRectSpacing) * ((float)i);
        
        for (int n=0;n<mGridRectHeight;n++) {
            
            float aY = aTop + ((float)mGridRectSpacing) * ((float)n);
            
            mGridList.Add(aX, aY);
            
        }
        
    }
    
}



void GameFormationEditor::DeleteNode() {
    mFormation.Remove(mFormation.mSelectedIndex);
}


void GameFormationEditor::GridSnap(float *pX, float *pY) {
    
    if (mGridEnabled) {
        float aBestDist = 60.0f * 60.0f;
        int aIndex = mGridList.GetClosestIndex(*pX, *pY, aBestDist);
        if (aIndex != -1) {
            
            *pX = mGridList.GetX(aIndex);
            *pY = mGridList.GetY(aIndex);
        }
    }
}
