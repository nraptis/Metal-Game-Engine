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
#include "LevelSectionBlueprint.hpp"

LevelSection::LevelSection() {
    mCandidateWave = NULL;
    mCandidateWaveDelay = 0;
    mCandidateWaveIndex = 0;
    
    mLoadError = false;
    
    mIsComplete = false;
    
    mAllWavesComplete = false;
    mAllPermsComplete = false;
    
    
    mDidSpawn = false;
    
    mKeepAliveTimer = 0;
    mForceKillTimer = 0;
    
    mDelay = 0;
    
    mStartWaveIndex = 0;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mFlyInType = SECTION_FLY_NONE;
    mFlyInTimer = 0;
    mFlyInTime = 145;
    //mFlyInTime = 999;
    
    
    mFlyOutType = SECTION_FLY_NONE;
    mFlyOutTimer = 0;
    mFlyOutTime = 145;
    //mFlyOutTime = 999;
    
    mName = "???";
}

LevelSection::~LevelSection() {
    FreeList(LevelWave, mWaveList);
    FreeList(LevelWave, mKillWaveList);
    mActiveWaveList.RemoveAll();
}

void LevelSection::Reset() {
    mActiveWaveList.RemoveAll();
    EnumList(LevelWave, aWave, mWaveList) {
        aWave->Reset();
        mKillWaveList.Add(aWave);
    }
    mWaveList.RemoveAll();
    
    
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        aPerm->Reset();
        mKillPermList.Add(aPerm);
    }
    mPermList.RemoveAll();
    
    mCandidateWaveIndex = mStartWaveIndex;
    mCandidateWave = NULL;
    mIsComplete = false;
    mAllWavesComplete = false;
    mAllPermsComplete = false;
    mDidSpawn = false;
    mCandidateWaveDelay = 0;
}

/*
void LevelSection::Restart() {
    mRemoveActiveWaveList.RemoveAll();
    mActiveWaveList.RemoveAll();
    mCandidateWaveIndex = mStartWaveIndex;
    mCandidateWave = NULL;
    mIsComplete = false;
    mCandidateWaveDelay = 0;
}
*/

void LevelSection::Spawn() {
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        aPerm->Prepare();
    }
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        aPerm->Spawn();
    }
    mDidSpawn = true;
}

