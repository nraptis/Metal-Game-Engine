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
    
    
    mPathMode = PATH_MODE_CREATE;
    
    
    
    mName = "[GamePathEditor]";
    
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
    
    mMenuPaths = new EditorMenuPath(this);
    AddChild(mMenuPaths);
    mMenuPaths->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 20.0f, 400.0f, 680.0f);
    
    mMenuControls = new EditorMenuPathControl(this);
    AddChild(mMenuControls);
    mMenuControls->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f), gSafeAreaInsetTop + 20.0f, 400.0f, 480.0f);
}

GamePathEditor::~GamePathEditor() {
    
}

void GamePathEditor::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    FCanvas::SetFrame(pX, pY, pWidth, pHeight);
    
}

void GamePathEditor::Layout() {
    
}

void GamePathEditor::Update() {
    
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
        if (mPath && mWave) {
            mPath->Add(pX, pY);
            mPath->mSelectedIndex = mPath->mNodeList.mCount - 1;
            
            LevelWavePathBlueprintNode *aNode = mPath->GetNode();
            if (aNode) {
                aNode->mConstraint.mTypeX = gEditor->ClosestXConstraint(pX);
                aNode->mConstraint.mTypeY = gEditor->ClosestYConstraint(pY);
                mWave->ApplyEditorConstraints();
                
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
            mPath->Set(mPath->mSelectedIndex, mSelectPathStartX + (pX - mSelectTouchStartX), mSelectPathStartY + (pY - mSelectTouchStartY));
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
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (mWave == NULL) { return; }
    if (mPath == NULL) { return; }
    LevelWavePathBlueprintNode *aNode = mPath->GetNode();
    
    if (pKey == __KEY__P) {
        PathPrint();
    }
    
    
    if (pKey == __KEY__DELETE) {
        if (aShift == false && aCtrl == false && aAlt == false) { PathDeletePoint(); }
    }
    
    if (pKey == __KEY__A) {
        if (aShift == false && aCtrl == false && aAlt == false) { mPathMode = PATH_MODE_CREATE; }
        
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
                mWave->ApplyEditorConstraints();
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
                mWave->ApplyEditorConstraints();
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
            mWave->ApplyEditorConstraints();
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
            mWave->ApplyEditorConstraints();
        }
    }
    
    
    if (aNode) {
        
        if (pKey == __KEY__LEFT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftX(-1.0f);
                mWave->ApplyEditorConstraints();
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftX(-10.0f);
                mWave->ApplyEditorConstraints();
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                ConstraintXToPrev();
            }
        }
        if (pKey == __KEY__RIGHT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftX(1.0f);
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftX(10.0f);
                mWave->ApplyEditorConstraints();
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                ConstraintXToNext();
                
            }
        }
        if (pKey == __KEY__UP) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftY(-1.0f);
                mWave->ApplyEditorConstraints();
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftY(-10.0f);
                mWave->ApplyEditorConstraints();
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                ConstraintYToPrev();
                
            }
        }
        if (pKey == __KEY__DOWN) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftY(1.0f);
                mWave->ApplyEditorConstraints();
                
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftY(10.0f);
                mWave->ApplyEditorConstraints();
                
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
    mEditor->ClosePathEditor();
}

void GamePathEditor::SetUp(LevelWaveBlueprint *pWave) {
    if (pWave == NULL) {
        mWave = NULL;
        mPath = NULL;
        return;
    }
    mWave = pWave;
    mPath = &(pWave->mPath);
    mSelectedTouch = NULL;
    
    if (mPath->mNodeList.mCount > 0) {
        mPathMode = PATH_MODE_SELECT;
    } else {
        mPathMode = PATH_MODE_CREATE;
    }
}

void GamePathEditor::PathRefresh() {
    if (mWave == NULL) { return; }
    mWave->Build();
}

void GamePathEditor::PathReset() {
    if (mPath == NULL) { return; }
    mPath->Clear();
}

void GamePathEditor::PathPrint() {
    if (mPath == NULL) { return; }
    FJSONNode *aSave = mPath->Save();
    FJSON aJSON;
    aJSON.mRoot = aSave;
    aJSON.Print();
}

void GamePathEditor::PathDeletePoint() {
    if (mWave == NULL || mPath == NULL) { return; }
    if (mPath->mSelectedIndex == -1) { return; }
    mPath->Remove(mPath->mSelectedIndex);
    mWave->ApplyEditorConstraints();
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
    if (mWave == NULL || mPath == NULL) { return; }
    LevelWavePathBlueprintNode *aNode = mPath->GetNode();
    if (aNode == NULL) { return; }
    aNode->mConstraint.mTypeX = gEditor->PrevXConstraintf(aNode->mEditorX);
    mWave->ApplyEditorConstraints();
}

void GamePathEditor::ConstraintXToNext() {
    if (mWave == NULL || mPath == NULL) { return; }
    LevelWavePathBlueprintNode *aNode = mPath->GetNode();
    if (aNode == NULL) { return; }
    aNode->mConstraint.mTypeX = gEditor->NextXConstraintf(aNode->mEditorX);
    mWave->ApplyEditorConstraints();
}

void GamePathEditor::ConstraintYToPrev() {
    if (mWave == NULL || mPath == NULL) { return; }
    LevelWavePathBlueprintNode *aNode = mPath->GetNode();
    if (aNode == NULL) { return; }
    aNode->mConstraint.mTypeY = gEditor->PrevYConstraintf(aNode->mEditorY);
    mWave->ApplyEditorConstraints();
}

void GamePathEditor::ConstraintYToNext() {
    if (mWave == NULL || mPath == NULL) { return; }
    LevelWavePathBlueprintNode *aNode = mPath->GetNode();
    if (aNode == NULL) { return; }
    aNode->mConstraint.mTypeY = gEditor->NextYConstraintf(aNode->mEditorY);
    mWave->ApplyEditorConstraints();
}


