//
//  LevelWavePathBlueprintBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWavePathBlueprint.hpp"
#include "os_core_graphics.h"
#include "FSpline.h"
#include "FPolyPath.h"
#include "core_includes.h"
#include "GameEditor.hpp"

static FPointList cPointList;
static FPointList cDumpList;
static FPolyPath cPolyPath;

LevelWavePathBlueprintNode::LevelWavePathBlueprintNode() {
    mX = 0.0f;
    mY = 0.0f;
    
    mBaseGameX = 0.0f;
    mBaseGameY = 0.0f;
    
    mGameX = 0.0f;
    mGameY = 0.0f;
    
    mType = -1;
    mWaitTimer = 0;
    mChamferSize = 0;
}

LevelWavePathBlueprintNode::~LevelWavePathBlueprintNode() {
    
}

void LevelWavePathBlueprintNode::ShiftX(float pShiftX) {
    if (mConstraint.mTypeX == X_CONSTRAINT_NONE) {
        mX = mX + pShiftX;
    } else {
        mConstraint.mOffsetX += pShiftX;
    }
}

void LevelWavePathBlueprintNode::ShiftY(float pShiftY) {
    if (mConstraint.mTypeY == Y_CONSTRAINT_NONE) {
        mY = mY + pShiftY;
    } else {
        mConstraint.mOffsetY += pShiftY;
    }
}

FJSONNode *LevelWavePathBlueprintNode::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    
    if (mConstraint.mTypeX == X_CONSTRAINT_NONE) {
        aExport->AddDictionaryFloat("x", mX);
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
        aExport->AddDictionaryFloat("y", mY);
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
    
    if (mChamferSize > 0) {
        aExport->AddDictionaryInt("chamfer", mChamferSize);
    }
    
    if (mWaitTimer > 0) {
        aExport->AddDictionaryInt("wait", mWaitTimer);
    }
    
    return aExport;
}

LevelWavePathBlueprint::LevelWavePathBlueprint() {
    mSmooth = true;
    mSpeed = 12.0f;
}



LevelWavePathBlueprint::~LevelWavePathBlueprint() {
    
}

void LevelWavePathBlueprint::Draw(bool pSelected) {
    for (int i=1;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode1 = (LevelWavePathBlueprintNode *)mNodeList.mData[i - 1];
        LevelWavePathBlueprintNode *aNode2 = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        if (pSelected) {
            Graphics::SetColor(0.75f, 0.75f, 0.75f, 0.25f);
            Graphics::DrawLine(aNode1->mX, aNode1->mY, aNode2->mX, aNode2->mY, 1.0f);
            
        } else {
            Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.1f);
            Graphics::DrawLine(aNode1->mX, aNode1->mY, aNode2->mX, aNode2->mY, 1.0f);
        }
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        if (pSelected) {
            if (i == mSelectedIndex) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aNode->mX, aNode->mY, 12.0f);
            } else {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aNode->mX, aNode->mY, 6.0f);
            }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                Graphics::SetColor(0.125f, 0.125f, 1.0f, 1.0f);
                Graphics::DrawLine(aNode->mX, aNode->mY - 10.0f, aNode->mX, aNode->mY + 10.0f);
            } else if (aNode->mConstraint.mTypeX != X_CONSTRAINT_NONE) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 1.0f);
                Graphics::DrawLine(aNode->mX, aNode->mY - 10.0f, aNode->mX, aNode->mY + 10.0f);
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                Graphics::SetColor(0.125f, 0.125f, 1.0f, 1.0f);
                Graphics::DrawLine(aNode->mX - 10.0f, aNode->mY, aNode->mX + 10.0f, aNode->mY);
            } else if (aNode->mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 1.0f);
                Graphics::DrawLine(aNode->mX - 10.0f, aNode->mY, aNode->mX + 10.0f, aNode->mY);
            }
        } else {
            Graphics::SetColor(0.65f, 0.65f, 0.65f, 0.35f);
            Graphics::DrawPoint(aNode->mX, aNode->mY, 3.0f);
        }
    }
}

