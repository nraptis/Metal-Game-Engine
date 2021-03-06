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
    mCenterX = (float)((int)(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft) / 2.0f + 0.5f));
    mCenterY = (float)((int)(mGameAreaTop + (mGameAreaBottom - mGameAreaTop) / 2.0f + 0.5f));
    
    
    
    mOverlay = NULL;
    mMenuAttachment = NULL;
    mMenuSpawnPicker = NULL;
    mMenuPermPicker = NULL;
    mMenuMotion = NULL;
    mMenuStyle = NULL;
    mMenuGrid = NULL;
    
    
    mPathSpeedClassIndex = -1;
    
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
    
    
    mMenuGrid = new EditorMenuFormationGrid(&mGrid);
    mToolContainer->AddChild(mMenuGrid);
    mMenuGrid->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f + 60.0f), gSafeAreaInsetTop + 20.0f + 200.0f, 400.0f, 736.0f - 100.0f);
    
    //                   *;
    /*
    void GameEditor::OpenSpawnPickerMenu() {
        if (mMenuSpawnPicker == NULL) {
            mMenuSpawnPicker = new EditorMenuSpawnPicker(this);
            mToolContainer->AddChild(mMenuSpawnPicker);
            mMenuSpawnPicker->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f),
                                       (gDeviceHeight - gSafeAreaInsetBottom - 2.0f) - 134.0f, 400.0f, 154.0f);
        }
    }
    */
    
    
    SetOverlay(mToolContainer);
    
    
    OpenMenuSpawnPicker();
    OpenMenuPermPicker();
    

    mGrid.mCenterX = mCenterX;
    mGrid.mCenterY = mCenterY;
    
    if (gEditor != NULL) {
        mGrid.mCenterX = gEditor->mCenterH;
        mGrid.mCenterY = gEditor->mCenterV;
    }
    
    mGrid.BuildGrid();
    mGrid.mGridEnabled = false;
    
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
    
    mGrid.Update();
    
}

void GamePermanentEditor::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.75f, 0.95f, 0.65f, 0.75f);
    Graphics::DrawRect(0.0f, 0.0f, mGameAreaLeft, gDeviceHeight);
    Graphics::DrawRect(mGameAreaLeft, 0.0f, mGameAreaRight - mGameAreaLeft, mGameAreaTop);
    Graphics::DrawRect(mGameAreaLeft, mGameAreaBottom, mGameAreaRight - mGameAreaLeft, gDeviceHeight - mGameAreaBottom);
    Graphics::DrawRect(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft), 0.0f, gDeviceWidth - (mGameAreaLeft + (mGameAreaRight - mGameAreaLeft)), gDeviceHeight);
    
    if (mGrid.mGridEnabled) {
        mGrid.Draw();
    }
    
    if (mMarkersDisplay == true) {
        if (gGame) {
            gGame->DrawTransform();
        }
    }
    
    if (gEditor != NULL) {
        
        int aIndex = gEditor->PermIndex();
        
        LevelSectionPerm *aPerm = (LevelSectionPerm *)gEditor->mEditorSection.mPermList.Fetch(aIndex);
        if (aPerm != NULL) {
            aPerm->mPath.mDrawOffsetX = aPerm->mX;
            aPerm->mPath.mDrawOffsetY = aPerm->mY;
            aPerm->mPath.Draw();
        }
    }
    
    //LevelSectionPermBlueprint *aPerm = GetPerm();
    
    
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
            LevelSectionPermBlueprint *aPerm = gEditor->PermGet();
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
        LevelSectionPermBlueprint *aPerm = gEditor->PermGet();
        if (mSelectedTouch == pData && aPerm != NULL) {
            
                if (mGrid.mGridEnabled) {
                    mGrid.GridSnap(&aX, &aY);
                    aPerm->mEditorX = aX;
                    aPerm->mEditorY = aY;
                    aPerm->mConstraint.mTypeX = X_CONSTRAINT_NONE;
                    aPerm->mConstraint.mTypeY = Y_CONSTRAINT_NONE;
                } else {
                    
                    if (mSnapsEnabled && gEditor != NULL) {
                        aPerm->mConstraint.mTypeX = gEditor->ClosestXConstraint(aX);
                        aPerm->mConstraint.mTypeY = gEditor->ClosestYConstraint(aY);
                    } else {
                        aPerm->mEditorX = aX;
                        aPerm->mEditorY = aY;
                    }
                    
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
        Log("Niffing Key [Perm Path]\n");
        return;
    }
    
    LevelSectionPermBlueprint *aPerm = GetPerm();
    LevelPermSpawnBlueprint *aSpawn = gEditor->PermSpawnGet();
    
    
    bool aForSpawn = false;
    
    if (aPerm != NULL) {
        if (aPerm->IsPathPerm() && aPerm->mSelectedSpawnIndex >= 0 && aPerm->mSelectedSpawnIndex < aPerm->mSpawnCount) {
            aForSpawn = true;
        } else {
            aForSpawn = false;
        }
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
    
    if (pKey == __KEY__P) {
        mSnapsEnabled = !mSnapsEnabled;
    }
    
    if (pKey == __KEY__B) {
        if (aPerm != NULL) {
            aPerm->mConstraint.mTypeX = X_CONSTRAINT_NONE;
            aPerm->mConstraint.mTypeY = Y_CONSTRAINT_NONE;
            Refresh();
        }
    }
    
    if (pKey == __KEY__O) {
        if (aPerm != NULL) {
            if (aSpawn != NULL) {
                gEditor->PickFormationForPermSpawnNode();
            } else {
                gEditor->PickFormationForPerm();
            }
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
    
    if (pKey == __KEY__G) {
        if (aShift == false && aCtrl == false && aAlt == false) { mGrid.mGridEnabled = !mGrid.mGridEnabled; }
    }
    
    if (pKey == __KEY__M) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            if (aForSpawn) {
                OpenMenuMotionForSpawn();
            } else {
                OpenMenuMotionForPerm();
            }
        }
    }
    
    if (pKey == __KEY__Y) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            if (aForSpawn) {
                OpenMenuStyleForSpawn();
            } else {
                OpenMenuStyleForPerm();
            }
        }
    }
    
    if (pKey == __KEY__T) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            OpenMenuAttachment();
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
    }
    
    if (pKey == __KEY__ESCAPE) {
        if (aShift == false && aCtrl == false && aAlt == false) { Close(); }
    }
    
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
    Log("GamePermanentEditor::ResetSelected()\n");
}

