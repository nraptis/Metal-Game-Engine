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
    
    mSelectedTouch = NULL;
    
    mName = "[GamePathEditor]";
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    mConstrainXToPoint = false;
    mConstrainYToPoint = false;
    
    mSelectPathStartX = 0.0f;
    mSelectPathStartY = 0.0f;
    
    mSelectTouchStartX = 0.0f;
    mSelectTouchStartY = 0.0f;
    
    mPath = NULL;
    
    mMenuPaths = new EditorMenuPath(this);
    AddChild(mMenuPaths);
    mMenuPaths->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 40.0f, 360.0f, 680.0f);
    
    
    mMenuControls = new EditorMenuPathControl(this);
    AddChild(mMenuControls);
    mMenuControls->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 360.0f), gSafeAreaInsetTop + 40.0f, 360.0f, 480.0f);
    
    
    
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
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    if (mPath) {
        //mPath->Draw(true, mSelectedIndex);
    }
    
    
}

void GamePathEditor::TouchDown(float pX, float pY, void *pData) {
    if (mPath != NULL) {
        if (mConstrainXToPoint || mConstrainYToPoint) {
            float aDist = 50.0f * 50.0f;
            int aIndex = mPath->GetClosestIndex(pX, pY, aDist);
            if (aIndex != -1 && mPath->mSelectedIndex != -1 && mPath->mSelectedIndex != aIndex) {
                printf("SNAPPING %d to %d\n", aIndex, mPath->mSelectedIndex);
                if (mConstrainXToPoint) {
                    mPath->SnapX(aIndex);
                }
                if (mConstrainYToPoint) {
                    mPath->SnapY(aIndex);
                }
                mConstrainXToPoint = false;
                mConstrainYToPoint = false;
            } else {
                printf("CANNOT SNAP %d to %d\n", aIndex, mPath->mSelectedIndex);
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
            
            LevelWavePathBlueprintNode *aNode = mPath->GetNode();
            if (aNode) {
                aNode->mConstraint.mTypeX = gEditor->ClosestXConstraint(pX);
                aNode->mConstraint.mTypeY = gEditor->ClosestYConstraint(pY);
                mPath->ApplyEditorConstraints();
                
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
    
    bool aShift = os_is_shift_key_down();
    bool aCtrl = os_is_control_key_down();
    bool aAlt = os_is_alt_key_down();
    
    if (mPath == NULL) {
        return;
    }
    
    LevelWavePathBlueprintNode *aNode = mPath->GetNode();
    
    if (pKey == __KEY__P) {
        PathPrint();
    }
    
    if (pKey == __KEY__A) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            mPathMode = PATH_MODE_CREATE;
        }
    }
    
    if (pKey == __KEY__S) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            mPathMode = PATH_MODE_SELECT;
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
                mPath->ApplyEditorConstraints();
            } else {
                mConstrainXToPoint = !mConstrainXToPoint;
            }
        }
        
        if (pKey == __KEY__Y) {
            if (aShift == false && aCtrl == true && aAlt == false) {
                aNode->mConstraint.mOffsetY = 0.0f;
                mPath->ApplyEditorConstraints();
            } else {
                mConstrainYToPoint = !mConstrainYToPoint;
            }
        }
        
        if (pKey == __KEY__ESCAPE) {
            ConstraintXToType(X_CONSTRAINT_NONE);
            ConstraintYToType(Y_CONSTRAINT_NONE);
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
            mPath->ApplyEditorConstraints();
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
            mPath->ApplyEditorConstraints();
        }
    }
    
    
    if (aNode) {
        
        if (pKey == __KEY__LEFT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftX(-1.0f);
                mPath->ApplyEditorConstraints();
                mPath->Build();
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftX(-10.0f);
                mPath->ApplyEditorConstraints();
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                
                aNode->mConstraint.mTypeX = gEditor->PrevXConstraintf(aNode->mX);
                mPath->ApplyEditorConstraints();
            }
        }
        if (pKey == __KEY__RIGHT) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftX(1.0f);
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftX(10.0f);
                mPath->ApplyEditorConstraints();
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                aNode->mConstraint.mTypeX = gEditor->NextXConstraintf(aNode->mX);
                mPath->ApplyEditorConstraints();
                
            }
        }
        if (pKey == __KEY__UP) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftY(-1.0f);
                mPath->ApplyEditorConstraints();
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftY(-10.0f);
                mPath->ApplyEditorConstraints();
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                aNode->mConstraint.mTypeY = gEditor->PrevYConstraintf(aNode->mY);
                mPath->ApplyEditorConstraints();
                
            }
        }
        if (pKey == __KEY__DOWN) {
            if (aShift == false && aCtrl == false && aAlt == false) {
                aNode->ShiftY(1.0f);
                mPath->ApplyEditorConstraints();
                mPath->Build();
            } else if (aShift == true && aCtrl == false && aAlt == false) {
                aNode->ShiftY(10.0f);
                mPath->ApplyEditorConstraints();
                
            } else if (aShift == false && aCtrl == true && aAlt == false) {
                aNode->mConstraint.mTypeY = gEditor->NextYConstraintf(aNode->mY);
                mPath->ApplyEditorConstraints();
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
        mPath = NULL;
        return;
    }
    mPath = &(pWave->mPath);
    mSelectedTouch = NULL;
    
    if (mPath->mNodeList.mCount > 0) {
        mPathMode = PATH_MODE_SELECT;
    } else {
        mPathMode = PATH_MODE_CREATE;
    }
    
    
}

void GamePathEditor::PathRefresh() {
    if (mPath == NULL) { return; }
    mPath->Build();
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
    if (mPath == NULL) { return; }
    if (mPath->mSelectedIndex == -1) { return; }
    mPath->Remove(mPath->mSelectedIndex);
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
