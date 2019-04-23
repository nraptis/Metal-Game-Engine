//
//  LevelPathBlueprintBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelPathBlueprint.hpp"
#include "LevelSectionPermanentBlueprint.hpp"
#include "os_core_graphics.h"
#include "FSpline.hpp"
#include "FPolyPath.hpp"
#include "core_includes.h"
#include "GameEditor.hpp"
#include "FLine.hpp"


LevelPathNodeBlueprint::LevelPathNodeBlueprint() {
    mEditorX = 0.0f; mEditorY = 0.0f;
    mPercentX = 0.0f; mPercentY = 0.0f;
    mBaseGameX = 0.0f; mBaseGameY = 0.0f;
    mGameX = 0.0f; mGameY = 0.0f;
    
    mType = -1;
    mWaitTimer = 0;
    mChamferSize = 0;
    
    mDecelDistance = 0;
    mAccelDistance = 0;
    
    mKillTimer = 8;
}

LevelPathNodeBlueprint::~LevelPathNodeBlueprint() {
    
}

void LevelPathNodeBlueprint::ShiftX(float pShiftX) {
    if (mConstraint.mTypeX == X_CONSTRAINT_NONE) {
        mEditorX = mEditorX + pShiftX;
    } else {
        mConstraint.mOffsetX += pShiftX;
    }
}

void LevelPathNodeBlueprint::ShiftY(float pShiftY) {
    if (mConstraint.mTypeY == Y_CONSTRAINT_NONE) {
        mEditorY = mEditorY + pShiftY;
    } else {
        mConstraint.mOffsetY += pShiftY;
    }
}

FJSONNode *LevelPathNodeBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    if (mConstraint.mTypeX == X_CONSTRAINT_NONE) {
        
        float aLeft = gEditor->mGameAreaLeft;
        float aRight = gEditor->mGameAreaRight;
        
        //100x percision
        float aX = (mEditorX - aLeft) / (aRight - aLeft) * 100.0f;
        aExport->AddDictionaryFloat("x", aX);
    } else {
        if (mConstraint.mTypeX != X_CONSTRAINT_NONE) {
            aExport->AddDictionaryInt("x_con", mConstraint.mTypeX);
        }
        if (mConstraint.mOffsetX != 0.0f) {
            aExport->AddDictionaryFloat("x_con_offset", mConstraint.mOffsetX);
        }
        if (mConstraint.mTargetX != -1 && mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
            aExport->AddDictionaryInt("x_con_target", mConstraint.mTargetX);
        }
    }
    
    if (mConstraint.mTypeY == Y_CONSTRAINT_NONE) {
        float aTop = gEditor->mGameAreaTop;
        float aBottom = gEditor->mGameAreaBottom;
        //100x percision
        float aY = (mEditorY - aTop) / (aBottom - aTop) * 100.0f;
        aExport->AddDictionaryFloat("y", aY);
    } else {
        if (mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
            aExport->AddDictionaryInt("y_con", mConstraint.mTypeY);
        }
        if (mConstraint.mOffsetY != 0.0f) {
            aExport->AddDictionaryFloat("y_con_offset", mConstraint.mOffsetY);
        }
        if (mConstraint.mTargetY != -1 && mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
            aExport->AddDictionaryInt("y_con_target", mConstraint.mTargetY);
        }
    }
    
    if (mDecelDistance > 0) {
        aExport->AddDictionaryInt("decel", mDecelDistance);
    }
    
    if (mAccelDistance > 0) {
        aExport->AddDictionaryInt("accel", mAccelDistance);
    }
    
    if (mChamferSize > 0) {
        aExport->AddDictionaryInt("chamfer", mChamferSize);
    }
    
    if (mWaitTimer > 0) {
        aExport->AddDictionaryInt("wait", mWaitTimer);
    }
    
    return aExport;
}

