//
//  GamePermanentEditor.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GamePermanentEditor.hpp"
#include "GameEditor.hpp"
#include "FAnimation.hpp"

GamePermanentEditor *gPermEditor = NULL;
GamePermanentEditor::GamePermanentEditor(GameEditor *pEditor) {
    
    gPermEditor = this;
    
    mEditor = pEditor;
    
    mGameAreaTop = pEditor->mGameAreaTop;
    mGameAreaRight = pEditor->mGameAreaRight;
    mGameAreaBottom = pEditor->mGameAreaBottom;
    mGameAreaLeft = pEditor->mGameAreaLeft;
    
    mOverlay = NULL;
    
    mSelectedTouch = NULL;
    mSnapsEnabled = true;
    
    mSelectNodeStartX = 0.0f;
    mSelectNodeStartY = 0.0f;
    
    mSelectTouchStartX = 0.0f;
    mSelectTouchStartY = 0.0f;
    
    mPermMode = PERMANENT_MODE_ADD;
    
    mMarkersDisplay = true;
    
    mName = "[GamePermanentEditor]";
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    mToolContainer = new FCanvas();
    mToolContainer->mConsumesTouches = false;
    mToolContainer->mName = "Tool Container";
    AddChild(mToolContainer);
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    mMenuPerm = new EditorMenuPermanent(this);
    mToolContainer->AddChild(mMenuPerm);
    mMenuPerm->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 20.0f, 400.0f, 736.0f);
    
    mMenuUtils = new EditorMenuPermanentUtils(this);
    mToolContainer->AddChild(mMenuUtils);
    mMenuUtils->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f), gSafeAreaInsetTop + 20.0f, 400.0f, 736.0f);
    
    SetOverlay(mToolContainer);
    
}

GamePermanentEditor::~GamePermanentEditor() {
    if (gPermEditor == this) { gPermEditor = NULL; }
    
    if (gEditor != NULL) {
        if (gEditor->mPermEditor == this) {
            gEditor->mPermEditor = NULL;
        }
    }
}

void GamePermanentEditor::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    FCanvas::SetFrame(pX, pY, pWidth, pHeight);
    
}

void GamePermanentEditor::Layout() {
    
}

void GamePermanentEditor::Update() {
    
}

void GamePermanentEditor::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 0.85f, 1.0f, 0.75f);
    Graphics::DrawRect(0.0f, 0.0f, mGameAreaLeft, gDeviceHeight);
    Graphics::DrawRect(mGameAreaLeft, 0.0f, mGameAreaRight - mGameAreaLeft, mGameAreaTop);
    Graphics::DrawRect(mGameAreaLeft, mGameAreaBottom, mGameAreaRight - mGameAreaLeft, gDeviceHeight - mGameAreaBottom);
    Graphics::DrawRect(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft), 0.0f, gDeviceWidth - (mGameAreaLeft + (mGameAreaRight - mGameAreaLeft)), gDeviceHeight);
    
    if (mMarkersDisplay == true) {
        if (gGame) {
            gGame->DrawTransform();
        }
    }
    
    if (gEditor != NULL) {
        
        int aIndex = gEditor->PermIndex();
        
        
        LevelSectionPermanent *aPerm = (LevelSectionPermanent *)gEditor->mEditorSection.mPermList.Fetch(aIndex);
        if (aPerm != NULL) {
            aPerm->mPath.Draw();
        }
    }
    
    //LevelSectionPermanentBlueprint *aPerm = GetPerm();
    
    
}

