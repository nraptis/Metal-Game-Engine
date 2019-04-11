//
//  LevelSectionBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelSectionBlueprint.hpp"
#include "GameEditor.hpp"
#include "LevelSection.hpp"

LevelSectionBlueprint::LevelSectionBlueprint() {
    mCurrentWave = NULL;
    mCurrentPerm = NULL;
    
}

LevelSectionBlueprint::~LevelSectionBlueprint() {
    FreeList(LevelWaveBlueprint, mWaveList);
    FreeList(LevelWaveBlueprint, mKillWaveList);
}

void LevelSectionBlueprint::Reset() {
    for (int i=0;i<mWaveList.mCount;i++) {
        LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mWaveList[i];
        mKillWaveList.Add(aWave);
    }
    mWaveList.RemoveAll();
    mCurrentWave = NULL;
    
    for (int i=0;i<mPermList.mCount;i++) {
        LevelSectionPermanentBlueprint *aPerm = (LevelSectionPermanentBlueprint *)mPermList[i];
        mKillPermList.Add(aPerm);
    }
    mPermList.RemoveAll();
    mCurrentPerm = NULL;
}

void LevelSectionBlueprint::Update() {
    
    
    EnumList(LevelWaveBlueprint, aWave, mWaveList) {
        aWave->Update();
    }
    
    EnumList(LevelSectionPermanentBlueprint, aPerm, mPermList) {
        aPerm->Update();
    }
    
    
    
    
    EnumList(LevelWaveBlueprint, aWave, mKillWaveList) {
        if (mCurrentWave == aWave) { mCurrentWave = NULL; }
        aWave->mKillTimer--;
        if (aWave->mKillTimer <= 0) { mDeleteWaveList.Add(aWave); }
    }
    EnumList(LevelWaveBlueprint, aWave, mDeleteWaveList) {
        mKillWaveList.Remove(aWave);
        delete aWave;
    }
    mDeleteWaveList.RemoveAll();
    
    
    
    
    EnumList(LevelSectionPermanentBlueprint, aPerm, mKillPermList) {
        if (mCurrentPerm == aPerm) { mCurrentPerm = NULL; }
        aPerm->mKillTimer--;
        if (aPerm->mKillTimer <= 0) { mDeletePermList.Add(aPerm); }
    }
    EnumList(LevelSectionPermanentBlueprint, aPerm, mDeletePermList) {
        mKillPermList.Remove(aPerm);
        delete aPerm;
    }
    mDeletePermList.RemoveAll();
    
}

void LevelSectionBlueprint::Draw() {
    for (int i=0;i<mWaveList.mCount;i++) {
        LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mWaveList[i];
        aWave->Draw(aWave == mCurrentWave);
    }
    
    for (int i=0;i<mPermList.mCount;i++) {
        LevelSectionPermanentBlueprint *aPerm = (LevelSectionPermanentBlueprint *)mPermList[i];
        aPerm->Draw(aPerm == mCurrentPerm);
    }
}

void LevelSectionBlueprint::WaveAdd() {
    mCurrentWave = new LevelWaveBlueprint();
    mWaveList.Add(mCurrentWave);
    if (mCurrentWave != NULL) {
        mCurrentWave->Build();
    }
}