void LevelPathNodeBlueprint::Load(FJSONNode *pNode) {
    
    if (pNode == NULL) { return; }
    
    mConstraint.mTypeX = pNode->GetInt("x_con", X_CONSTRAINT_NONE);
    mConstraint.mTargetX = pNode->GetInt("x_con_target", -1);
    mConstraint.mOffsetX = pNode->GetFloat("x_con_offset", 0.0f);
    
    mConstraint.mTypeY = pNode->GetInt("y_con", Y_CONSTRAINT_NONE);
    mConstraint.mTargetY = pNode->GetInt("y_con_target", -1);
    mConstraint.mOffsetY = pNode->GetFloat("y_con_offset", 0.0f);
    
    mPercentX = 0.0f;
    mPercentX = pNode->GetFloat("x", mPercentX);
    
    if (gEditor != NULL) {
        float aLeft = gEditor->mGameAreaLeft;
        float aRight = gEditor->mGameAreaRight;
        mEditorX = aLeft + (aRight - aLeft) * (mPercentX / 100.0f);
    }
    
    mPercentY = 0.0f;
    mPercentY = pNode->GetFloat("y", mPercentY);
    if (gEditor != NULL) {
        float aTop = gEditor->mGameAreaTop;
        float aBottom = gEditor->mGameAreaBottom;
        mEditorY = aTop + (aBottom - aTop) * (mPercentY / 100.0f);
    }
    
    
    mChamferSize = pNode->GetInt("chamfer", 0);
    mWaitTimer = pNode->GetInt("wait", 0);
    mDecelDistance = pNode->GetInt("decel", 0);
    mAccelDistance = pNode->GetInt("accel", 0);
    
}

LevelPathBlueprint::LevelPathBlueprint() {
    mWave = NULL;
    mPerm = NULL;
    mSpeedClass = SPEED_CLASS_MEDIUM;
    mSmooth = false;
    mClosed = false;
    mMaxSpawnSize = 0;
}

LevelPathBlueprint::~LevelPathBlueprint() {
    FreeList(LevelPathNodeBlueprint, mNodeList);
    FreeList(LevelPathNodeBlueprint, mKillList);
}

void LevelPathBlueprint::Update() {
    
    RefreshNodePositions();
    
    EnumList(LevelPathNodeBlueprint, aNode, mKillList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteList.Add(aNode); }
    }
    EnumList(LevelPathNodeBlueprint, aNode, mDeleteList) {
        mKillList.Remove(aNode);
        delete aNode;
    }
    mDeleteList.RemoveAll();
}

void LevelPathBlueprint::Reset() {
    
    EnumList(LevelPathNodeBlueprint, aNode, mNodeList) {
        mKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
    
    mSelectedIndex = -1;
    
    if (gEditor != NULL) {
        RefreshNodePositions();
        ApplyEditorConstraints();
    }
}

void LevelPathBlueprint::Draw(bool pSelected) {
    
    int aStartIndex = 1;
    if (mClosed) {
        aStartIndex = 0;
    }
    
    for (int i=aStartIndex;i<mNodeList.mCount;i++) {
        LevelPathNodeBlueprint *aNode1 = (LevelPathNodeBlueprint *)mNodeList.FetchCircular(i - 1);
        LevelPathNodeBlueprint *aNode2 = (LevelPathNodeBlueprint *)mNodeList.FetchCircular(i);
        
        float aX1 = aNode1->mEditorX;
        //if (aNode1->mConstraint.mTypeX != X_CONSTRAINT_NONE) { aX1 += aNode1->mConstraint.mOffsetX; }
        
        float aY1 = aNode1->mEditorY;
        //if (aNode1->mConstraint.mTypeY != Y_CONSTRAINT_NONE) { aY1 += aNode1->mConstraint.mOffsetY; }
        
        
        float aX2 = aNode2->mEditorX;
        //if (aNode2->mConstraint.mTypeX != X_CONSTRAINT_NONE) { aX2 += aNode2->mConstraint.mOffsetX; }
        
        float aY2 = aNode2->mEditorY;
        //if (aNode2->mConstraint.mTypeY != Y_CONSTRAINT_NONE) { aY2 += aNode2->mConstraint.mOffsetY; }
        
        
        if (pSelected) {
            Graphics::SetColor(0.75f, 0.75f, 0.75f, 0.25f);
            Graphics::DrawLine(aX1, aY1, aX2, aY2, 1.5f);
            
        } else {
            Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.25f);
            Graphics::DrawLine(aX1, aY1, aX2, aY2, 1.0f);
        }
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
        
        float aX = aNode->mEditorX;
        if (aNode->mConstraint.mTypeX != X_CONSTRAINT_NONE) { aX += aNode->mConstraint.mOffsetX; }
        
        float aY = aNode->mEditorY;
        if (aNode->mConstraint.mTypeY != Y_CONSTRAINT_NONE) { aY += aNode->mConstraint.mOffsetY; }

        if (pSelected) {
            if (i == mSelectedIndex) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aX, aY, 12.0f);
            } else {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aX, aY, 6.0f);
            }
        } else {
            Graphics::SetColor(0.65f, 0.65f, 0.65f, 0.35f);
            Graphics::DrawPoint(aX, aY, 4.0f);
        }
        
        if (pSelected) {
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                Graphics::SetColor(0.125f, 0.125f, 1.0f, 1.0f);
                Graphics::DrawLine(aNode->mEditorX, aNode->mEditorY - 10.0f, aNode->mEditorX, aNode->mEditorY + 10.0f);
            } else if (aNode->mConstraint.mTypeX != X_CONSTRAINT_NONE) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 1.0f);
                Graphics::DrawLine(aNode->mEditorX, aNode->mEditorY - 10.0f, aNode->mEditorX, aNode->mEditorY + 10.0f);
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                Graphics::SetColor(0.125f, 0.125f, 1.0f, 1.0f);
                Graphics::DrawLine(aNode->mEditorX - 10.0f, aNode->mEditorY, aNode->mEditorX + 10.0f, aNode->mEditorY);
            } else if (aNode->mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 1.0f);
                Graphics::DrawLine(aNode->mEditorX - 10.0f, aNode->mEditorY, aNode->mEditorX + 10.0f, aNode->mEditorY);
            }
        } else {
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                Graphics::SetColor(0.125f, 0.125f, 1.0f, 0.5f);
                Graphics::DrawLine(aNode->mEditorX, aNode->mEditorY - 10.0f, aNode->mEditorX, aNode->mEditorY + 10.0f);
            } else if (aNode->mConstraint.mTypeX != X_CONSTRAINT_NONE) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.5f);
                Graphics::DrawLine(aNode->mEditorX, aNode->mEditorY - 10.0f, aNode->mEditorX, aNode->mEditorY + 10.0f);
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                Graphics::SetColor(0.125f, 0.125f, 1.0f, 0.5f);
                Graphics::DrawLine(aNode->mEditorX - 10.0f, aNode->mEditorY, aNode->mEditorX + 10.0f, aNode->mEditorY);
            } else if (aNode->mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.5f);
                Graphics::DrawLine(aNode->mEditorX - 10.0f, aNode->mEditorY, aNode->mEditorX + 10.0f, aNode->mEditorY);
            }
        }
        
    }
}

