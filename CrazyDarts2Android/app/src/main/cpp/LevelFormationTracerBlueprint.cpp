//
//  LevelFormationTracerTracerBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelFormationTracerBlueprint.hpp"
#include "LevelFormationBlueprint.hpp"
#include "os_core_graphics.h"
#include "FSpline.hpp"
#include "FPolyPath.hpp"
#include "core_includes.h"
#include "GameEditor.hpp"
#include "FLine.hpp"


LevelFormationTracerNodeBlueprint::LevelFormationTracerNodeBlueprint() {
    mEditorX = 0.0f;
    mEditorY = 0.0f;
    
    mPercentX = 0.0f;
    mPercentY = 0.0f;
    
    mKillTimer = 8;
}

LevelFormationTracerNodeBlueprint::~LevelFormationTracerNodeBlueprint() {
    
}

FJSONNode *LevelFormationTracerNodeBlueprint::Save() {
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

void LevelFormationTracerNodeBlueprint::Load(FJSONNode *pNode) {
    
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

LevelFormationTracerBlueprint::LevelFormationTracerBlueprint() {
    mSelectedTracerNodeIndex = -1;
    mSelectedSpawnNodeIndex = 0;
    
    mCount = 5;
    mSpeedClass = SPEED_CLASS_MEDIUM_SLOW;
    
    
    mSpecialType = TRACER_SPECIAL_TYPE_NONE;
    
    mSpecialPercentX = 0.0f;
    mSpecialPercentY = 0.0f;
    
    mSpecialSpecialEditorX = 255.0f;
    mSpecialSpecialEditorY = 255.0f;
    
    mSpecialRadius = 255;
    mSpecialCornerRadius = 64;
    
    
}

LevelFormationTracerBlueprint::~LevelFormationTracerBlueprint() {
    FreeList(LevelFormationTracerNodeBlueprint, mTracerNodeList);
    FreeList(LevelFormationTracerNodeBlueprint, mKillTracerNodeList);
    
    
    FreeList(LevelFormationNodeBlueprint, mSpawnNodeList);
    FreeList(LevelFormationNodeBlueprint, mKillSpawnNodeList);
    
    
    
    
}

void LevelFormationTracerBlueprint::Update() {
    
    
    if (mSpecialType != TRACER_SPECIAL_TYPE_NONE) {
        EnumList(LevelFormationTracerNodeBlueprint, aNode, mTracerNodeList) {
            mKillTracerNodeList.Add(aNode);
        }
        mTracerNodeList.RemoveAll();
        mSelectedTracerNodeIndex = -1;
    }
    
    
    RefreshSpawnNodeList();
    RefreshNodePositions();
    
    EnumList(LevelFormationTracerNodeBlueprint, aNode, mKillTracerNodeList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteTracerNodeList.Add(aNode); }
    }
    EnumList(LevelFormationTracerNodeBlueprint, aNode, mDeleteTracerNodeList) {
        mKillTracerNodeList.Remove(aNode);
        delete aNode;
    }
    mDeleteTracerNodeList.RemoveAll();
    
    
    
    
    
    EnumList(LevelFormationNodeBlueprint, aNode, mKillSpawnNodeList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteSpawnNodeList.Add(aNode); }
    }
    EnumList(LevelFormationNodeBlueprint, aNode, mDeleteSpawnNodeList) {
        mKillSpawnNodeList.Remove(aNode);
        delete aNode;
    }
    mDeleteSpawnNodeList.RemoveAll();
}

void LevelFormationTracerBlueprint::Reset() {
    
    mSpecialType = TRACER_SPECIAL_TYPE_NONE;
    
    EnumList(LevelFormationTracerNodeBlueprint, aNode, mTracerNodeList) {
        mKillTracerNodeList.Add(aNode);
    }
    mTracerNodeList.RemoveAll();
    
    mSelectedTracerNodeIndex = -1;
    
    //if (gEditor != NULL) {
    //    RefreshNodePositions();
    //    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
    //}
}