void LevelSection::Update() {
    
    bool aBlockWaves = false;
    
    
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        aPerm->mIsPlayingEnter = false;
        aPerm->mIsPlayingExit = false;
    }
    
    
    if (mFlyInType != SECTION_FLY_NONE) {
        
        mFlyInTimer += 1;
        
        if (mFlyInTimer >= mFlyInTime) {
            mFlyInType = SECTION_FLY_NONE;
            mFlyInTimer = mFlyInTime;
            mX = 0.0f;
            mY = 0.0f;
        } else {
            
            float aStartX = 0.0f;
            float aStartY = 0.0f;
            
            float aEndX = 0.0f;
            float aEndY = 0.0f;
            
            if (mFlyInType == SECTION_FLY_LEFT) {
                aStartX = -(GAME_WIDTH + GAME_WIDTH / 4);
                aStartY = 0;
            }
            if (mFlyInType == SECTION_FLY_TOP) {
                aStartX = 0;
                aStartY = -(GAME_HEIGHT);
            }
            if (mFlyInType == SECTION_FLY_RIGHT) {
                aStartX = GAME_WIDTH + GAME_WIDTH / 4;
                aStartY = 0;
            }
            
            float aPercent = ((float)mFlyInTimer) / ((float)mFlyInTime);
            if (aPercent <= 0.0f) { aPercent = 0.0f; }
            if (aPercent >= 1.0f) { aPercent = 1.0f; }
            
            mX = aStartX + (aEndX - aStartX) * aPercent;
            mY = aStartY + (aEndY - aStartY) * aPercent;
            
            aBlockWaves = true;
        }
    }
    
    
    if (mFlyOutType != SECTION_FLY_NONE) {
        
        mFlyOutTimer += 1;
        
        if (mFlyOutTimer >=  mFlyOutTime) {
            mFlyOutType = SECTION_FLY_NONE;
            mFlyOutTimer = mFlyOutTime;
            mX = 0.0f;
            mY = 0.0f;
        } else {
            
            float aStartX = 0.0f;
            float aStartY = 0.0f;
            
            float aEndX = 0.0f;
            float aEndY = 0.0f;
            
            if (mFlyOutType == SECTION_FLY_LEFT) {
                aEndX = -(GAME_WIDTH + GAME_WIDTH / 4);
                aEndY = 0;
            }
            if (mFlyOutType == SECTION_FLY_TOP) {
                aEndX = 0;
                aEndY = -(GAME_HEIGHT);
            }
            if (mFlyOutType == SECTION_FLY_RIGHT) {
                aEndX = GAME_WIDTH + GAME_WIDTH / 4;
                aEndY = 0;
            }
            
            float aPercent = ((float)mFlyOutTimer) / ((float)mFlyOutTime);
            if (aPercent <= 0.0f) { aPercent = 0.0f; }
            if (aPercent >= 1.0f) { aPercent = 1.0f; }
            
            mX = aStartX + (aEndX - aStartX) * aPercent;
            mY = aStartY + (aEndY - aStartY) * aPercent;
        }
    }
    
    
    
    
    
    if (mFlyInType != SECTION_FLY_NONE) {
        EnumList(LevelSectionPerm, aPerm, mPermList) {
            aPerm->mIsPlayingEnter = true;
        }
    }
    
    if (mFlyOutType != SECTION_FLY_NONE) {
        EnumList(LevelSectionPerm, aPerm, mPermList) {
            aPerm->mIsPlayingExit = true;
        }
    }
    
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        aPerm->Update();
    }
    
    
    if (mDelay > 0) {
        --mDelay;
        return;
    }
    
    
    
    mAllWavesComplete = true;
    mAllPermsComplete = true;
    
    if (mDidSpawn == false) {
        mAllWavesComplete = false;
        mAllPermsComplete = false;
        mIsComplete = false;
    }
    
    if (mCandidateWaveIndex < mWaveList.mCount) {
        mAllWavesComplete = false;
    }
    
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        if (aPerm->IsClearForSectionCompletion() == false) {
            mAllPermsComplete = false;
        }
    }
    
    if (mCandidateWave == NULL && aBlockWaves == false) {
        mCandidateWave = (LevelWave *)mWaveList.Fetch(mCandidateWaveIndex);
        if (mCandidateWave != NULL) {
            if (mCandidateWaveIndex > mStartWaveIndex) {
                mCandidateWaveDelay = mCandidateWave->mCreationDelay;
            } else {
                mCandidateWaveDelay = 0;
            }
            ++mCandidateWaveIndex;
        }
    }
    
    if (mCandidateWave != NULL) {
        
        bool aCanSpawnWave = true;
        
        if (mCandidateWave->mCreationRequiresPrevWaveStart == true) {
            //Always yes...
        }
        
        bool aAllComplete = true;
        EnumList(LevelWave, aWave, mActiveWaveList) {
            if (aWave->mIsComplete == false) {
                aAllComplete = false;
            }
        }
        
        if (mCandidateWave->mCreationRequiresPrevWaveComplete == true) {
            if (aAllComplete == false) {
                aCanSpawnWave = false;
            }
        }
        
        //if (gGame->IsWaveClearForSpawn()) {
        //    aCanSpawnWave = true;
        //}
        
        if (mCandidateWave->mCreationRequiresScreenWavesClear == true) {
            if (gGame != NULL) {
                if (gGame->IsScreenClearForSpawn(false) == false) {
                    aCanSpawnWave = false;
                }
            }
        }
        
        if (mCandidateWave->mCreationRequiresScreenPermsClear == true) {
            if (gGame != NULL) {
                if (gGame->IsScreenClearForSpawn(true) == false) {
                    aCanSpawnWave = false;
                }
            }
        }
        
        if (aCanSpawnWave) {
            if (mCandidateWaveDelay > 0) {
                mCandidateWaveDelay--;
            } else {
                
                mActiveWaveList.Add(mCandidateWave);
                mCandidateWave->Prepare();
                mCandidateWave = NULL;
                
                bool aCheckAhead = true;
                while (aCheckAhead == true) {
                    aCheckAhead = false;
                    
                    LevelWave *aCheckWave = (LevelWave *)mWaveList.Fetch(mCandidateWaveIndex);
                    if (aCheckWave != NULL && aCheckWave->mCreationDelay == 0) {
                        
                        //All the conditions to insta-spawn these preceeding waves...
                        
                        //mCreationRequiresPrevWaveStart; (Don't Care)
                        //mCreationRequiresPrevWaveComplete; (Can't Do It)
                        //mCreationRequiresScreenWavesClear; (Can't Do It)
                        //mCreationRequiresScreenPermsClear; (Can't Do It)
                        if (   aCheckWave->mCreationRequiresPrevWaveComplete == false
                            && aCheckWave->mCreationRequiresScreenWavesClear == false
                            && aCheckWave->mCreationRequiresScreenPermsClear == false) {
                            
                            mActiveWaveList.Add(aCheckWave);
                            aCheckWave->Prepare();
                            aCheckAhead = true;
                            ++mCandidateWaveIndex;
                        }
                    }
                }
            }
        }
    }
    
    EnumList(LevelWave, aWave, mActiveWaveList) {
        if (aWave->mIsComplete == false) {
            mAllWavesComplete = false;
        }
    }
    
    if (mCandidateWave != NULL) {
        mAllWavesComplete = false;
    }
    
    if (mAllWavesComplete == true && mAllPermsComplete == true) {
        mIsComplete = true;
    }
    
    if (gGame->mTestOverlay != NULL) {
        gGame->mTestOverlay->SetBubbleStatusWavesComplete(mName.c(), mAllWavesComplete);
        gGame->mTestOverlay->SetBubbleStatusPermsComplete(mName.c(), mAllPermsComplete);
        gGame->mTestOverlay->SetBubbleStatusAllComplete(mName.c(), mIsComplete);
        gGame->mTestOverlay->SetBubbleStatusHasObjects(mName.c(), HasAnyObjects());
    }
    
    EnumList(LevelWave, aWave, mActiveWaveList) {
        aWave->Update();
        if (aWave->mIsComplete) {
            mRemoveActiveWaveList.Add(aWave);
        }
    }
    EnumList(LevelWave, aWave, mRemoveActiveWaveList) {
        mActiveWaveList.Remove(aWave);
    }
    mRemoveActiveWaveList.RemoveAll();
    
    EnumList(LevelWave, aWave, mKillWaveList) {
        if (mCandidateWave == aWave) { mCandidateWave = NULL; }
        aWave->mKillTimer--;
        if (aWave->mKillTimer <= 0) { mDeleteWaveList.Add(aWave); }
    }
    EnumList(LevelWave, aWave, mDeleteWaveList) {
        mKillWaveList.Remove(aWave);
        delete aWave;
    }
    mDeleteWaveList.RemoveAll();
}

