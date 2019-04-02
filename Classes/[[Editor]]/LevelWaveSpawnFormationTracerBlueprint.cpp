//
//  LevelWaveSpawnFormationTracerTracerBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawnFormationTracerBlueprint.hpp"
#include "LevelWaveSpawnFormationBlueprint.hpp"
#include "os_core_graphics.h"
#include "FSpline.h"
#include "FPolyPath.h"
#include "core_includes.h"
#include "GameEditor.hpp"
#include "FLine.h"


LevelWaveSpawnFormationTracerBlueprintNode::LevelWaveSpawnFormationTracerBlueprintNode() {
    mEditorX = 0.0f;
    mEditorY = 0.0f;
    
    mPercentX = 0.0f;
    mPercentY = 0.0f;
    
    mKillTimer = 8;
}

LevelWaveSpawnFormationTracerBlueprintNode::~LevelWaveSpawnFormationTracerBlueprintNode() {
    
}

FJSONNode *LevelWaveSpawnFormationTracerBlueprintNode::Save() {
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

void LevelWaveSpawnFormationTracerBlueprintNode::Load(FJSONNode *pNode) {
    
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

LevelWaveSpawnFormationTracerBlueprint::LevelWaveSpawnFormationTracerBlueprint() {
    mSelectedNodeIndex = -1;
    mCount = 5;
    mSpeedClass = 3;
}

LevelWaveSpawnFormationTracerBlueprint::~LevelWaveSpawnFormationTracerBlueprint() {
    FreeList(LevelWaveSpawnFormationTracerBlueprintNode, mNodeList);
    FreeList(LevelWaveSpawnFormationTracerBlueprintNode, mKillNodeList);
}

void LevelWaveSpawnFormationTracerBlueprint::Update() {
    
    RefreshNodePositions();
    
    EnumList(LevelWaveSpawnFormationTracerBlueprintNode, aNode, mKillNodeList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteNodeList.Add(aNode); }
    }
    EnumList(LevelWaveSpawnFormationTracerBlueprintNode, aNode, mDeleteNodeList) {
        mKillNodeList.Remove(aNode);
        delete aNode;
    }
    mDeleteNodeList.RemoveAll();
}

void LevelWaveSpawnFormationTracerBlueprint::Clear() {
    
    EnumList(LevelWaveSpawnFormationTracerBlueprintNode, aNode, mNodeList) {
        mKillNodeList.Add(aNode);
    }
    mNodeList.RemoveAll();
    
    mSelectedNodeIndex = -1;
    
    //if (gEditor != NULL) {
    //    RefreshNodePositions();
    //    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
    //}
}

void LevelWaveSpawnFormationTracerBlueprint::Draw(bool pSelected) {
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationTracerBlueprintNode *aNode1 = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.FetchCircular(i - 1);
        LevelWaveSpawnFormationTracerBlueprintNode *aNode2 = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.Fetch(i);
        
        if (pSelected) {
            Graphics::SetColor(1.0f, 1.0f, 0.75f, 0.65f);
            Graphics::DrawLine(aNode1->mEditorX, aNode1->mEditorY, aNode2->mEditorX, aNode2->mEditorY, 1.5f);
            
        } else {
            Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.25f);
            Graphics::DrawLine(aNode1->mEditorX, aNode1->mEditorY, aNode2->mEditorX, aNode2->mEditorY, 1.0f);
        }
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationTracerBlueprintNode *aNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.mData[i];
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
}

float LevelWaveSpawnFormationTracerBlueprint::GetX(int pIndex) {
    LevelWaveSpawnFormationTracerBlueprintNode *aNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorX; }
    return 0.0f;
}

float LevelWaveSpawnFormationTracerBlueprint::GetY(int pIndex) {
    LevelWaveSpawnFormationTracerBlueprintNode *aNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorY; }
    return 0.0f;
}

void LevelWaveSpawnFormationTracerBlueprint::Set(int pIndex, float pX, float pY) {
    LevelWaveSpawnFormationTracerBlueprintNode *aNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aNode != NULL) {
        aNode->mEditorX = pX;
        aNode->mEditorY = pY;
        RefreshNodePositions();
        if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
    }
}

void LevelWaveSpawnFormationTracerBlueprint::Add(float pX, float pY) {
    LevelWaveSpawnFormationTracerBlueprintNode *aNode = new LevelWaveSpawnFormationTracerBlueprintNode();
    aNode->mEditorX = pX;
    aNode->mEditorY = pY;
    mNodeList.Add(aNode);
    mSelectedNodeIndex = mNodeList.mCount - 1;
    RefreshNodePositions();
    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
}

