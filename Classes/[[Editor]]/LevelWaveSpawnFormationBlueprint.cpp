//
//  LevelWaveSpawnFormationBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawnFormationBlueprint.hpp"
#include "os_core_graphics.h"
#include "FSpline.h"
#include "FPolyPath.h"
#include "core_includes.h"
#include "GameEditor.hpp"
#include "FLine.h"


LevelWaveSpawnFormationBlueprintNode::LevelWaveSpawnFormationBlueprintNode() {
    mEditorX = 0.0f;
    mEditorY = 0.0f;
    
    mPercentX = 0.0f;
    mPercentY = 0.0f;
    
    mGameX = 0.0f;
    mGameY = 0.0f;
    
    mType = -1;
    
    mKillTimer = 8;
}

LevelWaveSpawnFormationBlueprintNode::~LevelWaveSpawnFormationBlueprintNode() {
    
}

FJSONNode *LevelWaveSpawnFormationBlueprintNode::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    
    //100x percision
    float aX = (mEditorX - aLeft) / (aRight - aLeft) * 100.0f - 50.0f;
    aExport->AddDictionaryFloat("x", aX);
    
    
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    //100x percision
    float aY = (mEditorY - aTop) / (aBottom - aTop) * 100.0f - 50.0f;
    aExport->AddDictionaryFloat("y", aY);
    
    return aExport;
}

void LevelWaveSpawnFormationBlueprintNode::Load(FJSONNode *pNode) {
    
    if (pNode == NULL) { return; }
    
    mPercentX = 0.0f;
    mPercentX = pNode->GetFloat("x", mPercentX);
    
    if (gEditor != NULL) {
        float aLeft = gEditor->mGameAreaLeft;
        float aRight = gEditor->mGameAreaRight;
        mEditorX = aLeft + (aRight - aLeft) * ((mPercentX + 50.0f) / 100.0f);
    }
    
    mPercentY = 0.0f;
    mPercentY = pNode->GetFloat("y", mPercentY);
    if (gEditor != NULL) {
        float aTop = gEditor->mGameAreaTop;
        float aBottom = gEditor->mGameAreaBottom;
        mEditorY = aTop + (aBottom - aTop) * ((mPercentY + 50.0f) / 100.0f);
    }
    
}

LevelWaveSpawnFormationBlueprint::LevelWaveSpawnFormationBlueprint() {
    
    mRotation = 0.0f;
    
    mRotationEnabled = false;
    
    mRotationSpeedClass = WAVE_SPEED_MEDIUM;
    
    mRotationSpeedNegateAlways = false;
    mRotationSpeedNegateRandom = true;
    
    
    mSelectedNodeIndex = -1;
    mCurrentTracerIndex = 0;
    
}

LevelWaveSpawnFormationBlueprint::~LevelWaveSpawnFormationBlueprint() {
    FreeList(LevelWaveSpawnFormationBlueprintNode, mNodeList);
    FreeList(LevelWaveSpawnFormationBlueprintNode, mKillNodeList);
}

void LevelWaveSpawnFormationBlueprint::Update() {
    
    RefreshNodePositions();
    
    EnumList(LevelWaveSpawnFormationBlueprintNode, aNode, mKillNodeList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteNodeList.Add(aNode); }
    }
    EnumList(LevelWaveSpawnFormationBlueprintNode, aNode, mDeleteNodeList) {
        mKillNodeList.Remove(aNode);
        delete aNode;
    }
    mDeleteNodeList.RemoveAll();
    
    //
}

void LevelWaveSpawnFormationBlueprint::Clear() {
    
    for (int i=0;i<4;i++) {
        mTracer[i].Clear();
    }
    
    EnumList(LevelWaveSpawnFormationBlueprintNode, aNode, mNodeList) {
        mKillNodeList.Add(aNode);
    }
    mNodeList.RemoveAll();
    
    mSelectedNodeIndex = -1;
    
    if (gFormationEditor != NULL) {
        RefreshNodePositions();
    //    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
        
    }
    
}

void LevelWaveSpawnFormationBlueprint::Draw(bool pSelected) {
    
    
    
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
        if (pSelected) {
            if (i == mSelectedNodeIndex) {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aNode->mEditorX, aNode->mEditorY, 12.0f);
            } else {
                Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
                Graphics::DrawPoint(aNode->mEditorX, aNode->mEditorY, 6.0f);
            }
        } else {
            Graphics::SetColor(0.65f, 0.65f, 0.65f, 0.35f);
            Graphics::DrawPoint(aNode->mEditorX, aNode->mEditorY, 4.0f);
        }
    }
    
    for (int i=0;i<4;i++) {
        mTracer[i].Draw(mCurrentTracerIndex == i);
    }
}

