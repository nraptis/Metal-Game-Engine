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
    mInitialDelay = 60;
    mCurrentSection = NULL;
    mPreviousSection = NULL;
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
    
    //So what can sections do?
    //They can be simply timed... The section goes away after X ticks.
    //They can be force-timed. They MUST remain for X ticks...
    //If they run out of kill-ables, and they have no forced time, they go away.
    //If they just run out of time, then they go away... (you lose lives for balloons in this case)
    
    //mPreviousSection
    
    
    if (mCurrentSection == NULL) {
        if (mCurrentSectionIndex < mSectionList.mCount) {
            mCurrentSection = (LevelSection *)(mSectionList[mCurrentSectionIndex++]);
            mCurrentSection->Spawn();
            mCurrentSection->FlyInReset(SECTION_FLY_TOP);
            
            if (gGame->mTestOverlay != NULL) {
                gGame->mTestOverlay->AddBubble(mCurrentSection->mName.c());
            }
        }
    }
    
    if (mPreviousSection != NULL) {
        mPreviousSection->Update();
        if (mPreviousSection->mFlyOutType == SECTION_FLY_NONE) {
            printf("KILL SECTION: %s\n", mPreviousSection->mName.c());
            
            DisposeSection(mPreviousSection);
        }
        
    }
    
    if (mCurrentSection != NULL) {
        mCurrentSection->Update();
        if (mCurrentSection->mIsComplete) {
            
            if (mCurrentSection->HasAnyObjects()) {
                
                if (mPreviousSection != NULL) {
                    printf("*** WARNING *** Section Overlap ***\n\n");
                    DisposeSection(mPreviousSection);
                }
                
                mPreviousSection = mCurrentSection;
                mPreviousSection->FlyOut(SECTION_FLY_LEFT);
                mCurrentSection = NULL;
            } else {
                DisposeSection(mCurrentSection);
            }
        }
    }
}


void LevelData::DisposeObject(GameObject *pObject) {
    
}

void LevelData::DisposeSection(LevelSection *pLevelSection) {
    
    printf("DISPOSE SECTION: %s\n", pLevelSection->mName.c());
    
    if (pLevelSection == mCurrentSection) { mCurrentSection = NULL; }
    if (pLevelSection == mPreviousSection) { mPreviousSection = NULL; }
    
    if (gGame->mTestOverlay != NULL) {
        gGame->mTestOverlay->RemoveBubble(pLevelSection->mName.c());
        gGame->mTestOverlay->SetBubbleStatusHasObjects(pLevelSection->mName.c(), false);
        gGame->mTestOverlay->SetBubbleStatusAllComplete(pLevelSection->mName.c(), false);
        gGame->mTestOverlay->SetBubbleStatusPermsComplete(pLevelSection->mName.c(), false);
        gGame->mTestOverlay->SetBubbleStatusWavesComplete(pLevelSection->mName.c(), false);
        
    }
    
    if (pLevelSection != NULL) {
        delete pLevelSection;
    }
}

void LevelData::Print(const char *pName) {
    
}

void LevelData::AddSection(LevelSection *pLevelSection) {
    mSectionList.Add(pLevelSection);
}
