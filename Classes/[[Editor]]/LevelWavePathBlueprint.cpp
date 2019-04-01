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
#include "FLine.h"


LevelWavePathBlueprintNode::LevelWavePathBlueprintNode() {
    mEditorX = 0.0f;
    mEditorY = 0.0f;
    
    mPercentX = 0.0f;
    mPercentY = 0.0f;
    
    mBaseGameX = 0.0f;
    mBaseGameY = 0.0f;
    
    mGameX = 0.0f;
    mGameY = 0.0f;
    
    mType = -1;
    mWaitTimer = 0;
    mChamferSize = 0;
    
    mKillTimer = 8;
}

LevelWavePathBlueprintNode::~LevelWavePathBlueprintNode() {
    
}

void LevelWavePathBlueprintNode::ShiftX(float pShiftX) {
    if (mConstraint.mTypeX == X_CONSTRAINT_NONE) {
        mEditorX = mEditorX + pShiftX;
    } else {
        mConstraint.mOffsetX += pShiftX;
    }
}

void LevelWavePathBlueprintNode::ShiftY(float pShiftY) {
    if (mConstraint.mTypeY == Y_CONSTRAINT_NONE) {
        mEditorY = mEditorY + pShiftY;
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
    

    mChamferSize = pNode->GetInt("chamfer", mChamferSize);
    mWaitTimer = pNode->GetInt("wait", mWaitTimer);
    
}

LevelWavePathBlueprint::LevelWavePathBlueprint() {
    mWave = NULL;
    mSpeedClass = WAVE_SPEED_MEDIUM;
    mSmooth = true;
}

LevelWavePathBlueprint::~LevelWavePathBlueprint() {
    FreeList(LevelWavePathBlueprintNode, mNodeList);
    FreeList(LevelWavePathBlueprintNode, mKillList);
}

void LevelWavePathBlueprint::Update() {
    
    RefreshNodePositions();
    
    EnumList(LevelWavePathBlueprintNode, aNode, mKillList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteList.Add(aNode); }
    }
    EnumList(LevelWavePathBlueprintNode, aNode, mDeleteList) {
        mKillList.Remove(aNode);
        delete aNode;
    }
    mDeleteList.RemoveAll();
}

void LevelWavePathBlueprint::Clear() {
    
    EnumList(LevelWavePathBlueprintNode, aNode, mNodeList) {
        mKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
    
    mSelectedIndex = -1;
    
    if (gEditor != NULL) {
        RefreshNodePositions();
        mWave->ApplyEditorConstraints();
    }
}

void LevelWavePathBlueprint::Draw(bool pSelected) {
    for (int i=1;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode1 = (LevelWavePathBlueprintNode *)mNodeList.mData[i - 1];
        LevelWavePathBlueprintNode *aNode2 = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        if (pSelected) {
            Graphics::SetColor(0.75f, 0.75f, 0.75f, 0.25f);
            Graphics::DrawLine(aNode1->mEditorX, aNode1->mEditorY, aNode2->mEditorX, aNode2->mEditorY, 1.0f);
            
        } else {
            Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.25f);
            Graphics::DrawLine(aNode1->mEditorX, aNode1->mEditorY, aNode2->mEditorX, aNode2->mEditorY, 1.0f);
        }
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        if (pSelected) {
            if (i == mSelectedIndex) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aNode->mEditorX, aNode->mEditorY, 12.0f);
            } else {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aNode->mEditorX, aNode->mEditorY, 6.0f);
            }
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
            Graphics::SetColor(0.65f, 0.65f, 0.65f, 0.35f);
            Graphics::DrawPoint(aNode->mEditorX, aNode->mEditorY, 4.0f);
        }
    }
}

float LevelWavePathBlueprint::GetX(int pIndex) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorX; }
    return 0.0f;
}

float LevelWavePathBlueprint::GetY(int pIndex) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorY; }
    return 0.0f;
}

void LevelWavePathBlueprint::Set(int pIndex, float pX, float pY) {
    LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) {
        aNode->mEditorX = pX;
        aNode->mEditorY = pY;
        RefreshNodePositions();
        mWave->ApplyEditorConstraints();
    }
}

void LevelWavePathBlueprint::Add(float pX, float pY) {
    LevelWavePathBlueprintNode *aNode = new LevelWavePathBlueprintNode();
    aNode->mEditorX = pX;
    aNode->mEditorY = pY;
    mNodeList.Add(aNode);
    RefreshNodePositions();
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
        if (mSelectedIndex >= pIndex) { mSelectedIndex--; }
        mKillList.Add(aDeleteNode);
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

void LevelWavePathBlueprint::RefreshNodePositions() {
    
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
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

int LevelWavePathBlueprint::GetClosestIndex(float pX, float pY, float &pDist) {
    int aResult = -1;
    if (mNodeList.mCount > 0) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mNodeList.First();
        
        aResult = 0;
        float aCheckDist = pDist;
        float aDiffX = aNode->mEditorX - pX;
        float aDiffY = aNode->mEditorY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        pDist = aDist;
        for (int i=1;i<mNodeList.mCount;i++) {
            aNode = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
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

void LevelWavePathBlueprint::GetClosestPointOnLine(float pX, float pY, float &pDist) {
    for (int i=1;i<mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode1 = (LevelWavePathBlueprintNode *)mNodeList.mData[i-1];
        LevelWavePathBlueprintNode *aNode2 = (LevelWavePathBlueprintNode *)mNodeList.mData[i];
        
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
    if (gEditor != NULL) {
        mWave->ApplyEditorConstraints();
    }
}