float LevelWaveSpawnFormationBlueprint::GetX(int pIndex) {
    LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorX; }
    return 0.0f;
}

float LevelWaveSpawnFormationBlueprint::GetY(int pIndex) {
    LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorY; }
    return 0.0f;
}

void LevelWaveSpawnFormationBlueprint::Set(int pIndex, float pX, float pY) {
    LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) {
        aNode->mEditorX = pX;
        aNode->mEditorY = pY;
        RefreshNodePositions();
        if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
    }
}

void LevelWaveSpawnFormationBlueprint::Add(float pX, float pY) {
    LevelWaveSpawnFormationBlueprintNode *aNode = new LevelWaveSpawnFormationBlueprintNode();
    aNode->mEditorX = pX;
    aNode->mEditorY = pY;
    mNodeList.Add(aNode);
    mSelectedNodeIndex = mNodeList.mCount - 1;
    RefreshNodePositions();
    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
}

void LevelWaveSpawnFormationBlueprint::Remove(int pIndex) {
    LevelWaveSpawnFormationBlueprintNode *aDeleteNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aDeleteNode) {
        if (mSelectedNodeIndex >= pIndex) { mSelectedNodeIndex--; }
        mKillNodeList.Add(aDeleteNode);
        mNodeList.RemoveAtIndex(pIndex);
    }
    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
}

LevelWaveSpawnFormationBlueprintNode *LevelWaveSpawnFormationBlueprint::GetNode(int pIndex) {
    LevelWaveSpawnFormationBlueprintNode *aResult = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(pIndex);
    return aResult;
}

LevelWaveSpawnFormationBlueprintNode *LevelWaveSpawnFormationBlueprint::GetNode() {
    LevelWaveSpawnFormationBlueprintNode *aResult = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.Fetch(mSelectedNodeIndex);
    return aResult;
}




void LevelWaveSpawnFormationBlueprint::TracerAdd(float pX, float pY) {
    LevelWaveSpawnFormationTracerBlueprint *aTracer = GetTracer();
    if (aTracer != NULL) {
        aTracer->Add(pX, pY);
    }
}

void LevelWaveSpawnFormationBlueprint::TracerRemove() {
    LevelWaveSpawnFormationTracerBlueprint *aTracer = GetTracer();
    if (aTracer != NULL) {
        aTracer->Remove(aTracer->mSelectedNodeIndex);
    }
}

void LevelWaveSpawnFormationBlueprint::TracerSet(int pIndex, float pX, float pY) {
    LevelWaveSpawnFormationTracerBlueprint *aTracer = GetTracer();
    if (aTracer != NULL) {
        aTracer->Set(pIndex, pX, pY);
    }
}

float LevelWaveSpawnFormationBlueprint::TracerGetX(int pIndex) {
    LevelWaveSpawnFormationTracerBlueprint *aTracer = GetTracer();
    if (aTracer != NULL) {
        return aTracer->GetX(pIndex);
    }
    return 0.0f;
}

float LevelWaveSpawnFormationBlueprint::TracerGetY(int pIndex) {
    LevelWaveSpawnFormationTracerBlueprint *aTracer = GetTracer();
    if (aTracer != NULL) {
        return aTracer->GetY(pIndex);
    }
    return 0.0f;
}

LevelWaveSpawnFormationTracerBlueprint *LevelWaveSpawnFormationBlueprint::GetTracer() {
    if (mCurrentTracerIndex >= 0 && mCurrentTracerIndex < 4) {
        return &(mTracer[mCurrentTracerIndex]);
    }
    return NULL;
}

LevelWaveSpawnFormationTracerBlueprintNode *LevelWaveSpawnFormationBlueprint::TracerGetNode(int pIndex) {
    LevelWaveSpawnFormationTracerBlueprint *aTracer = GetTracer();
    if (aTracer != NULL) {
        return aTracer->GetNode(pIndex);
    }
    return NULL;
}

LevelWaveSpawnFormationTracerBlueprintNode *LevelWaveSpawnFormationBlueprint::TracerGetNode() {
    LevelWaveSpawnFormationTracerBlueprint *aTracer = GetTracer();
    if (aTracer != NULL) {
        return aTracer->GetNode();
    }
    return NULL;
}