float LevelPathBlueprint::GetX(int pIndex) {
    LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorX; }
    return 0.0f;
}

float LevelPathBlueprint::GetY(int pIndex) {
    LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorY; }
    return 0.0f;
}

void LevelPathBlueprint::Set(int pIndex, float pX, float pY) {
    LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) {
        aNode->mEditorX = pX;
        aNode->mEditorY = pY;
        if (aNode->mConstraint.mTypeX != X_CONSTRAINT_TARGET &&
            aNode->mConstraint.mTypeX != X_CONSTRAINT_NONE) {
            if (gEditor != NULL) {
                aNode->mConstraint.mTypeX = gEditor->ClosestXConstraint(pX);
            }
        }
        if (aNode->mConstraint.mTypeY != Y_CONSTRAINT_TARGET &&
            aNode->mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
            if (gEditor != NULL) {
                aNode->mConstraint.mTypeY = gEditor->ClosestYConstraint(pY);
            }
        }
        RefreshNodePositions();
        ApplyEditorConstraints();
    }
}

void LevelPathBlueprint::Add(float pX, float pY) {
    LevelPathNodeBlueprint *aNode = new LevelPathNodeBlueprint();
    aNode->mEditorX = pX;
    aNode->mEditorY = pY;
    mNodeList.Add(aNode);
    RefreshNodePositions();
    ApplyEditorConstraints();
}

void LevelPathBlueprint::Remove(int pIndex) {
    LevelPathNodeBlueprint *aDeleteNode = (LevelPathNodeBlueprint *)mNodeList.Fetch(pIndex);
    if (aDeleteNode) {
        for (int i=0;i<mNodeList.mCount;i++) {
            LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                if (aNode->mConstraint.mTargetX == pIndex) {
                    aNode->mConstraint.mTypeX = X_CONSTRAINT_NONE;
                } else if (aNode->mConstraint.mTargetX > pIndex) {
                    aNode->mConstraint.mTargetX -= 1;
                }
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                if (aNode->mConstraint.mTargetY == pIndex) {
                    aNode->mConstraint.mTypeY = Y_CONSTRAINT_NONE;
                } else if (aNode->mConstraint.mTargetY > pIndex) {
                    aNode->mConstraint.mTargetY -= 1;
                }
            }
        }
        if (mSelectedIndex >= pIndex) { mSelectedIndex--; }
        mKillList.Add(aDeleteNode);
        mNodeList.RemoveAtIndex(pIndex);
    }
    ApplyEditorConstraints();
}