void GamePermanentEditor::TouchDown(float pX, float pY, void *pData) {
    
    if (gEditor == NULL) { return; }
    if (mEditor == NULL) { return; }
    
    
    float aX = pX;
    float aY = pY;
    
    if (mPermMode == PERMANENT_MODE_ADD) {
        
        gEditor->mSection.PermAdd(pX, pY);
        
    } else if (mPermMode == PERMANENT_MODE_MOVE) {
        if (mSelectedTouch == NULL) {
            float aDist = 50.0f * 50.0f;
            
            gEditor->mSection.PermSelectClosest(pX, pY);
            LevelSectionPermanentBlueprint *aPerm = gEditor->PermnGet();
            if (aPerm != NULL) {
                mSelectedTouch = pData;
                mSelectNodeStartX = aPerm->mEditorX;
                mSelectNodeStartY = aPerm->mEditorY;
                mSelectTouchStartX = pX;
                mSelectTouchStartY = pY;
            }
        }
        
    } else if (mPermMode == PERMANENT_MODE_SELECT) {
        if (mSelectedTouch == NULL) {
            
            gEditor->mSection.PermSelectClosest(pX, pY);
        } else {
            mSelectedTouch = NULL;
            //mFormation.mSelectedNodeIndex = -1;
            
        }
    }
}

void GamePermanentEditor::TouchMove(float pX, float pY, void *pData) {
    float aX = mSelectNodeStartX + (pX - mSelectTouchStartX);
    float aY = mSelectNodeStartY + (pY - mSelectTouchStartY);
    
    if (mPermMode == PERMANENT_MODE_MOVE) {
        LevelSectionPermanentBlueprint *aPerm = gEditor->PermnGet();
        if (mSelectedTouch == pData && aPerm != NULL) {
            if (mSnapsEnabled && gEditor != NULL) {
                aPerm->mConstraint.mTypeX = gEditor->ClosestXConstraint(aX);
                aPerm->mConstraint.mTypeY = gEditor->ClosestYConstraint(aY);
            } else {
                aPerm->mEditorX = aX;
                aPerm->mEditorY = aY;
            }
            aPerm->ApplyEditorConstraints();
        }
    }
}

void GamePermanentEditor::TouchUp(float pX, float pY, void *pData) {
    if (mSelectedTouch == pData) {
        mSelectedTouch = NULL;
    }
}

void GamePermanentEditor::TouchFlush() {
    
}

void GamePermanentEditor::KeyDown(int pKey) {
    
    if (mOverlay == mPathEditor) {
        printf("Niffing Key [Perm Path]\n");
        return;
    }
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (gEditor == NULL) { return; }
    if (gGame == NULL) { return; }
    
    if (pKey == __KEY__DELETE) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            DeletePermanent();
        }
        if (aShift == false && aCtrl == true && aAlt == false) {
            DeletePath();
        }
    }
    
    if (pKey == __KEY__E) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            OpenPathEditor();
        }
    }
    
    if (pKey == __KEY__A) {
        mPermMode = PERMANENT_MODE_ADD;
    }
    
    if (pKey == __KEY__E) {
        mPermMode = PERMANENT_MODE_MOVE;
    }
    
    if (pKey == __KEY__S) {
        
        if (aShift == false && aCtrl == false && aAlt == false) {
            mPermMode = PERMANENT_MODE_SELECT;
        }
        
        if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    
    if (pKey == __KEY__L) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    
    
    if (pKey == __KEY__DELETE) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            //mFormation.Remove(mFormation.mSelectedNodeIndex);
        }
        
        if (aShift == false && aCtrl == true && aAlt == false) {
            
            
            //for (int i=mFormation.mNodeList.mCount - 1;i>=0;i--) {
            //    mFormation.Remove(i);
            //}
            
        }
    }
    
    if (pKey == __KEY__ESCAPE) {
        if (aShift == false && aCtrl == false && aAlt == false) { Close(); }
    }
    
    
    LevelSectionPermanentBlueprint *aPerm = GetPerm();
    
    if (aPerm != NULL) {
        if (pKey == __KEY__LEFT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aPerm->ShiftX(-1);
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aPerm->ShiftX(-10);
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
            }
        }
        if (pKey == __KEY__RIGHT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aPerm->ShiftX(1);
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aPerm->ShiftX(10);
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
            }
        }
        if (pKey == __KEY__UP) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aPerm->ShiftY(-1);
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aPerm->ShiftY(-10);
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
            }
        }
        if (pKey == __KEY__DOWN) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aPerm->ShiftY(1);
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aPerm->ShiftY(10);
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
            }
        }
    }
}