void GamePermanentEditor::Refresh() {
    if (gGame != NULL) {
        gGame->DisposeAllObjects();
    }
    
    if (gEditor != NULL) {
        gEditor->RefreshPlayback();
    }
}

void GamePermanentEditor::RefreshSpeed() {
    
    if (gEditor != NULL) {
        LevelSectionPermBlueprint *aPerm = GetPerm();
        if (aPerm != NULL) {
            aPerm->mPath.mSpeedClass = gEditor->SpeedConvertSegmentToType(mPathSpeedClassIndex);
        }
    }
}

void GamePermanentEditor::BreakConstraintX() {
    LevelSectionPermBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        mSnapsEnabled = false;
        aPerm->mConstraint.mTypeX = X_CONSTRAINT_NONE;
        Refresh();
    }
}

void GamePermanentEditor::BreakConstraintY() {
    LevelSectionPermBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        mSnapsEnabled = false;
        aPerm->mConstraint.mTypeY = Y_CONSTRAINT_NONE;
        Refresh();
    }
}

void GamePermanentEditor::ResetOffsetX() {
    LevelSectionPermBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        aPerm->mConstraint.mOffsetX = 0.0f;
        Refresh();
    }
}

void GamePermanentEditor::ResetOffsetY() {
    LevelSectionPermBlueprint *aPerm = GetPerm();
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
    LevelSectionPermBlueprint *aPerm = GetPerm();
    if (aPerm == NULL) {
        Log("No Perm Selected...\n");
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

void GamePermanentEditor::OpenMenuPermPicker() {
    if (mMenuPermPicker == NULL) {
        mMenuPermPicker = new EditorMenuPermPicker(this);
        mToolContainer->AddChild(mMenuPermPicker);
        mMenuPermPicker->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f),
                                  (gDeviceHeight - gSafeAreaInsetBottom - 2.0f) - 134.0f, 400.0f, 154.0f);
    }
}

void GamePermanentEditor::OpenMenuSpawnPicker() {
    if (mMenuSpawnPicker == NULL) {
        mMenuSpawnPicker = new EditorMenuPermSpawnPicker(this);
        mToolContainer->AddChild(mMenuSpawnPicker);
        mMenuSpawnPicker->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f), (gDeviceHeight - gSafeAreaInsetBottom - 2.0f) - (154.0f + 134.0f + 2.0f), 400.0f, 154.0f);
    }
}

void GamePermanentEditor::OpenMenuAttachment() {
    if (mMenuAttachment == NULL) {
        mMenuAttachment = new EditorMenuAttachment(this);
        mToolContainer->AddChild(mMenuAttachment);
        mMenuAttachment->SetFrame(gDeviceWidth2 + 200.0f,
                                  (gDeviceHeight - gSafeAreaInsetBottom) - 600.0f - 2.0f, 400.0f, 600.0f);
    }
}

