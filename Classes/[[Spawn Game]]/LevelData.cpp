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
    mFlyInFromRight = false;
}

LevelData::~LevelData() {
    
}

void LevelData::Update() {
    
    if (mInitialDelay > 0) {
        --mInitialDelay;
        return;
    }
    
    //So what can sections do?
    //They can be simply timed... The section goes away after X ticks.
    //They can be force-timed. They MUST remain for X ticks...
    //If they run out of kill-ables, and they have no forced time, they go away.
    //If they just run out of time, then they go away... (you lose lives for balloons in this case)
    
    bool aIsFirstSection = false;
    
    if (mCurrentSection == NULL) {
        if (mCurrentSectionIndex < mSectionList.mCount) {
            
            if (gGame->IsAnyObjectFloatingAway() == false) {
                
                
                
                if (mCurrentSectionIndex == 0) {
                    aIsFirstSection = true;
                }
                
                mCurrentSection = (LevelSection *)(mSectionList[mCurrentSectionIndex++]);
                mCurrentSection->Spawn();
                
                if (mPreviousSection != NULL) {
                    //We always fly in - if it's all waves, we still need the delay...
                    if (mFlyInFromRight) {
                        mCurrentSection->FlyInReset(SECTION_FLY_RIGHT);
                    } else {
                        mCurrentSection->FlyInReset(SECTION_FLY_LEFT);
                    }
                } else {
                    
                    //We have no previous section...
                    //Do we have any perms?
                    if (mCurrentSection->HasAnyPermanents()) {
                        if (aIsFirstSection) {
                            mCurrentSection->FlyInReset(SECTION_FLY_TOP);
                        } else {
                            
                            mFlyInFromRight = gRand.GetBool();
                            if (mFlyInFromRight) {
                                mCurrentSection->FlyInReset(SECTION_FLY_RIGHT);
                            } else {
                                mCurrentSection->FlyInReset(SECTION_FLY_LEFT);
                            }
                        }
                    }
                }
                
                if (gGame->mTestOverlay != NULL) {
                    gGame->mTestOverlay->AddBubble(mCurrentSection->mName.c());
                }
                
                
            }
        }
    }
    
    if (mPreviousSection != NULL) {
        mPreviousSection->Update();
        if (mPreviousSection->mFlyOutType == SECTION_FLY_NONE) {
            DisposeSection(mPreviousSection);
        }
    }
    
    if (mCurrentSection != NULL) {
        mCurrentSection->Update();
        
        bool aKeepAlive = false;
        bool aForceKill = false;
        
        if (mCurrentSection->mFlyInType == SECTION_FLY_NONE &&
            mCurrentSection->mFlyOutType == SECTION_FLY_NONE) {
            
            if (mCurrentSection->mForceKillTimer > 0) {
                mCurrentSection->mForceKillTimer--;
                if (mCurrentSection->mForceKillTimer <= 0) {
                    aForceKill = true;
                }
            }
            
            if (mCurrentSection->mKeepAliveTimer > 0) {
                mCurrentSection->mKeepAliveTimer--;
                if (mCurrentSection->mKeepAliveTimer > 0) {
                    aKeepAlive = true;
                }
            }
        } else {
            if (mCurrentSection->mKeepAliveTimer > 0) {
                aKeepAlive = true;
            }
        }
        
        if (mCurrentSection->mFlyInType != SECTION_FLY_NONE ||
            mCurrentSection->mFlyOutType != SECTION_FLY_NONE) {
            aKeepAlive = true;
        }
        
        if (((mCurrentSection->mIsComplete == true) || (aForceKill == true))
            && (aKeepAlive == false)) {
            
            if (mCurrentSection->HasAnyObjects()) {
                
                if (mPreviousSection != NULL) { DisposeSection(mPreviousSection); }
                
                mPreviousSection = mCurrentSection;
                mCurrentSection = NULL;
                
                mFlyInFromRight = gRand.GetBool();
                if (mFlyInFromRight) {
                    mPreviousSection->FlyOut(SECTION_FLY_LEFT);
                } else {
                    mPreviousSection->FlyOut(SECTION_FLY_RIGHT);
                }
                
            } else {
                DisposeSection(mCurrentSection);
            }
        }
    }
}

void LevelData::DisposeObject(GameObject *pObject) {
    
    if (mPreviousSection) {
        mPreviousSection->DisposeObject(pObject);
    }
    
    if (mCurrentSection) {
        mCurrentSection->DisposeObject(pObject);
    }
}

void LevelData::DisposeSection(LevelSection *pLevelSection) {
    
    if (pLevelSection == mCurrentSection) { mCurrentSection = NULL; }
    if (pLevelSection == mPreviousSection) { mPreviousSection = NULL; }
    
    if (pLevelSection != NULL) {
        FList aList;
        pLevelSection->HandOffAllPermanentGameObjects(&aList);
        for (int i=0;i<aList.mCount;i++) {
            GameObject *aObject = ((GameObject *)aList.mData[i]);
            if (gGame != NULL) {
                gGame->FlyOffEscape(aObject);
            }
        }
    }
    
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
