//
//  LevelData.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelData.hpp"
#include "Game.hpp"
#include "GameLevelController.hpp"

LevelData::LevelData() {
    mCurrentSectionIndex = 0;
    mInitialDelay = 100;
    mCurrentSection = NULL;
}

LevelData::~LevelData() {
    
}

void LevelData::Update() {
    if (mInitialDelay > 0) {
        --mInitialDelay;
        if (mInitialDelay <= 0) {
            Log("About to spawn First SECTION...\n");
        }
        return;
    }
    
    if (mCurrentSection == NULL) {
        if (mCurrentSectionIndex < mSectionList.mCount) {
            mCurrentSection = (LevelSection *)(mSectionList[mCurrentSectionIndex++]);
            mCurrentSection->Spawn();
            
        }
    }
    
    if (mCurrentSection != NULL) {
        mCurrentSection->Update();
        if (mCurrentSection->mIsComplete) {
            DisposeSection(mCurrentSection);
        }
    }
    
    
}


void LevelData::DisposeObject(GameObject *pObject) {
    
}

void LevelData::DisposeSection(LevelSection *pLevelSection) {
    
}

void LevelData::Print(const char *pName) {
    
}

void LevelData::AddSection(LevelSection *pLevelSection) {
    mSectionList.Add(pLevelSection);
}
