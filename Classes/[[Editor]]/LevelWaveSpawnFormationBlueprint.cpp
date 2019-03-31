//
//  LevelWaveSpawnFormationBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawnFormationBlueprint.hpp"
#include "LevelWaveSpawnFormation.hpp"
#include "GameEditor.hpp"

LevelWaveSpawnFormationBlueprintNode::LevelWaveSpawnFormationBlueprintNode() {
    mX = 0.0f;
    mY = 0.0f;
    
    mFormationX = 0.0f;
    mFormationY = 0.0f;
    
    mType = -1;
    
    mKillTimer = 27;
}

LevelWaveSpawnFormationBlueprintNode::~LevelWaveSpawnFormationBlueprintNode() {
    
}

FJSONNode *LevelWaveSpawnFormationBlueprintNode::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    
    //100x percision
    float aX = (mX - aLeft) / (aRight - aLeft) * 100.0f - 50.0f;
    aExport->AddDictionaryFloat("x", aX);
    
    
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    //100x percision
    float aY = (mY - aTop) / (aBottom - aTop) * 100.0f - 50.0f;
    aExport->AddDictionaryFloat("y", aY);
    
    
    
    
    return aExport;
}

void LevelWaveSpawnFormationBlueprintNode::Load(FJSONNode *pNode) {
    
    if (pNode == NULL) { return; }
    
    
    float aX = 0.0f;
    aX = pNode->GetFloat("x", aX);
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    mX = aLeft + (aRight - aLeft) * ((aX + 50.0f) / 100.0f);
    
    float aY = 0.0f;
    aY = pNode->GetFloat("y", aY);
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    mY = aTop + (aBottom - aTop) * ((aY + 50.0f) / 100.0f);
    
    
    
}


LevelWaveSpawnFormationBlueprint::LevelWaveSpawnFormationBlueprint() {
    
}

LevelWaveSpawnFormationBlueprint::~LevelWaveSpawnFormationBlueprint() {
    FreeList(LevelWaveSpawnFormationBlueprintNode, mNodeList);
    FreeList(LevelWaveSpawnFormationBlueprintNode, mKillList);
}

void LevelWaveSpawnFormationBlueprint::Update() {
    EnumList(LevelWaveSpawnFormationBlueprintNode, aNode, mKillList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteList.Add(aNode); }
    }
    EnumList(LevelWaveSpawnFormationBlueprintNode, aNode, mDeleteList) {
        mKillList.Remove(aNode);
        delete aNode;
    }
    mDeleteList.RemoveAll();
}

void LevelWaveSpawnFormationBlueprint::Clear() {
    EnumList(LevelWaveSpawnFormationBlueprintNode, aNode, mNodeList) {
        mKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
    mSelectedIndex = -1;
    if (gFormationEditor) {
        gFormationEditor->Refresh();
    }
}

void LevelWaveSpawnFormationBlueprint::Draw(bool pSelected) {
    for (int i=1;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationBlueprintNode *aNode1 = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i - 1];
        LevelWaveSpawnFormationBlueprintNode *aNode2 = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
        if (pSelected) {
            Graphics::SetColor(0.75f, 0.75f, 0.75f, 0.25f);
            Graphics::DrawLine(aNode1->mX, aNode1->mY, aNode2->mX, aNode2->mY, 1.0f);
            
        } else {
            Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.25f);
            Graphics::DrawLine(aNode1->mX, aNode1->mY, aNode2->mX, aNode2->mY, 1.0f);
        }
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
        if (pSelected) {
            if (i == mSelectedIndex) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aNode->mX, aNode->mY, 12.0f);
            } else {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aNode->mX, aNode->mY, 6.0f);
            }
        } else {
            Graphics::SetColor(0.65f, 0.65f, 0.65f, 0.35f);
            Graphics::DrawPoint(aNode->mX, aNode->mY, 4.0f);
        }
    }
}

float LevelWaveSpawnFormationBlueprint::GetX(int pIndex) {
    LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mX; }
    return 0.0f;
}

float LevelWaveSpawnFormationBlueprint::GetY(int pIndex) {
    LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mY; }
    return 0.0f;
}

void LevelWaveSpawnFormationBlueprint::Set(int pIndex, float pX, float pY) {
    LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) {
        aNode->mX = pX;
        aNode->mY = pY;
        if (gFormationEditor) { gFormationEditor->Refresh(); }
    }
}

void LevelWaveSpawnFormationBlueprint::Add(float pX, float pY) {
    LevelWaveSpawnFormationBlueprintNode *aNode = new LevelWaveSpawnFormationBlueprintNode();
    aNode->mX = pX;
    aNode->mY = pY;
    mNodeList.Add(aNode);
    if (gFormationEditor) { gFormationEditor->Refresh(); }
}

void LevelWaveSpawnFormationBlueprint::Remove(int pIndex) {
    
    LevelWaveSpawnFormationBlueprintNode *aDeleteNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aDeleteNode) {
        if (mSelectedIndex >= pIndex) { mSelectedIndex--; }
        mKillList.Add(aDeleteNode);
        mNodeList.RemoveAtIndex(pIndex);
    }
    
    if (gFormationEditor) { gFormationEditor->Refresh(); }
}

LevelWaveSpawnFormationBlueprintNode *LevelWaveSpawnFormationBlueprint::GetNode(int pIndex) {
    LevelWaveSpawnFormationBlueprintNode *aResult = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    return aResult;
}

LevelWaveSpawnFormationBlueprintNode *LevelWaveSpawnFormationBlueprint::GetNode() {
    LevelWaveSpawnFormationBlueprintNode *aResult = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(mSelectedIndex);
    return aResult;
}

int LevelWaveSpawnFormationBlueprint::GetClosestIndex(float pX, float pY, float &pDist) {
    int aResult = -1;
    if (mNodeList.mCount > 0) {
        LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.First();
        
        aResult = 0;
        float aCheckDist = pDist;
        float aDiffX = aNode->mX - pX;
        float aDiffY = aNode->mY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        pDist = aDist;
        for (int i=1;i<mNodeList.mCount;i++) {
            aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
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

FJSONNode *LevelWaveSpawnFormationBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_ARRAY;
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
        aExport->AddArray(aNode->Save());
    }
    return aExport;
}

void LevelWaveSpawnFormationBlueprint::Load(FJSONNode *pNode) {
    Clear();
    if (pNode == NULL) { return; }
    EnumJSONArray(pNode, aPathLoadNode) {
        LevelWaveSpawnFormationBlueprintNode *aPathNode = new LevelWaveSpawnFormationBlueprintNode();
        aPathNode->Load(aPathLoadNode);
        mNodeList.Add(aPathNode);
    }
    if (gFormationEditor) { gFormationEditor->Refresh(); }
}