void GamePermanentEditor::KeyUp(int pKey) {
    
}

void GamePermanentEditor::Notify(void *pSender, const char *pNotification) {
    
}

void GamePermanentEditor::SetUp() {
    if (gEditor != NULL) {
        mGameAreaTop = gEditor->mGameAreaTop;
        mGameAreaRight = gEditor->mGameAreaRight;
        mGameAreaBottom = gEditor->mGameAreaBottom;
        mGameAreaLeft = gEditor->mGameAreaLeft;
    }
    PickDefaultModes();
}

void GamePermanentEditor::PickDefaultModes() {
    if (gEditor != NULL) {
        if (gEditor->mSection.mPermList.mCount > 0) {
            mPermMode = PERMANENT_MODE_MOVE;
        } else {
            mPermMode = PERMANENT_MODE_ADD;
        }
    }
}

void GamePermanentEditor::Close() {
    mEditor->ClosePermanentEditor();
}

void GamePermanentEditor::ResetSelected() {
    printf("GamePermanentEditor::ResetSelected()\n");
    
    
}

void GamePermanentEditor::Refresh() {
    if (gGame != NULL) {
        gGame->DisposeAllObjects();
    }
    
    if (gEditor != NULL) {
        gEditor->RefreshPlayback();
    }
}


void GamePermanentEditor::BreakConstraintX() {
    LevelSectionPermanentBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        aPerm->mConstraint.mTypeX = X_CONSTRAINT_NONE;
        Refresh();
    }
}

void GamePermanentEditor::BreakConstraintY() {
    
    LevelSectionPermanentBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        aPerm->mConstraint.mTypeY = Y_CONSTRAINT_NONE;
        Refresh();
    }
}


void GamePermanentEditor::ResetOffsetX() {
    LevelSectionPermanentBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        
        aPerm->mConstraint.mOffsetX = 0.0f;
        Refresh();
    }
}

void GamePermanentEditor::ResetOffsetY() {
    LevelSectionPermanentBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        
        aPerm->mConstraint.mOffsetY = 0.0f;
        Refresh();
    }
}

void GamePermanentEditor::SetOverlay(FCanvas *pCanvas) {
    if (mOverlay) {
        if (mOverlay == pCanvas) {
            return;
        }
        mOverlay->Deactivate();
        mOverlay = NULL;
    }
    if (pCanvas) {
        mOverlay = pCanvas;
        mOverlay->Activate();
    }
}

void GamePermanentEditor::OpenPathEditor() {
    LevelSectionPermanentBlueprint *aPerm = GetPerm();
    if (aPerm == NULL) {
        printf("No Perm Selected...\n");
        return;
    }
    mPathEditor = new GamePathEditor(this);
    mPathEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mPathEditor->mName = "{Path Editor}";
    AddChild(mPathEditor);
    mPathEditor->SetUp(aPerm);
    SetOverlay(mPathEditor);
}

void GamePermanentEditor::ClosePathEditor() {
    SetOverlay(mToolContainer);
    if (mPathEditor) {
        mPathEditor->Kill();
        mPathEditor = NULL;
    }
}

void GamePermanentEditor::AddPath() {
    OpenPathEditor();
}

void GamePermanentEditor::DeletePath() {
    LevelSectionPermanentBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        aPerm->DeletePath();
    }
}

void GamePermanentEditor::DeletePermanent() {
    if (gEditor != NULL) {
        gEditor->PermDelete();
    }
}

LevelSectionPermanentBlueprint *GamePermanentEditor::GetPerm() {
    
    if (gEditor != NULL) {
        LevelSectionPermanentBlueprint *aPerm = gEditor->PermnGet();
        if (aPerm != NULL) {
            return aPerm;
        }
    }
    return NULL;
}