void LevelWaveSpawnFormationTracerBlueprint::Remove(int pIndex) {
    LevelWaveSpawnFormationTracerBlueprintNode *aDeleteNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.Fetch(pIndex);
    if (aDeleteNode) {
        if (mSelectedNodeIndex >= pIndex) { mSelectedNodeIndex--; }
        mKillNodeList.Add(aDeleteNode);
        mNodeList.RemoveAtIndex(pIndex);
    }
    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
}

LevelWaveSpawnFormationTracerBlueprintNode *LevelWaveSpawnFormationTracerBlueprint::GetNode(int pIndex) {
    LevelWaveSpawnFormationTracerBlueprintNode *aResult = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.Fetch(pIndex);
    return aResult;
}

LevelWaveSpawnFormationTracerBlueprintNode *LevelWaveSpawnFormationTracerBlueprint::GetNode() {
    LevelWaveSpawnFormationTracerBlueprintNode *aResult = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.Fetch(mSelectedNodeIndex);
    return aResult;
}

void LevelWaveSpawnFormationTracerBlueprint::RefreshNodePositions() {
    
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationTracerBlueprintNode *aNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.mData[i];
        aNode->mPercentX = ((aNode->mEditorX - aLeft) / (aRight - aLeft)) * 100.0f - 50.0f;
        aNode->mPercentY = ((aNode->mEditorY - aTop) / (aBottom - aTop)) * 100.0f - 50.0f;
    }
}

int LevelWaveSpawnFormationTracerBlueprint::GetClosestIndex(float pX, float pY, float &pDist) {
    int aResult = -1;
    if (mNodeList.mCount > 0) {
        LevelWaveSpawnFormationTracerBlueprintNode *aNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.First();
        
        aResult = 0;
        float aCheckDist = pDist;
        float aDiffX = aNode->mEditorX - pX;
        float aDiffY = aNode->mEditorY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        pDist = aDist;
        for (int i=1;i<mNodeList.mCount;i++) {
            aNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.mData[i];
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

void LevelWaveSpawnFormationTracerBlueprint::Build(LevelWaveSpawnFormationTracer *pTracer) {
    if (pTracer == NULL) { return; }
    
    pTracer->Reset();
    
    pTracer->SetSpeedClass(mSpeedClass);
    pTracer->mCount = mCount;
    
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationTracerBlueprintNode *aNodeBlueprint = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.mData[i];
        
        LevelWaveSpawnFormationTracerNode *aNode = new LevelWaveSpawnFormationTracerNode(pTracer);
        
        aNode->mBaseX = aNodeBlueprint->mPercentX;
        aNode->mBaseY = aNodeBlueprint->mPercentY;
        
        pTracer->mTracerNodeList.Add(aNode);
    }
    
}

FJSONNode *LevelWaveSpawnFormationTracerBlueprint::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    
    aExport->AddDictionaryInt("object_count", mCount);
    aExport->AddDictionaryInt("speed_class", mSpeedClass);
    
    
    
    FJSONNode *aNodeListNode = new FJSONNode();
    aNodeListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationTracerBlueprintNode *aNode = (LevelWaveSpawnFormationTracerBlueprintNode *)mNodeList.mData[i];
        aNodeListNode->AddArray(aNode->Save());
    }
    aExport->AddDictionary("tracer_node_list", aNodeListNode);
    return aExport;
}

void LevelWaveSpawnFormationTracerBlueprint::Load(FJSONNode *pNode) {
    Clear();
    if (pNode == NULL) { return; }
    
    
    mCount = pNode->GetInt("object_count", mCount);
    mSpeedClass = pNode->GetInt("speed_class", mSpeedClass);
    
    
    FJSONNode *aNodeListNode = pNode->GetArray("tracer_node_list");
    if (aNodeListNode != NULL) {
        EnumJSONArray(aNodeListNode, aFormationBlueprintLoadNode) {
            LevelWaveSpawnFormationTracerBlueprintNode *aPathNode = new LevelWaveSpawnFormationTracerBlueprintNode();
            aPathNode->Load(aFormationBlueprintLoadNode);
            mNodeList.Add(aPathNode);
        }
    }
    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
}

bool LevelWaveSpawnFormationTracerBlueprint::IsValid() {
    
    if (mNodeList.mCount > 0) { return true; }
    
    
    return false;
}