void LevelSectionBlueprint::WaveRemove() {
    if (mCurrentWave != NULL) {
        mWaveList.Remove(mCurrentWave);
        mKillWaveList.Add(mCurrentWave);
        mCurrentWave = NULL;
        WaveSelectPrev();
    }
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::WaveSelectNext() {
    if ((mWaveList.mCount) > 0 && (mCurrentWave != NULL)) {
        int aIndex = mWaveList.Find(mCurrentWave) + 1;
        if (aIndex >= mWaveList.mCount) aIndex = 0;
        mCurrentWave = (LevelWaveBlueprint *)mWaveList.Fetch(aIndex);
    } else {
        mCurrentWave = (LevelWaveBlueprint *)mWaveList.First();
    }
    if (mCurrentWave != NULL) {
        mCurrentWave->Build();
    }
}

void LevelSectionBlueprint::WaveSelectPrev() {
    if ((mWaveList.mCount) > 0 && (mCurrentWave != NULL)) {
        int aIndex = mWaveList.Find(mCurrentWave) - 1;
        if (aIndex < 0) aIndex = mWaveList.mCount - 1;
        mCurrentWave = (LevelWaveBlueprint *)mWaveList.Fetch(aIndex);
    } else {
        mCurrentWave = (LevelWaveBlueprint *)mWaveList.Last();
    }
    if (mCurrentWave != NULL) {
        mCurrentWave->Build();
    }
}

void LevelSectionBlueprint::WaveDeselect() {
    mCurrentWave = NULL;
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::WaveMoveUp() {
    mWaveList.MoveObjectDown(mCurrentWave);
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::WaveMoveDown() {
    mWaveList.MoveObjectUp(mCurrentWave);
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::WaveSelect(int pIndex) {
    mCurrentWave = (LevelWaveBlueprint *)mWaveList.Fetch(pIndex);
    if (mCurrentWave != NULL) {
        mCurrentWave->Build();
    }
}

int LevelSectionBlueprint::WaveCount(int pIndex) {
    LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mWaveList.Fetch(pIndex);
    if (aWave != NULL) {
        return aWave->mPath.mNodeList.mCount;
    }
    return 0;
}


void LevelSectionBlueprint::PermAdd(float pX, float pY) {
    mCurrentPerm = new LevelSectionPermanentBlueprint();
    
    mCurrentPerm->mEditorX = pX;
    mCurrentPerm->mEditorY = pY;
    
    if (gPermEditor != NULL) {
        if (gPermEditor->mSnapsEnabled == true) {
            mCurrentPerm->mConstraint.mTypeX = gEditor->ClosestXConstraint(pX);
            mCurrentPerm->mConstraint.mTypeY = gEditor->ClosestYConstraint(pY);
            mCurrentPerm->ApplyEditorConstraints();
        }
    }
    
    mPermList.Add(mCurrentPerm);
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::PermRemove() {
    if (mCurrentPerm != NULL) {
        mPermList.Remove(mCurrentPerm);
        mKillPermList.Add(mCurrentPerm);
        mCurrentPerm = NULL;
        PermSelectPrev();
    }
}

void LevelSectionBlueprint::PermSelectNext() {
    if ((mWaveList.mCount) > 0 && (mCurrentPerm != NULL)) {
        int aIndex = mPermList.Find(mCurrentPerm) + 1;
        if (aIndex >= mPermList.mCount) aIndex = 0;
        mCurrentPerm = (LevelSectionPermanentBlueprint *)mPermList.Fetch(aIndex);
    } else {
        mCurrentPerm = (LevelSectionPermanentBlueprint *)mPermList.First();
    }
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::PermSelectPrev() {
    if ((mPermList.mCount) > 0 && (mCurrentPerm != NULL)) {
        int aIndex = mPermList.Find(mCurrentPerm) - 1;
        if (aIndex < 0) aIndex = mWaveList.mCount - 1;
        mCurrentPerm = (LevelSectionPermanentBlueprint *)mPermList.Fetch(aIndex);
    } else {
        mCurrentPerm = (LevelSectionPermanentBlueprint *)mPermList.Last();
    }
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::PermDeselect() {
    mCurrentPerm = NULL;
}

void LevelSectionBlueprint::PermMoveUp() {
    mPermList.MoveObjectDown(mCurrentPerm);
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::PermMoveDown() {
    mPermList.MoveObjectUp(mCurrentPerm);
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

void LevelSectionBlueprint::PermSelect(int pIndex) {
    mCurrentPerm = (LevelSectionPermanentBlueprint *)mPermList.Fetch(pIndex);
    if (gEditor != NULL) { gEditor->RefreshPlayback(); }
}

int LevelSectionBlueprint::PermSelectClosest(float pX, float pY) {
    int aResult = -1;
    float aBestDist = 80.0f * 80.0f;
    
    for (int i=0;i<mPermList.mCount;i++) {
        LevelSectionPermanentBlueprint *aPerm = (LevelSectionPermanentBlueprint *)mPermList[i];
        
        float aPathDist = 80.0f * 80.0f;
        aPerm->mPath.GetClosestIndex(pX, pY, aPathDist);
        if (aPathDist < aBestDist) {
            aResult = i;
            aBestDist = aPathDist;
        }
        
        float aDist = DistanceSquared(aPerm->mEditorX, aPerm->mEditorY, pX, pY);
        
        if (aDist < aBestDist) {
            aResult = i;
            aBestDist = aDist;
        }
    }
    
    if (aResult >= 0 && aResult < mPermList.mCount) {
        mCurrentPerm = (LevelSectionPermanentBlueprint *)mPermList.Fetch(aResult);
    } else {
        mCurrentPerm = NULL;
    }
    
    return aResult;
}

void LevelSectionBlueprint::PermRefreshPositions() {
    float aLeft = gEditor->mGameAreaLeft;
    float aRight = gEditor->mGameAreaRight;
    float aTop = gEditor->mGameAreaTop;
    float aBottom = gEditor->mGameAreaBottom;
    
    for (int i=0;i<mPermList.mCount;i++) {
        LevelSectionPermanentBlueprint *aPerm = (LevelSectionPermanentBlueprint *)mPermList[i];
        aPerm->mPercentX = ((aPerm->mEditorX - aLeft) / (aRight - aLeft)) * 100.0f;
        aPerm->mPercentY = ((aPerm->mEditorY - aTop) / (aBottom - aTop)) * 100.0f;
    }
}

void LevelSectionBlueprint::Build() {
    if (gEditor) {
        Build(&gEditor->mEditorSection);
    }
}

void LevelSectionBlueprint::Build(LevelSection *pSection) {
    
    if (pSection == NULL) { return; }
    
    pSection->Reset();
    
    for (int i=0;i<mWaveList.mCount;i++) {
        LevelWaveBlueprint *aWaveBlueprint = (LevelWaveBlueprint *)mWaveList[i];
        LevelWave *aWave = new LevelWave();
        aWaveBlueprint->Build(aWave);
        pSection->AddWave(aWave);
    }
    
    //TODO:
    
    for (int i=0;i<mPermList.mCount;i++) {
        LevelSectionPermanentBlueprint *aPermBlueprint = (LevelSectionPermanentBlueprint *)mPermList.mData[i];
        LevelSectionPermanent *aPerm = new LevelSectionPermanent(pSection);
        aPermBlueprint->Build(aPerm);
        pSection->AddPerm(aPerm);
    }
    
    
}

FJSONNode *LevelSectionBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->AddDictionaryBool("section", true);
    
    FJSONNode *aWaveArray = new FJSONNode();
    aExport->AddDictionary("wave_list", aWaveArray);
    aWaveArray->mNodeType = JSON_NODE_TYPE_ARRAY;
    
    for (int i=0;i<mWaveList.mCount;i++) {
        LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mWaveList[i];
        aWaveArray->AddArray(aWave->Save());
    }
    
    if (mPermList.mCount > 0) {
        FJSONNode *aPermArray = new FJSONNode();
        aExport->AddDictionary("perm_list", aPermArray);
        aPermArray->mNodeType = JSON_NODE_TYPE_ARRAY;
        for (int i=0;i<mPermList.mCount;i++) {
            LevelSectionPermanentBlueprint *aPerm = (LevelSectionPermanentBlueprint *)mPermList.mData[i];
            aPermArray->AddArray(aPerm->Save());
        }
    }
    
    return aExport;
}

void LevelSectionBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    FJSONNode *aWaveArray = pNode->GetArray("wave_list");
    if (aWaveArray != NULL) {
        EnumJSONArray(aWaveArray, aWaveNode) {
            LevelWaveBlueprint *aWave = new LevelWaveBlueprint();
            aWave->Load(aWaveNode);
            mWaveList.Add(aWave);
        }
    }
    
    FJSONNode *aPermArray = pNode->GetArray("perm_list");
    if (aPermArray != NULL) {
        EnumJSONArray(aPermArray, aPermNode) {
            LevelSectionPermanentBlueprint *aPerm = new LevelSectionPermanentBlueprint();
            aPerm->Load(aPermNode);
            mPermList.Add(aPerm);
        }
    }
    
    //TODO: Remove
    if (gEditor != NULL) {
        WaveSelectNext();
        PermSelectNext();
    }
}


