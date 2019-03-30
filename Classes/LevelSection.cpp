//
//  LevelSection.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelSection.hpp"
#include "Game.hpp"
#include "GameLevelController.hpp"

LevelSection::LevelSection() {
    mCurrentWave = NULL;
    mCurrentWaveIndex = 0;
    
    mIsComplete = false;
    
    mDelay = 100;
    
    mKillTimer = 8;
}

LevelSection::~LevelSection() {
    FreeList(LevelWave, mWaveList);
    FreeList(LevelWave, mKillList);
}

void LevelSection::Reset() {
    EnumList(LevelWave, aWave, mWaveList) {
        mKillList.Add(aWave);
    }
    mWaveList.RemoveAll();
    mCurrentWaveIndex = 0;
}

void LevelSection::Restart() {
    
    mCurrentWave = NULL;
    mCurrentWaveIndex = 0;
    
}

void LevelSection::Spawn() {
    Log("LevelSection::Spawn()\n");
    
}

void LevelSection::Update() {
    
    if (mDelay > 0) {
        --mDelay;
        //Log("LevelSection::Delay(%d)\n", mDelay);
        
        if (mDelay <= 0) {
            Log("About to spawn First Wave...\n");
        }
        return;
    }
    
    if (mCurrentWave == NULL) {
        if (mCurrentWaveIndex < mWaveList.mCount) {
            mCurrentWave = (LevelWave *)(mWaveList[mCurrentWaveIndex++]);
            mCurrentWave->Spawn();
            
        }
    }
    
    if (mCurrentWave != NULL) {
        mCurrentWave->Update();
        if (mCurrentWave->mIsComplete) {
            DisposeWave(mCurrentWave);
        }
    }
    
    
    
    
    
    
    EnumList(LevelWave, aWave, mKillList) {
        if (mCurrentWave == aWave) { mCurrentWave = NULL; }
        aWave->mKillTimer--;
        if (aWave->mKillTimer <= 0) { mDeleteList.Add(aWave); }
    }
    EnumList(LevelWave, aWave, mDeleteList) {
        mKillList.Remove(aWave);
        delete aWave;
    }
    mDeleteList.RemoveAll();
    
}

void LevelSection::Draw() {
    
}

void LevelSection::Dispose() {
    
}

void LevelSection::DisposeObject(GameObject *pObject) {
    
}

void LevelSection::DisposeWave(LevelWave *pLevelWave) {
    Log("Dispose Wave: [%X]\n", pLevelWave);
    if (pLevelWave == mCurrentWave) {
        mCurrentWave = NULL;
    }
    
}

void LevelSection::AddWave(LevelWave *pLevelWave) {
 
    mWaveList.Add(pLevelWave);
    
}
