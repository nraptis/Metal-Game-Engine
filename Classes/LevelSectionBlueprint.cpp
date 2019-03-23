//
//  LevelSectionBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelSectionBlueprint.hpp"
#include "GameEditor.hpp"

LevelSectionBlueprint::LevelSectionBlueprint() {
    mCurrentWave = NULL;
}

LevelSectionBlueprint::~LevelSectionBlueprint() {
    
}

void LevelSectionBlueprint::Clear() {
    FreeList(LevelWaveBlueprint, mWaveList);
    mCurrentWave = NULL;
}

void LevelSectionBlueprint::Draw() {
    for (int i=0;i<mWaveList.mCount;i++) {
        LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mWaveList[i];
        aWave->Draw(aWave == mCurrentWave);
    }
}

void LevelSectionBlueprint::WaveAdd() {
    mCurrentWave = new LevelWaveBlueprint();
    mWaveList.Add(mCurrentWave);
}

void LevelSectionBlueprint::WaveRemove() {
    if (mCurrentWave) {
        mWaveList.Remove(mCurrentWave);
        delete mCurrentWave;
        mCurrentWave = NULL;
        WaveSelectPrev();
    }
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
}

void LevelSectionBlueprint::WaveMoveUp() {
    mWaveList.MoveObjectDown(mCurrentWave);
}

void LevelSectionBlueprint::WaveMoveDown() {
    mWaveList.MoveObjectUp(mCurrentWave);
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
    return aExport;
}

void LevelSectionBlueprint::Load(FJSONNode *pNode) {
    Clear();
    if (pNode == NULL) { return; }
    
    FJSONNode *aWaveArray = pNode->GetArray("wave_list");
    if (aWaveArray != NULL) {
        EnumJSONArray(aWaveArray, aWaveNode) {
            LevelWaveBlueprint *aWave = new LevelWaveBlueprint();
            aWave->Load(aWaveNode);
            mWaveList.Add(aWave);
        }
    }
    WaveSelectNext();
}


