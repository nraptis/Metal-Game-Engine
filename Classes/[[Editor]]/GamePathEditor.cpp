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
#include "GamePermanentEditor.hpp"
#include "FAnimation.hpp"

GamePathEditor::GamePathEditor(GameEditor *pEditor) {
    mEditor = pEditor;
    mPermanentEditor = NULL;
    Init();
    
    mGrid.mGridEnabled = false;
    
}

GamePathEditor::GamePathEditor(GamePermanentEditor *pEditor) {
    mEditor = NULL;
    mPermanentEditor = pEditor;
    Init();
    
    mGrid.mGridEnabled = mPermanentEditor->mGrid.mGridEnabled;
}

void GamePathEditor::Init() {
    mPathMode = PATH_MODE_CREATE;
    
    mName = "[GamePathEditor]";
    
    
    mMenuGrid = NULL;
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    mConstrainXToPoint = false;
    mConstrainYToPoint = false;
    
    mSelectedTouch = NULL;
    
    mSelectPathStartX = 0.0f;
    mSelectPathStartY = 0.0f;
    
    mSelectTouchStartX = 0.0f;
    mSelectTouchStartY = 0.0f;
    
    mPath = NULL;
    mWave = NULL;
    mPerm = NULL;
    
    mMenuPaths = new EditorMenuPath(this);
    AddChild(mMenuPaths);
    mMenuPaths->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 20.0f, 400.0f, 680.0f);
    
    mMenuControls = new EditorMenuPathControl(this);
    AddChild(mMenuControls);
    mMenuControls->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f), gSafeAreaInsetTop + 20.0f, 400.0f, 480.0f);
    
    
    mMenuGrid = new EditorMenuFormationGrid(&mGrid);
    AddChild(mMenuGrid);
    mMenuGrid->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f + 60.0f), gSafeAreaInsetTop + 20.0f + 200.0f, 400.0f, 736.0f - 200.0f);
    
}

GamePathEditor::~GamePathEditor() {
    
    if (gEditor != NULL) {
        if (gEditor->mPathEditor == this) {
            gEditor->mPathEditor = NULL;
        }
    }
    if (mPermanentEditor != NULL) {
        if (mPermanentEditor->mPathEditor == this) {
            mPermanentEditor->mPathEditor = NULL;
        }
    }
    
}

void GamePathEditor::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    FCanvas::SetFrame(pX, pY, pWidth, pHeight);
    
}

void GamePathEditor::Layout() {
    
}

void GamePathEditor::Update() {
    
    mGrid.Update();
    
    
    if (mConstrainXToPoint && mConstrainYToPoint) {
        mConstrainXToPoint = false;
        mConstrainYToPoint = false;
    }
    
    if (mPath != NULL) {
        if (mPath->mSelectedIndex == -1) {
            mConstrainXToPoint = false;
            mConstrainYToPoint = false;
        }
    }
    
}

void GamePathEditor::Draw() {
    
    if (mGrid.mGridEnabled) {
        mGrid.Draw();
    }
    
}

void GamePathEditor::TouchDown(float pX, float pY, void *pData) {
    if (mPath != NULL) {
        if (mConstrainXToPoint || mConstrainYToPoint) {
            float aDist = 50.0f * 50.0f;
            int aIndex = mPath->GetClosestIndex(pX, pY, aDist);
            if (aIndex != -1 && mPath->mSelectedIndex != -1 && mPath->mSelectedIndex != aIndex) {
                if (mConstrainXToPoint) {
                    mPath->SnapX(aIndex);
                }
                if (mConstrainYToPoint) {
                    mPath->SnapY(aIndex);
                }
                mConstrainXToPoint = false;
                mConstrainYToPoint = false;
            }
            
            mSelectedTouch = NULL;
            return;
        }
        
        //mConstrainXToPoint = false;
        //mConstrainYToPoint = false;
        
    }
    
    if (mPathMode == PATH_MODE_CREATE) {
        if (mPath) {
            mPath->Add(pX, pY);
            mPath->mSelectedIndex = mPath->mNodeList.mCount - 1;
            
            LevelPathNodeBlueprint *aNode = mPath->GetNode();
            if (aNode) {
                
                if (mGrid.mGridEnabled) {
                    float aX = pX;
                    float aY = pY;
                    mGrid.GridSnap(&aX, &aY);
                    aNode->mEditorX = aX;
                    aNode->mEditorY = aY;
                    aNode->mConstraint.mTypeX = X_CONSTRAINT_NONE;
                    aNode->mConstraint.mTypeY = Y_CONSTRAINT_NONE;
                } else {
                    aNode->mConstraint.mTypeX = gEditor->ClosestXConstraint(pX);
                    aNode->mConstraint.mTypeY = gEditor->ClosestYConstraint(pY);
                }
                
                
                
                
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
                
            }
        }
    } else if (mPathMode == PATH_MODE_EDIT) {
        if (mSelectedTouch == NULL && mPath != NULL) {
            float aDist = 50.0f * 50.0f;
            int aIndex = mPath->GetClosestIndex(pX, pY, aDist);
            if (aIndex != -1) {
                mSelectedTouch = pData;
                mPath->mSelectedIndex = aIndex;
                mSelectPathStartX = mPath->GetX(aIndex); mSelectPathStartY = mPath->GetY(aIndex);
                mSelectTouchStartX = pX; mSelectTouchStartY = pY;
            }
        } else {
            mSelectedTouch = NULL;
            mPath->mSelectedIndex = -1;
        }
    } else if (mPathMode == PATH_MODE_SELECT) {
        if (mSelectedTouch == NULL && mPath != NULL) {
            float aDist = 50.0f * 50.0f;
            int aIndex = mPath->GetClosestIndex(pX, pY, aDist);
            if (aIndex != -1) {
                mSelectedTouch = pData;
                mPath->mSelectedIndex = aIndex;
                mSelectPathStartX = mPath->GetX(aIndex); mSelectPathStartY = mPath->GetY(aIndex);
                mSelectTouchStartX = pX; mSelectTouchStartY = pY;
            }
        } else {
            mSelectedTouch = NULL;
            mPath->mSelectedIndex = -1;
        }
    }
}