LevelPathNodeBlueprint *LevelPathBlueprint::GetNode(int pIndex) {
    LevelPathNodeBlueprint *aResult = (LevelPathNodeBlueprint *)mNodeList.Fetch(pIndex);
    return aResult;
}

LevelPathNodeBlueprint *LevelPathBlueprint::GetNode() {
    LevelPathNodeBlueprint *aResult = (LevelPathNodeBlueprint *)mNodeList.Fetch(mSelectedIndex);
    return aResult;
}

void LevelPathBlueprint::RefreshNodePositions() {
    
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
        aNode->mPercentX = (aNode->mEditorX - aLeft) / (aRight - aLeft) * 100.0f;
        aNode->mPercentY = (aNode->mEditorY - aTop) / (aBottom - aTop) * 100.0f;
        
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_NONE) {
            aNode->mConstraint.mOffsetX = 0.0f;
        }
        if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_NONE) {
            aNode->mConstraint.mOffsetY = 0.0f;
        }
    }
}

int LevelPathBlueprint::GetClosestIndex(float pX, float pY, float &pDist) {
    int aResult = -1;
    if (mNodeList.mCount > 0) {
        LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.First();
        
        aResult = 0;
        float aCheckDist = pDist;
        float aDiffX = aNode->mEditorX - pX;
        float aDiffY = aNode->mEditorY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        pDist = aDist;
        for (int i=1;i<mNodeList.mCount;i++) {
            aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
            aDiffX = aNode->mEditorX - pX;
            aDiffY = aNode->mEditorY - pY;
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            if (aDist < pDist) {
                pDist = aDist;
                aResult = i;
            }
        }
        if (pDist > aCheckDist) { aResult = -1; }
    }
    
    return aResult;
}

void LevelPathBlueprint::GetClosestPointOnLine(float pX, float pY, float &pDist) {
    for (int i=1;i<mNodeList.mCount;i++) {
        LevelPathNodeBlueprint *aNode1 = (LevelPathNodeBlueprint *)mNodeList.mData[i-1];
        LevelPathNodeBlueprint *aNode2 = (LevelPathNodeBlueprint *)mNodeList.mData[i];
        
        float aClosestX = 0.0f;
        float aClosestY = 0.0f;
        
        FLine::SegmentClosestPoint(aNode1->mEditorX, aNode1->mEditorY, aNode2->mEditorX, aNode2->mEditorY, pX, pY, aClosestX, aClosestY);
        
        float aDiffX = aClosestX - pX;
        float aDiffY = aClosestY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        if (aDist < pDist) {
            pDist = aDist;
        }
    }
}

void LevelPathBlueprint::SnapX(int pIndex) {
    
    LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL && pIndex >= 0 && pIndex < mNodeList.mCount) {
        aNode->mConstraint.mTypeX = X_CONSTRAINT_TARGET;
        aNode->mConstraint.mTargetX = pIndex;
    }
    ApplyEditorConstraints();
}

void LevelPathBlueprint::SnapY(int pIndex) {
    LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL && pIndex >= 0 && pIndex < mNodeList.mCount) {
        aNode->mConstraint.mTypeY = Y_CONSTRAINT_TARGET;
        aNode->mConstraint.mTargetY = pIndex;
    }
    ApplyEditorConstraints();
}

void LevelPathBlueprint::SetSnapXType(int pType) {
    LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL) {
        aNode->mConstraint.mTypeX = pType;
    }
    ApplyEditorConstraints();
}

void LevelPathBlueprint::SetSnapYType(int pType) {
    LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL) {
        aNode->mConstraint.mTypeY = pType;
    }
    ApplyEditorConstraints();
}