float LevelWavePathBlueprint::GetX(int pIndex) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mX; }
    return 0.0f;
}

float LevelWavePathBlueprint::GetY(int pIndex) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mY; }
    return 0.0f;
}

void LevelWavePathBlueprint::Set(int pIndex, float pX, float pY) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) {
        aNode->mX = pX;
        aNode->mY = pY;
        ApplyEditorConstraints();
    }
}

void LevelWavePathBlueprint::Add(float pX, float pY) {
    LevelWavePathBlueprintNode *aNode = new LevelWavePathBlueprintNode();
    aNode->mX = pX;
    aNode->mY = pY;
    mNodeList.Add(aNode);
    ApplyEditorConstraints();
}

void LevelWavePathBlueprint::Remove(int pIndex) {
    
    LevelWavePathBlueprintNode *aDeleteNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aDeleteNode) {
        
        for (int i=0;i<mNodeList.mCount;i++) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
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
        
        if (mSelectedIndex >= pIndex) {
            mSelectedIndex--;
        }
        
        delete aDeleteNode;
        mNodeList.RemoveAtIndex(pIndex);
    }
    ApplyEditorConstraints();
}

void LevelWavePathBlueprint::Clear() {
    FreeList(LevelWavePathBlueprintNode, mNodeList);
    mSelectedIndex = -1;
    ApplyEditorConstraints();
}

LevelWavePathBlueprintNode *LevelWavePathBlueprint::GetNode(int pIndex) {
    LevelWavePathBlueprintNode *aResult = (LevelWavePathBlueprintNode *)mNodeList.Fetch(pIndex);
    return aResult;
}

LevelWavePathBlueprintNode *LevelWavePathBlueprint::GetNode() {
    LevelWavePathBlueprintNode *aResult = (LevelWavePathBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    return aResult;
}




int LevelWavePathBlueprint::GetClosestIndex(float pX, float pY, float &pDist) {
    int aResult = -1;
    if (mNodeList.mCount > 0) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.First();
        
        aResult = 0;
        float aCheckDist = pDist;
        float aDiffX = aNode->mX - pX;
        float aDiffY = aNode->mY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        pDist = aDist;
        for (int i=1;i<mNodeList.mCount;i++) {
            aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
            aDiffX = aNode->mX - pX;
            aDiffY = aNode->mY - pY;
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

void LevelWavePathBlueprint::SnapX(int pIndex) {
    
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL && pIndex >= 0 && pIndex < mNodeList.mCount) {
        aNode->mConstraint.mTypeX = X_CONSTRAINT_TARGET;
        aNode->mConstraint.mTargetX = pIndex;
    }
    ApplyEditorConstraints();
}

void LevelWavePathBlueprint::SnapY(int pIndex) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL && pIndex >= 0 && pIndex < mNodeList.mCount) {
        aNode->mConstraint.mTypeY = Y_CONSTRAINT_TARGET;
        aNode->mConstraint.mTargetY = pIndex;
    }
    ApplyEditorConstraints();
}

void LevelWavePathBlueprint::SetSnapXType(int pType) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL) {
        aNode->mConstraint.mTypeX = pType;
    }
    ApplyEditorConstraints();
}

void LevelWavePathBlueprint::SetSnapYType(int pType) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL) {
        aNode->mConstraint.mTypeY = pType;
    }
    ApplyEditorConstraints();
}