void LevelWaveSpawnFormationBlueprint::Print() {
    FJSON aJSON;
    aJSON.mRoot = Save();
    aJSON.Print();
}
      
void LevelWaveSpawnFormationBlueprint::RefreshNodePositions() {
    
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
        aNode->mPercentX = ((aNode->mEditorX - aLeft) / (aRight - aLeft)) * 100.0f - 50.0f;
        aNode->mPercentY = ((aNode->mEditorY - aTop) / (aBottom - aTop)) * 100.0f - 50.0f;
    }
}

int LevelWaveSpawnFormationBlueprint::GetClosestIndex(float pX, float pY, float &pDist) {
    int aResult = -1;
    if (mNodeList.mCount > 0) {
        LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.First();
        
        aResult = 0;
        float aCheckDist = pDist;
        float aDiffX = aNode->mEditorX - pX;
        float aDiffY = aNode->mEditorY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        pDist = aDist;
        for (int i=1;i<mNodeList.mCount;i++) {
            aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
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

void LevelWaveSpawnFormationBlueprint::Build() {
    if (gFormationEditor != NULL) {
        Build(&(gFormationEditor->mEditorFormation));
    }
}

void LevelWaveSpawnFormationBlueprint::Build(LevelWaveSpawnFormation *pFormation) {
    if (pFormation == NULL) { return; }
    
    pFormation->Reset();
    pFormation->mRotation = mRotation;
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationBlueprintNode *aNodeBlueprint = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
        LevelWaveSpawnFormationNode *aNode = new LevelWaveSpawnFormationNode(pFormation);
        aNode->mBaseX = aNodeBlueprint->mPercentX;
        aNode->mBaseY = aNodeBlueprint->mPercentY;
        pFormation->mNodeList.Add(aNode);
    }
    
    for (int i=0;i<4;i++) {
        if (mTracer[i].IsValid()) {
            LevelWaveSpawnFormationTracer *aTracer = new LevelWaveSpawnFormationTracer();
            mTracer[i].Build(aTracer);
            pFormation->mTracerList.Add(aTracer);
        }
    }
    
    
    
}

FJSONNode *LevelWaveSpawnFormationBlueprint::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    if (mRotation != 0) {
        aExport->AddDictionaryFloat("rotation", mRotation);
    }
    
    FJSONNode *aNodeListNode = new FJSONNode();
    aNodeListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationBlueprintNode *aNode = (LevelWaveSpawnFormationBlueprintNode *)mNodeList.mData[i];
        aNodeListNode->AddArray(aNode->Save());
    }
    aExport->AddDictionary("node_list", aNodeListNode);
    
    
    bool aSaveTracers = false;
    for (int i=0;i<4;i++) {
        if (mTracer[i].IsValid()) {
            aSaveTracers = true;
        }
    }
    if (aSaveTracers) {
        FJSONNode *aTracerListNode = new FJSONNode();
        aTracerListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
        for (int i=0;i<4;i++) {
            
            if (mTracer[i].IsValid()) {
                aTracerListNode->AddArray(mTracer[i].Save());
            }
            
        }
        aExport->AddDictionary("tracer_list", aTracerListNode);
    }
    
    
    
    return aExport;
}

void LevelWaveSpawnFormationBlueprint::Load(FJSONNode *pNode) {
    Clear();
    if (pNode == NULL) { return; }
    
    mRotation = pNode->GetFloat("rotation", mRotation);
    
    
    FJSONNode *aNodeListNode = pNode->GetArray("node_list");
    if (aNodeListNode != NULL) {
        EnumJSONArray(aNodeListNode, aFormationBlueprintLoadNode) {
            LevelWaveSpawnFormationBlueprintNode *aNode = new LevelWaveSpawnFormationBlueprintNode();
            aNode->Load(aFormationBlueprintLoadNode);
            mNodeList.Add(aNode);
        }
    }
    
    
    FJSONNode *aTracerListNode = pNode->GetArray("tracer_list");
    if (aTracerListNode != NULL) {
        int aIndex = 0;
        EnumJSONArray(aTracerListNode, aTracerBlueprintLoadNode) {
            mTracer[aIndex].Load(aTracerBlueprintLoadNode);
            ++aIndex;
            if (aIndex == 4) { break; }
        }
    }
}

bool LevelWaveSpawnFormationBlueprint::IsValid() {
    if (mNodeList.mCount > 0) {
        return true;
    }
    for (int i=0;i<4;i++) {
        if (mTracer[i].IsValid() == true) {
            return true;
        }
    }
    return false;
}