void LevelPathBlueprint::ApplyEditorConstraints() {
    
    for (int aLoops = 0;aLoops<40;aLoops++) {
        for (int i=0;i<mNodeList.mCount;i++) {
            LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
            
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                LevelPathNodeBlueprint *aTarget = (LevelPathNodeBlueprint *)mNodeList.mData[aNode->mConstraint.mTargetX];
                if (aTarget != 0) {
                    aNode->mEditorX = aTarget->mEditorX;
                }
            }
            
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                LevelPathNodeBlueprint *aTarget = (LevelPathNodeBlueprint *)mNodeList.mData[aNode->mConstraint.mTargetY];
                if (aTarget != 0) {
                    aNode->mEditorY = aTarget->mEditorY;
                }
            }
            
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_EXIT) { aNode->mEditorX = gEditor->mExitZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_SPAWN) { aNode->mEditorX = gEditor->mSpawnZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_PEEK) { aNode->mEditorX = gEditor->mPeekZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_QUARTER) { aNode->mEditorX = gEditor->mQuarterZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_CENTER) { aNode->mEditorX = gEditor->mCenterH; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_QUARTER) { aNode->mEditorX = gEditor->mQuarterZoneRight; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_PEEK) { aNode->mEditorX = gEditor->mPeekZoneRight; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_SPAWN) { aNode->mEditorX = gEditor->mSpawnZoneRight; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_EXIT) { aNode->mEditorX = gEditor->mExitZoneRight; }
            
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_EXIT) { aNode->mEditorY = gEditor->mExitZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_SPAWN) { aNode->mEditorY = gEditor->mSpawnZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_PEEK) { aNode->mEditorY = gEditor->mPeekZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_QUARTER) { aNode->mEditorY = gEditor->mQuarterZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_CENTER) { aNode->mEditorY = gEditor->mCenterV; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) { aNode->mEditorY = gEditor->mQuarterZoneBottom; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM) { aNode->mEditorY = gEditor->mPlayZoneBottom; }
        }
    }
}

int LevelPathBlueprint::GetExitType() {
    LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.Last();
    if (aNode != NULL) {
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_EXIT) { return WAVE_EXIT_TYPE_INSTANT; }
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_EXIT) { return WAVE_EXIT_TYPE_INSTANT; }
        if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_EXIT) { return WAVE_EXIT_TYPE_INSTANT; }
    }
    return WAVE_EXIT_TYPE_DISPERSE;
}