void LevelWavePathBlueprint::ApplyEditorConstraints() {
    
    for (int aLoops = 0;aLoops<40;aLoops++) {
        for (int i=0;i<mNodeList.mCount;i++) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
            
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mNodeList.mData[aNode->mConstraint.mTargetX];
                if (aTarget != 0) {
                    aNode->mX = aTarget->mX;
                }
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mNodeList.mData[aNode->mConstraint.mTargetY];
                if (aTarget != 0) {
                    aNode->mY = aTarget->mY;
                }
            }
            
            
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_SPAWN) { aNode->mX = gEditor->mSpawnZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_PEEK) { aNode->mX = gEditor->mPeekZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_QUARTER) { aNode->mX = gEditor->mQuarterZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_CENTER) { aNode->mX = gEditor->mCenterH; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_QUARTER) { aNode->mX = gEditor->mQuarterZoneRight; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_PEEK) { aNode->mX = gEditor->mPeekZoneRight; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_SPAWN) { aNode->mX = gEditor->mSpawnZoneRight; }

            
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_SPAWN) { aNode->mY = gEditor->mSpawnZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_PEEK) { aNode->mY = gEditor->mPeekZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_QUARTER) { aNode->mY = gEditor->mQuarterZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_CENTER) { aNode->mY = gEditor->mCenterV; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) { aNode->mY = gEditor->mQuarterZoneBottom; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM) { aNode->mY = gEditor->mPlayZoneBottom; }
            
        }
    }
    Build();
}


FPoint LevelWavePathBlueprint::GetGamePos(LevelWavePathBlueprintNode *pNode) {
    FPoint aResult;
    if (pNode != NULL) {
        aResult = GetGamePos(pNode->mX, pNode->mY);
    }
    return aResult;
}

FPoint LevelWavePathBlueprint::GetGamePos(float pX, float pY) {
    FPoint aPoint = FPoint(pX, pY);
    aPoint = FCanvas::Convert(aPoint.mX, aPoint.mY, gEditor, gGame);
    return aPoint;
}

void LevelWavePathBlueprint::Build() {
    
    if (gGame) {
        Build(&gGame->mEditorPath);
    }
    
}

void LevelWavePathBlueprint::Build(LevelWavePath *pPath) {
    
    if (pPath == NULL) { return; }
    
    pPath->Reset();
    pPath->mSmooth = mSmooth;
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        FPoint aPoint = GetGamePos(aNode);
        
        if (aNode->mConstraint.HasX()) {
            aPoint.mX = aNode->mConstraint.GameX(false);
        }
        
        if (aNode->mConstraint.HasY()) {
            aPoint.mY = aNode->mConstraint.GameY(false);
        }
        
        aNode->mBaseGameX = aPoint.mX;
        aNode->mBaseGameY = aPoint.mY;
    }
    
    for (int aLoops = 0;aLoops<40;aLoops++) {
        for (int i=0;i<mNodeList.mCount;i++) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mNodeList.mData[aNode->mConstraint.mTargetX];
                if (aTarget != 0) { aNode->mBaseGameX = aTarget->mBaseGameX; }
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mNodeList.mData[aNode->mConstraint.mTargetY];
                if (aTarget != 0) { aNode->mBaseGameY = aTarget->mBaseGameY; }
            }
        }
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
     
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
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        
        float aChamferSize = ((float) aNode->mChamferSize);
        if (aNode->mChamferSize > 0 &&
            i > 0 &&
            i < (mNodeList.mCount - 1)) {
            
            LevelWavePathBlueprintNode *aPrevNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i - 1];
            LevelWavePathBlueprintNode *aNextNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i + 1];
            
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
                           aNode->mGameY + aDiffBackY * aChamferSize);
            pPath->AddMove(aNode->mGameX + aDiffNextX * aChamferSize,
                           aNode->mGameY + aDiffNextY * aChamferSize);
        } else {
            pPath->AddMove(aNode->mGameX, aNode->mGameY, aNode->mWaitTimer);
        }
    }
}

FJSONNode *LevelWavePathBlueprint::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    
    aExport->AddDictionaryBool("blueprint", true);
    aExport->AddDictionaryBool("smooth", mSmooth);
    aExport->AddDictionaryFloat("speed", mSpeed);
    
    FJSONNode *aPathArray = new FJSONNode();
    aExport->AddDictionary("path", aPathArray);
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        aPathArray->AddArray(aNode->Save());
    }
    
    return aExport;
}




