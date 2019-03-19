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
    mType = -1;
    mWaitTimer = 0;
    mChamfer = false;
}

LevelWavePathBlueprintNode::~LevelWavePathBlueprintNode() {
    
}

LevelWavePathBlueprint::LevelWavePathBlueprint() {
    
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
        
        if (mSelectedIndex > pIndex) {
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
    
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        FPoint aPoint = GetGamePos(aNode);
        
        //aPoint.mX = gRand.Get(1000.0f);
        //aPoint.mY = gRand.Get(1000.0f);
        
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_SPAWN) { aPoint.mX = gGame->mSpawnZoneLeft; }
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_PEEK) { aPoint.mX = gGame->mPeekZoneLeft; }
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_QUARTER) { aPoint.mX = gGame->mQuarterZoneLeft; }
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_CENTER) { aPoint.mX = gGame->mWidth2; }
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_QUARTER) { aPoint.mX = gGame->mQuarterZoneRight; }
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_PEEK) { aPoint.mX = gGame->mPeekZoneRight; }
        if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_SPAWN) { aPoint.mX = gGame->mSpawnZoneRight; }
        if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_SPAWN) { aPoint.mY = gGame->mSpawnZoneTop; }
        if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_PEEK) { aPoint.mY = gGame->mPeekZoneTop; }
        if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_QUARTER) { aPoint.mY = gGame->mQuarterZoneTop; }
        if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_CENTER) { aPoint.mY = (gGame->mPlayAreaBottom + gGame->mPlayAreaTop) / 2.0f; }
        if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) { aPoint.mY = gEditor->mQuarterZoneBottom; }
        if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM) { aPoint.mY = gGame->mPlayAreaBottom; }
        
        aNode->mGameX = aPoint.mX;
        aNode->mGameY = aPoint.mY;
    }
    
    for (int aLoops = 0;aLoops<40;aLoops++) {
        for (int i=0;i<mNodeList.mCount;i++) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mNodeList.mData[aNode->mConstraint.mTargetX];
                if (aTarget != 0) { aNode->mGameX = aTarget->mGameX; }
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mNodeList.mData[aNode->mConstraint.mTargetY];
                if (aTarget != 0) { aNode->mGameY = aTarget->mGameY; }
            }
        }
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        FPoint aPoint = GetGamePos(aNode);
        pPath->AddMove(aNode->mGameX, aNode->mGameY);
    }
    
    
    //PATH_CHAMFER_SIZE
    
    
}