void LevelPathBlueprint::Build(LevelPath *pPath) {
    
    if (pPath == NULL) { return; }
    
    pPath->Reset();
    
    pPath->mSmooth = mSmooth;
    pPath->mClosed = mClosed;
    pPath->SetSpeedClass(mSpeedClass);
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
        
        FVec2 aPoint;
        aPoint.mX = aNode->mPercentX / 100.0f;
        aPoint.mY = aNode->mPercentY / 100.0f;
        
        if (aNode->mConstraint.HasX()) {
            aPoint.mX = aNode->mConstraint.GameX(false);
            
            if (i == 0) {
                if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_SPAWN) {
                    aPoint.mX -= mMaxSpawnSize;
                }
                if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_SPAWN) {
                    aPoint.mX += mMaxSpawnSize;
                }
            }
            
            if (i == (mNodeList.mCount - 1)) {
                if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_EXIT) {
                    aPoint.mX -= mMaxSpawnSize;
                }
                if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_EXIT) {
                    aPoint.mX += mMaxSpawnSize;
                }
            }
            aNode->mBaseGameX = aPoint.mX;
        } else {
            aNode->mBaseGameX = gGame->mGameAreaLeft + (gGame->mGameAreaRight - gGame->mGameAreaLeft) * aPoint.mX;
        }
        
        if (aNode->mConstraint.HasY()) {
            aPoint.mY = aNode->mConstraint.GameY(false);
            if (i == 0) {
                if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_SPAWN) {
                    aPoint.mY -= mMaxSpawnSize;
                }
            }
            if (i == (mNodeList.mCount - 1)) {
                if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_EXIT) {
                    aPoint.mY -= mMaxSpawnSize;
                }
            }
            aNode->mBaseGameY = aPoint.mY;
        } else {
            aNode->mBaseGameY = gGame->mGameAreaTop + (gGame->mGameAreaBottom - gGame->mGameAreaTop) * aPoint.mY;
        }
    }
    
    for (int aLoops = 0;aLoops<20;aLoops++) {
        for (int i=0;i<mNodeList.mCount;i++) {
            LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                LevelPathNodeBlueprint *aTarget = (LevelPathNodeBlueprint *)mNodeList.mData[aNode->mConstraint.mTargetX];
                if (aTarget != 0) { aNode->mBaseGameX = aTarget->mBaseGameX + aTarget->mConstraint.mOffsetX; }
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                LevelPathNodeBlueprint *aTarget = (LevelPathNodeBlueprint *)mNodeList.mData[aNode->mConstraint.mTargetY];
                if (aTarget != 0) { aNode->mBaseGameY = aTarget->mBaseGameY + aTarget->mConstraint.mOffsetY; }
            }
        }
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
        
        if (aNode->mConstraint.HasX() || aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
            aNode->mGameX = aNode->mBaseGameX + aNode->mConstraint.mOffsetX;
        } else {
            aNode->mGameX = aNode->mBaseGameX;
        }
        
        if (aNode->mConstraint.HasY() || aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
            aNode->mGameY = aNode->mBaseGameY + aNode->mConstraint.mOffsetY;
        } else {
            aNode->mGameY = aNode->mBaseGameY;
        }
        
        printf("aNode->mGameX = %f aNode->mGameY = %f\n", aNode->mGameX, aNode->mGameY);
    }
    printf("=======\n");
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
        
        float aChamferSize = ((float) aNode->mChamferSize);
        if (aNode->mChamferSize > 0 &&
            i > 0 &&
            i < (mNodeList.mCount - 1)) {
            
            LevelPathNodeBlueprint *aPrevNode = (LevelPathNodeBlueprint *)mNodeList.mData[i - 1];
            LevelPathNodeBlueprint *aNextNode = (LevelPathNodeBlueprint *)mNodeList.mData[i + 1];
            
            float aDiffBackX = aPrevNode->mGameX - aNode->mGameX;
            float aDiffBackY = aPrevNode->mGameY - aNode->mGameY;
            
            float aDiffNextX = aNextNode->mGameX - aNode->mGameX;
            float aDiffNextY = aNextNode->mGameY - aNode->mGameY;
            
            float aLengthBack = aDiffBackX * aDiffBackX + aDiffBackY * aDiffBackY;
            float aLengthNext = aDiffNextX * aDiffNextX + aDiffNextY * aDiffNextY;
            
            if (aLengthBack > SQRT_EPSILON) {
                aLengthBack = sqrtf(aLengthBack);
                aDiffBackX /= aLengthBack;
                aDiffBackY /= aLengthBack;
                
            } else {
                aDiffBackX = 0.0f;
                aDiffBackY = -1.0f;
            }
            
            if (aLengthNext > SQRT_EPSILON) {
                aLengthNext = sqrtf(aLengthNext);
                aDiffNextX /= aLengthNext;
                aDiffNextY /= aLengthNext;
                
            } else {
                aDiffNextX = 0.0f;
                aDiffNextY = -1.0f;
            }
            
            pPath->AddMove(aNode->mGameX + aDiffBackX * aChamferSize,
                           aNode->mGameY + aDiffBackY * aChamferSize,
                           aNode->mAccelDistance,
                           aNode->mDecelDistance,
                           aNode->mWaitTimer);
            pPath->AddMove(aNode->mGameX + aDiffNextX * aChamferSize,
                           aNode->mGameY + aDiffNextY * aChamferSize,
                           0,
                           aNode->mWaitTimer);
        } else {
            pPath->AddMove(aNode->mGameX, aNode->mGameY, aNode->mAccelDistance, aNode->mDecelDistance, aNode->mWaitTimer);
        }
    }
    
}

FJSONNode *LevelPathBlueprint::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    if (mSmooth == true) {
        aExport->AddDictionaryBool("smooth", mSmooth);
    }
    
    if (mClosed == true) {
        aExport->AddDictionaryBool("closed", mClosed);
    }
    
    if (mSpeedClass != SPEED_CLASS_MEDIUM) {
        aExport->AddDictionaryInt("speed_class", mSpeedClass);
    }
    
    
    FJSONNode *aNodeListNode = new FJSONNode();
    aNodeListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mNodeList.mData[i];
        aNodeListNode->AddArray(aNode->Save());
    }
    aExport->AddDictionary("node_list", aNodeListNode);
    
    return aExport;
}

void LevelPathBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    mSmooth = pNode->GetBool("smooth", false);
    mClosed = pNode->GetBool("closed", false);
    
    mSpeedClass = pNode->GetInt("speed_class", SPEED_CLASS_MEDIUM);
    
    FJSONNode *aNodeListNode = pNode->GetArray("node_list");
    
    if (aNodeListNode != NULL) {
        EnumJSONArray(aNodeListNode, aPathLoadNode) {
            LevelPathNodeBlueprint *aPathNode = new LevelPathNodeBlueprint();
            aPathNode->Load(aPathLoadNode);
            mNodeList.Add(aPathNode);
        }
    }
}