void GamePathEditor::TouchMove(float pX, float pY, void *pData) {
    if (mPathMode == PATH_MODE_EDIT) {
        if (mSelectedTouch == pData && mPath != NULL) {
            
            float aX = mSelectPathStartX + (pX - mSelectTouchStartX);
            float aY = mSelectPathStartY + (pY - mSelectTouchStartY);
           
            LevelPathNodeBlueprint *aNode = mPath->GetNode();
            
            if (aNode != NULL) {
                if (mGrid.mGridEnabled) {
                    mGrid.GridSnap(&aX, &aY);
                    aNode->mEditorX = aX;
                    aNode->mEditorY = aY;
                    aNode->mConstraint.mTypeX = X_CONSTRAINT_NONE;
                    aNode->mConstraint.mTypeY = Y_CONSTRAINT_NONE;
                } else {
                    mPath->Set(mPath->mSelectedIndex, aX, aY);
                    //aNode->mConstraint.mTypeX = gEditor->ClosestXConstraint(pX);
                    //aNode->mConstraint.mTypeY = gEditor->ClosestYConstraint(pY);
                    
                }
            }
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
    
    if (gEditor == NULL) { return; }
    
    if (mPermanentEditor != NULL) {
        if (mPermanentEditor->mOverlay != this) {
            return;
        }
    }
    if (mEditor != NULL) {
        if (mEditor->mOverlay != this) {
            return;
        }
    }
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    //if (mWave == NULL) { return; }
    
    if (mPath == NULL) { return; }
    LevelPathNodeBlueprint *aNode = mPath->GetNode();
    
    if (pKey == __KEY__P) {
        PathPrint();
    }
    
    if (pKey == __KEY__DELETE) {
        if (aShift == false && aCtrl == false && aAlt == false) { PathDeletePoint(); }
    }
    
    if (pKey == __KEY__A) {
        if (aShift == false && aCtrl == false && aAlt == false) { mPathMode = PATH_MODE_CREATE; }
        
    }
    
    if (pKey == __KEY__G) {
        if (aShift == false && aCtrl == false && aAlt == false) { mGrid.mGridEnabled = !mGrid.mGridEnabled; }
    }
    
    if (pKey == __KEY__ESCAPE) {
        if (aShift == false && aCtrl == false && aAlt == false) { Close(); }
    }
    
    if (pKey == __KEY__S) {
        if (aShift == false && aCtrl == false && aAlt == false) { mPathMode = PATH_MODE_SELECT; }
        
    }
    
    if (pKey == __KEY__B) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            ConstraintXToType(X_CONSTRAINT_NONE);
            ConstraintYToType(Y_CONSTRAINT_NONE);
        }
    }
    
    if (pKey == __KEY__E) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            mPathMode = PATH_MODE_EDIT;
        }
    }
    
    if (aNode) {
        if (pKey == __KEY__X) {
            if (aShift == false && aCtrl == true && aAlt == false) {
                aNode->mConstraint.mOffsetX = 0.0f;
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
            } else {
                mConstrainXToPoint = !mConstrainXToPoint;
                if (mConstrainXToPoint) {
                    mConstrainYToPoint = false;
                }
            }
        }
        
        if (pKey == __KEY__Y) {
            if (aShift == false && aCtrl == true && aAlt == false) {
                aNode->mConstraint.mOffsetY = 0.0f;
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
            } else {
                mConstrainYToPoint = !mConstrainYToPoint;
                if (mConstrainYToPoint) {
                    mConstrainXToPoint = false;
                }
            }
        }
        
        if (pKey == __KEY__L) {
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_SPAWN) {
                aNode->mConstraint.mTypeX = X_CONSTRAINT_LEFT_PEEK;
            } else if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_PEEK) {
                aNode->mConstraint.mTypeX = X_CONSTRAINT_LEFT_QUARTER;
            } else if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_QUARTER) {
                aNode->mConstraint.mTypeX = X_CONSTRAINT_CENTER;
            } else if (aNode->mConstraint.mTypeX == X_CONSTRAINT_CENTER) {
                aNode->mConstraint.mTypeX = X_CONSTRAINT_RIGHT_QUARTER;
            } else if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_QUARTER) {
                aNode->mConstraint.mTypeX = X_CONSTRAINT_RIGHT_PEEK;
            } else if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_PEEK) {
                aNode->mConstraint.mTypeX = X_CONSTRAINT_RIGHT_SPAWN;
            }else if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_SPAWN) {
                aNode->mConstraint.mTypeX = X_CONSTRAINT_LEFT_SPAWN;
            } else {
                aNode->mConstraint.mTypeX = X_CONSTRAINT_LEFT_SPAWN;
            }
            
            if (mWave != NULL) {
                mWave->ApplyEditorConstraints();
            }
            if (mPerm != NULL) {
                mPerm->ApplyEditorConstraints();
            }
        }
        
        if (pKey == __KEY__U) {
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_SPAWN) {
                aNode->mConstraint.mTypeY = Y_CONSTRAINT_TOP_PEEK;
            } else if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_PEEK) {
                aNode->mConstraint.mTypeY = Y_CONSTRAINT_TOP_QUARTER;
            } else if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_QUARTER) {
                aNode->mConstraint.mTypeY = Y_CONSTRAINT_CENTER;
            } else if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_CENTER) {
                aNode->mConstraint.mTypeY = Y_CONSTRAINT_BOTTOM_QUARTER;
            } else if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) {
                aNode->mConstraint.mTypeY = Y_CONSTRAINT_BOTTOM;
            } else if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM) {
                aNode->mConstraint.mTypeY = Y_CONSTRAINT_TOP_SPAWN;
            } else {
                aNode->mConstraint.mTypeY = Y_CONSTRAINT_TOP_SPAWN;
            }
            
            if (mWave != NULL) {
                mWave->ApplyEditorConstraints();
            }
            if (mPerm != NULL) {
                mPerm->ApplyEditorConstraints();
            }
        }
    }
    
    
    if (aNode) {
        
        if (pKey == __KEY__LEFT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftX(-1.0f);
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftX(-10.0f);
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                ConstraintXToPrev();
            }
        }
        if (pKey == __KEY__RIGHT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftX(1.0f);
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftX(10.0f);
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                ConstraintXToNext();
                
            }
        }
        if (pKey == __KEY__UP) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftY(-1.0f);
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftY(-10.0f);
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                ConstraintYToPrev();
                
            }
        }
        if (pKey == __KEY__DOWN) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftY(1.0f);
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
                
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftY(10.0f);
                if (mWave != NULL) {
                    mWave->ApplyEditorConstraints();
                }
                if (mPerm != NULL) {
                    mPerm->ApplyEditorConstraints();
                }
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                ConstraintYToNext();
            }
        }
    }
}