void LevelFormationTracerBlueprint::Nuke() {
    Reset();
    
    mCount = 5;
    mSpeedClass = SPEED_CLASS_MEDIUM_SLOW;
    mSpecialType = TRACER_SPECIAL_TYPE_NONE;
    
    for (int i=0;i<mSpawnNodeList.mCount;i++) {
        LevelFormationNodeBlueprint *aNodeB = (LevelFormationNodeBlueprint *)mSpawnNodeList.mData[i];
        mKillSpawnNodeList.Add(aNodeB);
    }
    mSpawnNodeList.RemoveAll();
}


void LevelFormationTracerBlueprint::Draw(bool pSelected) {
    
    for (int i=0;i<mTracerNodeList.mCount;i++) {
        LevelFormationTracerNodeBlueprint *aNode1 = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.FetchCircular(i - 1);
        LevelFormationTracerNodeBlueprint *aNode2 = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.Fetch(i);
        
        if (pSelected) {
            Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
            Graphics::DrawLine(aNode1->mEditorX, aNode1->mEditorY, aNode2->mEditorX, aNode2->mEditorY, 2.0f);
            
        } else {
            Graphics::SetColor(0.65f, 0.65f, 0.85f, 0.25f);
            Graphics::DrawLine(aNode1->mEditorX, aNode1->mEditorY, aNode2->mEditorX, aNode2->mEditorY, 1.0f);
        }
    }
    
    for (int i=0;i<mTracerNodeList.mCount;i++) {
        LevelFormationTracerNodeBlueprint *aNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.mData[i];
        if (pSelected) {
            if (i == mSelectedTracerNodeIndex) {
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
    
    
    if (mSpecialType != TRACER_SPECIAL_TYPE_NONE) {
        Graphics::SetColor(0.0f, 0.4f, 0.93f, 0.87f);
        Graphics::OutlineRect(mSpecialSpecialEditorX - 3.0f, mSpecialSpecialEditorY - 3.0f, 5.0f, 5.0f, 2.0f);
    }
    
}

float LevelFormationTracerBlueprint::GetX(int pIndex) {
    LevelFormationTracerNodeBlueprint *aNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorX; }
    return 0.0f;
}

float LevelFormationTracerBlueprint::GetY(int pIndex) {
    LevelFormationTracerNodeBlueprint *aNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.Fetch(pIndex);
    if (aNode != NULL) { return aNode->mEditorY; }
    return 0.0f;
}

void LevelFormationTracerBlueprint::Set(int pIndex, float pX, float pY) {
    LevelFormationTracerNodeBlueprint *aNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.Fetch(pIndex);
    if (aNode != NULL) {
        aNode->mEditorX = pX;
        aNode->mEditorY = pY;
        RefreshNodePositions();
        if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
    }
}

void LevelFormationTracerBlueprint::Add(float pX, float pY) {
    LevelFormationTracerNodeBlueprint *aNode = new LevelFormationTracerNodeBlueprint();
    aNode->mEditorX = pX;
    aNode->mEditorY = pY;
    mTracerNodeList.Add(aNode);
    mSelectedTracerNodeIndex = mTracerNodeList.mCount - 1;
    RefreshNodePositions();
    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
}

void LevelFormationTracerBlueprint::Remove(int pIndex) {
    LevelFormationTracerNodeBlueprint *aDeleteNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.Fetch(pIndex);
    if (aDeleteNode) {
        if (mSelectedTracerNodeIndex >= pIndex) { mSelectedTracerNodeIndex--; }
        mKillTracerNodeList.Add(aDeleteNode);
        mTracerNodeList.RemoveAtIndex(pIndex);
    }
    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
}

LevelFormationTracerNodeBlueprint *LevelFormationTracerBlueprint::GetNode(int pIndex) {
    LevelFormationTracerNodeBlueprint *aResult = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.Fetch(pIndex);
    return aResult;
}

LevelFormationTracerNodeBlueprint *LevelFormationTracerBlueprint::GetNode() {
    LevelFormationTracerNodeBlueprint *aResult = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.Fetch(mSelectedTracerNodeIndex);
    return aResult;
}

void LevelFormationTracerBlueprint::RefreshSpawnNodeList() {
    
    while (mSpawnNodeList.mCount > mCount && mSpawnNodeList.mCount > 0) {
        LevelFormationNodeBlueprint *aLast = (LevelFormationNodeBlueprint *)mSpawnNodeList.PopLast();
        mKillSpawnNodeList.Add(aLast);
    }
    
    while (mSpawnNodeList.mCount < mCount && mSpawnNodeList.mCount < 128) {
        LevelFormationNodeBlueprint *aNode = new LevelFormationNodeBlueprint();
        mSpawnNodeList.Add(aNode);
    }
}

void LevelFormationTracerBlueprint::RefreshNodePositions() {
    
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    
    for (int i=0;i<mTracerNodeList.mCount;i++) {
        LevelFormationTracerNodeBlueprint *aNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.mData[i];
        aNode->mPercentX = ((aNode->mEditorX - aLeft) / (aRight - aLeft)) * 100.0f - 50.0f;
        aNode->mPercentY = ((aNode->mEditorY - aTop) / (aBottom - aTop)) * 100.0f - 50.0f;
    }
    
    mSpecialPercentX = (mSpecialSpecialEditorX - aLeft) / (aRight - aLeft) * 100.0f - 50.0f;
    mSpecialPercentY = (mSpecialSpecialEditorY - aTop) / (aBottom - aTop) * 100.0f - 50.0f;
}

int LevelFormationTracerBlueprint::GetClosestIndex(float pX, float pY, float &pDist) {
    int aResult = -1;
    if (mTracerNodeList.mCount > 0) {
        LevelFormationTracerNodeBlueprint *aNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.First();
        
        aResult = 0;
        float aCheckDist = pDist;
        float aDiffX = aNode->mEditorX - pX;
        float aDiffY = aNode->mEditorY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        pDist = aDist;
        for (int i=1;i<mTracerNodeList.mCount;i++) {
            aNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.mData[i];
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

void LevelFormationTracerBlueprint::Build(LevelFormationTracer *pTracer) {
    if (pTracer == NULL) { return; }
    
    pTracer->Reset();
    
    pTracer->SetSpeedClass(mSpeedClass);
    //pTracer->mCount = mCount;
    
    
    pTracer->mSpecialType = mSpecialType;
    
    pTracer->mSpecialX = mSpecialPercentX;
    pTracer->mSpecialY = mSpecialPercentY;
    
    pTracer->mSpecialRadius = (float)mSpecialRadius;
    pTracer->mSpecialCornerRadius = (float)mSpecialCornerRadius;
    
    for (int i=0;i<mTracerNodeList.mCount;i++) {
        LevelFormationTracerNodeBlueprint *aNodeBlueprint = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.mData[i];
        
        LevelFormationTracerNode *aNode = new LevelFormationTracerNode(pTracer);
        
        aNode->mBaseX = aNodeBlueprint->mPercentX;
        aNode->mBaseY = aNodeBlueprint->mPercentY;
        
        pTracer->mTracerNodeList.Add(aNode);
    }
    
    
    for (int i=0;i<mSpawnNodeList.mCount;i++) {
        LevelFormationNodeBlueprint *aNodeBlueprint = (LevelFormationNodeBlueprint *)mSpawnNodeList.mData[i];
        LevelFormationNode *aNode = new LevelFormationNode();
        aNode->mFormation = pTracer->mFormation;
        aNode->mObjectType = aNodeBlueprint->mObjectType;
        pTracer->mSpawnNodeList.Add(aNode);
    }
}

FJSONNode *LevelFormationTracerBlueprint::Save() {
    
    RefreshSpawnNodeList();
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    
    aExport->AddDictionaryInt("object_count", mCount);
    aExport->AddDictionaryInt("speed_class", mSpeedClass);
    
    aExport->AddDictionaryInt("special_type", mSpecialType);
    
    if (mSpecialType != TRACER_SPECIAL_TYPE_NONE) {
        float aLeft = gEditor->mGameAreaLeft;
        float aRight = gEditor->mGameAreaRight;
        float aX = (mSpecialSpecialEditorX - aLeft) / (aRight - aLeft) * 100.0f - 50.0f;
        aExport->AddDictionaryFloat("special_x", aX);
        
        float aTop = gEditor->mGameAreaTop;
        float aBottom = gEditor->mGameAreaBottom;
        float aY = (mSpecialSpecialEditorY - aTop) / (aBottom - aTop) * 100.0f - 50.0f;
        aExport->AddDictionaryFloat("special_y", aY);
    }
    
    if (mSpecialType == TRACER_SPECIAL_TYPE_CIRCLE) {
        
        aExport->AddDictionaryInt("special_type_radius", mSpecialRadius);
        
    }
    if (mSpecialType == TRACER_SPECIAL_TYPE_ROUNDED_RECT) {
        aExport->AddDictionaryInt("special_type_size", mSpecialRadius);
        aExport->AddDictionaryInt("special_type_corner_radius", mSpecialCornerRadius);
    }
    
    
    if (mTracerNodeList.mCount > 0) {
        FJSONNode *aTracerNodeListNode = new FJSONNode();
        aTracerNodeListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
        for (int i=0;i<mTracerNodeList.mCount;i++) {
            LevelFormationTracerNodeBlueprint *aNode = (LevelFormationTracerNodeBlueprint *)mTracerNodeList.mData[i];
            aTracerNodeListNode->AddArray(aNode->Save());
        }
        aExport->AddDictionary("tracer_node_list", aTracerNodeListNode);
    }
    
    
    //To save space, we will only save the spawn node list
    //if any node has type which is not balloon...
    
    bool aShouldSaveSpawnNodeList = false;
    
#define GO_TYPE_CNT 32
    int aTypeCount[GO_TYPE_CNT];
    memset(aTypeCount, 0, sizeof(aTypeCount));
    
    for (int i=0;i<mSpawnNodeList.mCount;i++) {
        LevelFormationNodeBlueprint *aNodeBlueprint = (LevelFormationNodeBlueprint *)mSpawnNodeList.mData[i];
        if (aNodeBlueprint->mObjectType >= 0 && aNodeBlueprint->mObjectType < GO_TYPE_CNT) {
            aTypeCount[aNodeBlueprint->mObjectType] += 1;
        } else { printf("ILLEGAL TYPE!!!\n***\n\n***\n"); }
    }
    
    int aMonoType = GAME_OBJECT_TYPE_BALLOON;
    int aDifferentTypes = 0;
    for (int i=0;i<GO_TYPE_CNT;i++) {
        if (aTypeCount[i] == mSpawnNodeList.mCount) { aMonoType = i; }
        if (aTypeCount[i] > 0) { aDifferentTypes += 1; }
    }
    
    if (aMonoType != GAME_OBJECT_TYPE_BALLOON) {
        aExport->AddDictionaryInt("spawn_monotype", aMonoType);
    } else if (aDifferentTypes > 1) {
        aShouldSaveSpawnNodeList = true;
    }
    
    if (aShouldSaveSpawnNodeList && mSpawnNodeList.mCount > 0) {
        FJSONNode *aSpawnNodeListNode = new FJSONNode();
        aSpawnNodeListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
        for (int i=0;i<mSpawnNodeList.mCount;i++) {
            LevelFormationNodeBlueprint *aNodeBlueprint = (LevelFormationNodeBlueprint *)mSpawnNodeList.mData[i];
            aSpawnNodeListNode->AddArray(aNodeBlueprint->Save(true));
        }
        aExport->AddDictionary("spawn_node_list", aSpawnNodeListNode);
    }
    
    return aExport;
}

void LevelFormationTracerBlueprint::Load(FJSONNode *pNode) {
    Reset();
    
    if (pNode == NULL) { return; }
    
    mCount = pNode->GetInt("object_count", mCount);
    RefreshSpawnNodeList();
    
    mSpeedClass = pNode->GetInt("speed_class", mSpeedClass);
    
    mSpecialType = pNode->GetInt("special_type", mSpecialType);
    
    if (mSpecialType != TRACER_SPECIAL_TYPE_NONE) {
        
        mSpecialPercentX = 0.0f;
        mSpecialPercentX = pNode->GetFloat("special_x", mSpecialPercentX);
        
        if (gEditor != NULL) {
            float aLeft = gEditor->mGameAreaLeft;
            float aRight = gEditor->mGameAreaRight;
            mSpecialSpecialEditorX = aLeft + (aRight - aLeft) * ((mSpecialPercentX + 50.0f) / 100.0f);
        }
        
        mSpecialPercentY = 0.0f;
        mSpecialPercentY = pNode->GetFloat("special_y", mSpecialPercentY);
        if (gEditor != NULL) {
            float aTop = gEditor->mGameAreaTop;
            float aBottom = gEditor->mGameAreaBottom;
            mSpecialSpecialEditorY = aTop + (aBottom - aTop) * ((mSpecialPercentY + 50.0f) / 100.0f);
        }
    }
    
    if (mSpecialType == TRACER_SPECIAL_TYPE_CIRCLE) {
        mSpecialRadius = pNode->GetInt("special_type_radius", mSpecialRadius);
    }
    
    if (mSpecialType == TRACER_SPECIAL_TYPE_ROUNDED_RECT) {
        mSpecialRadius = pNode->GetInt("special_type_size", mSpecialRadius);
        mSpecialCornerRadius = pNode->GetInt("special_type_corner_radius", mSpecialCornerRadius);
    }
    
    FJSONNode *aTracerNodeListNode = pNode->GetArray("tracer_node_list");
    if (aTracerNodeListNode != NULL) {
        EnumJSONArray(aTracerNodeListNode, aLoadNode) {
            LevelFormationTracerNodeBlueprint *aPathNode = new LevelFormationTracerNodeBlueprint();
            aPathNode->Load(aLoadNode);
            mTracerNodeList.Add(aPathNode);
        }
    }
    
    
    FJSONNode *aSpawnNodeListNode = pNode->GetArray("spawn_node_list");
    if (aSpawnNodeListNode != NULL) {
        
        int aIndex = 0;
        EnumJSONArray(aSpawnNodeListNode, aLoadNode) {
            LevelFormationNodeBlueprint *aSpawnNode = (LevelFormationNodeBlueprint *)mSpawnNodeList.Fetch(aIndex);
            if (aSpawnNode != NULL) {
                aSpawnNode->Load(aLoadNode);
            }
            ++aIndex;
        }
    }
    
    int aMonoType = GAME_OBJECT_TYPE_BALLOON;
    aMonoType = pNode->GetInt("spawn_monotype", aMonoType);
    if (aMonoType != GAME_OBJECT_TYPE_BALLOON) {
        EnumList(LevelFormationNodeBlueprint, aNode, mSpawnNodeList) {
            aNode->mObjectType = aMonoType;
        }
    }
    
    
    
    if (gFormationEditor != NULL) { gFormationEditor->Refresh(); }
}

bool LevelFormationTracerBlueprint::IsValid() {
    if (mTracerNodeList.mCount > 0) { return true; }
    if (mSpecialType != TRACER_SPECIAL_TYPE_NONE) { return true; }
    return false;
}

