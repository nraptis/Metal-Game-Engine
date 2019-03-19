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
}

void LevelSectionBlueprint::WaveSelectPrev() {
    if ((mWaveList.mCount) > 0 && (mCurrentWave != NULL)) {
        int aIndex = mWaveList.Find(mCurrentWave) - 1;
        if (aIndex < 0) aIndex = mWaveList.mCount - 1;
        mCurrentWave = (LevelWaveBlueprint *)mWaveList.Fetch(aIndex);
    } else {
        mCurrentWave = (LevelWaveBlueprint *)mWaveList.First();
    }
}

void LevelSectionBlueprint::WaveDeselect() {
    mCurrentWave = NULL;
}