void GamePathEditor::KeyUp(int pKey) {
    
}

void GamePathEditor::Notify(void *pSender, const char *pNotification) {
    
}

void GamePathEditor::Load() {
    
}

void GamePathEditor::Close() {
    if (mEditor != NULL) {
        mEditor->ClosePathEditor();
    }
    
    if (mPermanentEditor != NULL) {
        mPermanentEditor->ClosePathEditor();
    }
}

void GamePathEditor::SetUp(LevelWaveBlueprint *pWave) {
    mWave = NULL;
    mPath = NULL;
    mPerm = NULL;
    if (pWave == NULL) {
        return;
    }
    mWave = pWave;
    SetUpPath(&(pWave->mPath));
    
    
    mGrid.mCenterX = gEditor->mCenterH;
    mGrid.mCenterY = gEditor->mCenterV;
    mGrid.BuildGrid();
}

void GamePathEditor::SetUp(LevelSectionPermanentBlueprint *pPerm) {
    mWave = NULL;
    mPath = NULL;
    mPerm = NULL;
    if (pPerm == NULL) {
        return;
    }
    mPerm = pPerm;
    SetUpPath(&(mPerm->mPath));
    
    mGrid.mCenterX = mPerm->mEditorX;
    if (mPerm->mConstraint.mTypeX != X_CONSTRAINT_NONE) {
        float aFactorX = (gEditor->mGameAreaRight - gEditor->mGameAreaLeft) / (gGame->mGameAreaRight - gGame->mGameAreaLeft);
        mGrid.mCenterX += mPerm->mConstraint.mOffsetX * aFactorX;
    }
    
    mGrid.mCenterY = mPerm->mEditorY;
    if (mPerm->mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
        float aFactorY = (gEditor->mGameAreaBottom - gEditor->mGameAreaTop) / (gGame->mGameAreaBottom - gGame->mGameAreaTop);
        mGrid.mCenterY += mPerm->mConstraint.mOffsetY * aFactorY;
    }
    mGrid.BuildGrid();
}