void GamePermanentEditor::OpenMenuMotionForPerm() {
    if (mMenuMotion == NULL) {
        mMenuMotion = new EditorMenuMotion(this);
        mMenuMotion->mIsForPermSpawn = false;
        mToolContainer->AddChild(mMenuMotion);
        mMenuMotion->SetFrame(gDeviceWidth2 / 2.0f - 420.0f / 2.0f, 130.0f, 420.0f, 600.0f);
    }
}

void GamePermanentEditor::OpenMenuMotionForSpawn() {
    if (mMenuMotion == NULL) {
        mMenuMotion = new EditorMenuMotion(this);
        mMenuMotion->mIsForPermSpawn = true;
        mToolContainer->AddChild(mMenuMotion);
        mMenuMotion->SetFrame(gDeviceWidth2 / 2.0f - 420.0f / 2.0f, 130.0f, 420.0f, 600.0f);
    }
}

void GamePermanentEditor::OpenMenuStyleForPerm() {
    if (mMenuStyle == NULL) {
        mMenuStyle = new EditorMenuStyle(this);
        mMenuStyle->mIsForPermSpawn = false;
        mToolContainer->AddChild(mMenuStyle);
        mMenuStyle->SetFrame(gDeviceWidth2 / 2.0f - 300.0f / 2.0f, 220.0f, 420.0f, 400.0f);
    }
}

void GamePermanentEditor::OpenMenuStyleForSpawn() {
    if (mMenuStyle == NULL) {
        mMenuStyle = new EditorMenuStyle(this);
        mMenuStyle->mIsForPermSpawn = true;
        mToolContainer->AddChild(mMenuStyle);
        mMenuStyle->SetFrame(gDeviceWidth2 / 2.0f - 300.0f / 2.0f, 220.0f, 420.0f, 400.0f);
    }
}

void GamePermanentEditor::AddPath() {
    OpenPathEditor();
}

void GamePermanentEditor::DeletePath() {
    LevelSectionPermBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        aPerm->DeletePath();
    }
}

void GamePermanentEditor::DeletePermanent() {
    if (gEditor != NULL) {
        gEditor->PermDelete();
    }
}

void GamePermanentEditor::PermSelect(int pIndex) {
    if (gEditor != NULL) {
        gEditor->PermSelect(pIndex);
    }
}

void GamePermanentEditor::PermSpawnSelect(int pIndex) {
    LevelSectionPermBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        aPerm->mSelectedSpawnIndex = pIndex;
    }
}

int GamePermanentEditor::PermSpawnIndex() {
    LevelSectionPermBlueprint *aPerm = GetPerm();
    if (aPerm != NULL) {
        if (aPerm->mSelectedSpawnIndex >= 0 && aPerm->mSelectedSpawnIndex < aPerm->mSpawnCount) {
            return aPerm->mSelectedSpawnIndex;
        }
    }
    return -1;
}

LevelSectionPermBlueprint *GamePermanentEditor::GetPerm() {
    if (gEditor != NULL) {
        LevelSectionPermBlueprint *aPerm = gEditor->PermGet();
        if (aPerm != NULL) {
            return aPerm;
        }
    }
    return NULL;
}

void GamePermanentEditor::PastePerm() {
    gEditor->mSection.PermAdd(mWidth2, mHeight2);
    LevelSectionPermBlueprint *aPerm = gEditor->PermGet();
    if (aPerm != NULL) {
        gEditor->PastePerm(aPerm);
    }
}

void GamePermanentEditor::PastePermSpawnAtEndOfList() {
    LevelSectionPermBlueprint *aPerm = gEditor->PermGet();
    if (aPerm == NULL) { return; }
    if (aPerm->mSpawnCount >= PERM_MAX_SPAWN_COUNT) { return; }
    int aPasteIndex = aPerm->mSpawnCount;
    aPerm->mSpawnCount++;
    aPerm->mSelectedSpawnIndex = aPasteIndex;
    gEditor->PastePermSpawn(&(aPerm->mSpawn[aPasteIndex]));
}

void GamePermanentEditor::PastePermSpawnAfterCurrent() {
    LevelSectionPermBlueprint *aPerm = gEditor->PermGet();
    if (aPerm == NULL) { return; }
    if (aPerm->mSpawnCount >= PERM_MAX_SPAWN_COUNT) { return; }
    
    if ((aPerm->mSelectedSpawnIndex < 0) || (aPerm->mSelectedSpawnIndex >= aPerm->mSpawnCount)) { return; }
    int aPasteIndex = aPerm->mSelectedSpawnIndex;
    aPerm->ShiftSpawnFromIndex(aPasteIndex);
    aPerm->mSelectedSpawnIndex = (aPasteIndex + 1);
    gEditor->PastePermSpawn(&(aPerm->mSpawn[aPasteIndex + 1]));
}
