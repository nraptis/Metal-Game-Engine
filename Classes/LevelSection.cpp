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
}

LevelSection::~LevelSection() {
    
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