void GamePathEditor::SetUpPath(LevelPathBlueprint *pPath) {
    
    if (gGame != NULL) {
        gGame->DisposeAllObjects();
    }
    
    mPath = pPath;
    mSelectedTouch = NULL;
    
    if (mPath->mNodeList.mCount > 0) {
        mPathMode = PATH_MODE_SELECT;
    } else {
        mPathMode = PATH_MODE_CREATE;
    }
}


void GamePathEditor::PathRefresh() {
    //if (mWave == NULL) { return; }
    if (mWave != NULL) {
        mWave->Build();
    }
    if (mPerm != NULL) {
        
    }
    
    if (gEditor != NULL) {
        gEditor->RefreshPlayback();
    }
}

void GamePathEditor::PathReset() {
    if (mPath == NULL) { return; }
    mPath->Reset();
}

void GamePathEditor::PathPrint() {
    if (mPath == NULL) { return; }
    FJSONNode *aSave = mPath->Save();
    FJSON aJSON;
    aJSON.mRoot = aSave;
    aJSON.Print();
}

void GamePathEditor::PathDeletePoint() {
    if (mPath == NULL) { return; }
    if (mPath->mSelectedIndex == -1) { return; }
    mPath->Remove(mPath->mSelectedIndex);
    if (mWave != NULL) {
        mWave->ApplyEditorConstraints();
    }
    if (mPerm != NULL) {
        mPerm->ApplyEditorConstraints();
    }
}

void GamePathEditor::ConstrainXToPoint() {
    if (mPath == NULL) { return; }
    if (mPath->mSelectedIndex == -1) { return; }
    mConstrainXToPoint = true;
}

void GamePathEditor::ConstrainYToPoint() {
    if (mPath == NULL) { return; }
    if (mPath->mSelectedIndex == -1) { return; }
    mConstrainYToPoint = true;
}

void GamePathEditor::ConstraintXToType(int pType) {
    if (mPath == NULL) { return; }
    if (mPath->mSelectedIndex == -1) { return; }
    mPath->SetSnapXType(pType);
}

void GamePathEditor::ConstraintYToType(int pType) {
    if (mPath == NULL) { return; }
    if (mPath->mSelectedIndex == -1) { return; }
    mPath->SetSnapYType(pType);
}


void GamePathEditor::ConstraintXToPrev() {
    if (mPath == NULL) { return; }
    LevelPathNodeBlueprint *aNode = mPath->GetNode();
    if (aNode == NULL) { return; }
    aNode->mConstraint.mTypeX = gEditor->PrevXConstraintf(aNode->mEditorX);
    if (mWave != NULL) {
        mWave->ApplyEditorConstraints();
    }
    if (mPerm != NULL) {
        mPerm->ApplyEditorConstraints();
    }
}

void GamePathEditor::ConstraintXToNext() {
    if (mPath == NULL) { return; }
    LevelPathNodeBlueprint *aNode = mPath->GetNode();
    if (aNode == NULL) { return; }
    aNode->mConstraint.mTypeX = gEditor->NextXConstraintf(aNode->mEditorX);
    if (mWave != NULL) {
        mWave->ApplyEditorConstraints();
    }
    if (mPerm != NULL) {
        mPerm->ApplyEditorConstraints();
    }
}

void GamePathEditor::ConstraintYToPrev() {
    if (mPath == NULL) { return; }
    LevelPathNodeBlueprint *aNode = mPath->GetNode();
    if (aNode == NULL) { return; }
    aNode->mConstraint.mTypeY = gEditor->PrevYConstraintf(aNode->mEditorY);
    if (mWave != NULL) {
        mWave->ApplyEditorConstraints();
    }
    if (mPerm != NULL) {
        mPerm->ApplyEditorConstraints();
    }
}

void GamePathEditor::ConstraintYToNext() {
    if (mPath == NULL) { return; }
    LevelPathNodeBlueprint *aNode = mPath->GetNode();
    if (aNode == NULL) { return; }
    aNode->mConstraint.mTypeY = gEditor->NextYConstraintf(aNode->mEditorY);
    if (mWave != NULL) {
        mWave->ApplyEditorConstraints();
    }
    if (mPerm != NULL) {
        mPerm->ApplyEditorConstraints();
    }
}


