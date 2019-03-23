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
        
        float aLeft = gEditor->mGameAreaLeft;
        float aRight = gEditor->mGameAreaRight;
        
        //100x percision
        float aX = (mX - aLeft) / (aRight - aLeft) * 100.0f;
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
        float aY = (mY - aTop) / (aBottom - aTop) * 100.0f;
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
    
    if (mChamferSize > 0) {
        aExport->AddDictionaryInt("chamfer", mChamferSize);
    }
    
    if (mWaitTimer > 0) {
        aExport->AddDictionaryInt("wait", mWaitTimer);
    }
    
    return aExport;
}

void LevelWavePathBlueprintNode::Load(FJSONNode *pNode) {
    
    if (pNode == NULL) { return; }
    
    mConstraint.mTypeX = pNode->GetInt("x_con", mConstraint.mTypeX);
    mConstraint.mTargetX = pNode->GetInt("x_con_target", mConstraint.mTargetX);
    mConstraint.mOffsetX = pNode->GetFloat("x_con_offset", mConstraint.mOffsetX);
    
    mConstraint.mTypeY = pNode->GetInt("y_con", mConstraint.mTypeY);
    mConstraint.mTargetY = pNode->GetInt("y_con_target", mConstraint.mTargetY);
    mConstraint.mOffsetY = pNode->GetFloat("y_con_offset", mConstraint.mOffsetY);
    
    float aX = 0.0f;
    aX = pNode->GetFloat("x", aX);
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    mX = aLeft + (aRight - aLeft) * (aX / 100.0f);
    
    float aY = 0.0f;
    aY = pNode->GetFloat("y", aY);
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    mY = aTop + (aBottom - aTop) * (aY / 100.0f);
    

    mChamferSize = pNode->GetInt("chamfer", mChamferSize);
    mWaitTimer = pNode->GetInt("wait", mWaitTimer);
    
}

LevelWavePathBlueprint::LevelWavePathBlueprint() {
    
    mWave = NULL;
    
}



LevelWavePathBlueprint::~LevelWavePathBlueprint() {
    
}

void LevelWavePathBlueprint::Clear() {
    FreeList(LevelWavePathBlueprintNode, mNodeList);
    mSelectedIndex = -1;
    mWave->ApplyEditorConstraints();
}

void LevelWavePathBlueprint::Draw(bool pSelected) {
    for (int i=1;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode1 = (LevelWavePathBlueprintNode *)mNodeList.mData[i - 1];
        LevelWavePathBlueprintNode *aNode2 = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        if (pSelected) {
            Graphics::SetColor(0.75f, 0.75f, 0.75f, 0.25f);
            Graphics::DrawLine(aNode1->mX, aNode1->mY, aNode2->mX, aNode2->mY, 1.0f);
            
        } else {
            Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.25f);
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
            Graphics::DrawPoint(aNode->mX, aNode->mY, 4.0f);
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
        mWave->ApplyEditorConstraints();
    }
}

void LevelWavePathBlueprint::Add(float pX, float pY) {
    LevelWavePathBlueprintNode *aNode = new LevelWavePathBlueprintNode();
    aNode->mX = pX;
    aNode->mY = pY;
    mNodeList.Add(aNode);
    mWave->ApplyEditorConstraints();
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
    mWave->ApplyEditorConstraints();
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
    mWave->ApplyEditorConstraints();
}

void LevelWavePathBlueprint::SnapY(int pIndex) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL && pIndex >= 0 && pIndex < mNodeList.mCount) {
        aNode->mConstraint.mTypeY = Y_CONSTRAINT_TARGET;
        aNode->mConstraint.mTargetY = pIndex;
    }
    mWave->ApplyEditorConstraints();
}

void LevelWavePathBlueprint::SetSnapXType(int pType) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL) {
        aNode->mConstraint.mTypeX = pType;
    }
    mWave->ApplyEditorConstraints();
}

void LevelWavePathBlueprint::SetSnapYType(int pType) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    if (aNode != NULL) {
        aNode->mConstraint.mTypeY = pType;
    }
    mWave->ApplyEditorConstraints();
}



FPoint LevelWavePathBlueprint::GetNormalizedPos(LevelWavePathBlueprintNode *pNode) {
    FPoint aResult;
    if (pNode != NULL) {
        aResult = GetNormalizedPos(pNode->mX, pNode->mY);
    }
    return aResult;
}

FPoint LevelWavePathBlueprint::GetNormalizedPos(float pX, float pY) {
    FPoint aPoint = FPoint(pX, pY);
    if (gEditor) {
        float aLeft = gEditor->mGameAreaLeft;
        float aRight = gEditor->mGameAreaRight;
        float aTop = gEditor->mGameAreaTop;
        float aBottom = gEditor->mGameAreaBottom;
        aPoint.mX = (pX - aLeft) / (aRight - aLeft);
        aPoint.mY = (pY - aTop) / (aBottom - aTop);
    }
    
    //aPoint = FCanvas::Convert(aPoint.mX, aPoint.mY, gEditor, gGame);
    
    return aPoint;
}

FJSONNode *LevelWavePathBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_ARRAY;
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        aExport->AddArray(aNode->Save());
    }
    return aExport;
}

void LevelWavePathBlueprint::Load(FJSONNode *pNode) {
    Clear();
    if (pNode == NULL) { return; }
    EnumJSONArray(pNode, aPathLoadNode) {
        LevelWavePathBlueprintNode *aPathNode = new LevelWavePathBlueprintNode();
        aPathNode->Load(aPathLoadNode);
        mNodeList.Add(aPathNode);
    }
    mWave->ApplyEditorConstraints();
}