void LevelSection::Draw() {
    
}

void LevelSection::DisposeObject(GameObject *pObject) {
    EnumList(LevelWave, aWave, mWaveList) {
        aWave->DisposeObject(pObject);
    }
    
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        aPerm->DisposeObject(pObject);
    }
    
}

void LevelSection::AddWave(LevelWave *pLevelWave) {
    mWaveList.Add(pLevelWave);
}

void LevelSection::AddPerm(LevelSectionPerm *pPerm) {
    mPermList.Add(pPerm);
}

void LevelSection::FlyInReset(int pType) {
    mFlyInType = pType;
    mFlyInTimer = 0;
    Update();
}

void LevelSection::FlyOut(int pType) {
    mFlyOutType = pType;
    mFlyOutTimer = 0;
    Update();
}

//Do we have any objects sitting on the board?
//Note: Be careful, this will assume that all spawning has taken place...
bool LevelSection::HasAnyObjects() {
    if (mIsComplete == false) { return true; }
    
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        if (aPerm->HasAnyObjects() == true) {
            return true;
        }
    }
    
    return false;
}

bool LevelSection::HasAnyPermanents() {
    return (mPermList.mCount > 0);
}

bool LevelSection::HasAllPermanents() {
    return (mWaveList.mCount == 0) && (mPermList.mCount > 0);
}

bool LevelSection::HasAnyWaves() {
    return (mWaveList.mCount > 0);
}

bool LevelSection::HasAllWaves() {
    return (mWaveList.mCount > 0) && (mPermList.mCount == 0);
}

void LevelSection::HandOffAllPermanentGameObjects(FList *pList) {
    
    EnumList(LevelSectionPerm, aPerm, mPermList) {
        aPerm->HandOffAllGameObjects(pList);
    }
    
    Log("Handing off all game objects, count = %d\n", pList->mCount);
    
    
}


void LevelSection::Load(const char *pFile) {
    
    mName = pFile;
    mName.RemovePath();
    mName.RemoveExtension();
    
    mLoadError = false;
    
    LevelSectionBlueprint aBlueprint;
    FJSON aJSON;
    aJSON.Load(pFile);
    
    if (aJSON.mRoot == NULL) {
        mLoadError = true;
        return;
    }
    
    aBlueprint.Load(aJSON.mRoot);
    aBlueprint.Build(this);
}
