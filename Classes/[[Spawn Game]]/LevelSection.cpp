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
    
    mIsComplete = false;
    mDelay = 100;
    mKillTimer = 8;
    
    mStartWaveIndex = 0;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mFlyInType = SECTION_FLY_IN_NONE;
    mFlyInTimer = 0;
    mFlyInTime = 200;
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
    
    
    EnumList(LevelSectionPermanent, aPerm, mPermList) {
        aPerm->Reset();
        mKillPermList.Add(aPerm);
    }
    mPermList.RemoveAll();
    
    
    mCandidateWaveIndex = mStartWaveIndex;
    mCandidateWave = NULL;
    mCandidateWaveDelay = 0;
}

void LevelSection::Restart() {
    mRemoveActiveWaveList.RemoveAll();
    mActiveWaveList.RemoveAll();
    mCandidateWaveIndex = mStartWaveIndex;
    mCandidateWave = NULL;
    mCandidateWaveDelay = 0;
}

void LevelSection::Spawn() {
    Log("LevelSection::Spawn()\n");
    
    EnumList(LevelSectionPermanent, aPerm, mPermList) {
        aPerm->Spawn();
    
        //TODO: Move per fly-in...
    
    }
    
    
}

void LevelSection::Update() {
    
    
    bool aBlockWaves = false;
    
    
    if (mFlyInType != SECTION_FLY_IN_NONE) {
        
        mFlyInTimer += 1;
        
        if (mFlyInTimer >= mFlyInTime) {
            mFlyInType = SECTION_FLY_IN_NONE;
            mFlyInTimer = mFlyInTime;
            mX = 0.0f;
            mY = 0.0f;
        } else {
            
            float aStartX = 0.0f;
            float aStartY = 0.0f;
            
            float aEndX = 0.0f;
            float aEndY = 0.0f;
            
            if (mFlyInType == SECTION_FLY_IN_LEFT) {
                aStartX = -GAME_WIDTH;
                aStartY = 0;
            }
            if (mFlyInType == SECTION_FLY_IN_TOP) {
                aStartX = 0;
                aStartY = -GAME_HEIGHT;
            }
            if (mFlyInType == SECTION_FLY_IN_RIGHT) {
                aStartX = GAME_WIDTH;
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
    
    EnumList(LevelSectionPermanent, aPerm, mPermList) {
        aPerm->Update();
    }
    
    
    
    if (mDelay > 0) {
        --mDelay;
        //Log("LevelSection::Delay(%d)\n", mDelay);
        
        if (mDelay <= 0) {
            Log("About to spawn First Wave...\n");
        }
        return;
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
        
        bool aCanSpawnWave = false;
        
        
        
       
        
        if (mCandidateWave->mCreationType == WAVE_CREATION_TYPE_PREV_WAVE_END ||
            mCandidateWave->mCreationType == WAVE_CREATION_TYPE_PREV_WAVE_CLEAR) {
            
            bool aAllComplete = true;
            
            EnumList(LevelWave, aWave, mActiveWaveList) {
                if (aWave->mIsComplete == false) {
                    aAllComplete = false;
                }
            }
            
            if (aAllComplete) {
                if (mCandidateWave->mCreationType == WAVE_CREATION_TYPE_PREV_WAVE_END) {
                    aCanSpawnWave = true;
                }
                if (mCandidateWave->mCreationType == WAVE_CREATION_TYPE_PREV_WAVE_CLEAR) {
                    if (gGame->IsWaveClearForSpawn()) {
                        aCanSpawnWave = true;
                    }
                }
            }
        } else if (mCandidateWave->mCreationType == WAVE_CREATION_TYPE_SCREEN_CLEAR_IGNORE_PERMS) {
            if (gGame->IsScreenClearForSpawn(false)) {
                aCanSpawnWave = true;
            }
        } else if (mCandidateWave->mCreationType == WAVE_CREATION_TYPE_SCREEN_CLEAR_AND_PERMS) {
            if (gGame->IsScreenClearForSpawn(true)) {
                aCanSpawnWave = true;
            }
        } else {//}  if (mCandidateWave->mCreationType == WAVE_CREATION_TYPE_PREV_WAVE_START) {
            aCanSpawnWave = true;
        }
        
        if (aCanSpawnWave) {
            if (mCandidateWaveDelay > 0) {
                mCandidateWaveDelay--;
            } else {
                
                printf("Spawn Candidate Wave... [%d]\n", mCandidateWaveIndex - 1);
                
                mActiveWaveList.Add(mCandidateWave);
                mCandidateWave->Prepare();
                mCandidateWave = NULL;
                
                bool aCheckAhead = true;
                while (aCheckAhead == true) {
                    aCheckAhead = false;
                    
                    LevelWave *aCheckWave = (LevelWave *)mWaveList.Fetch(mCandidateWaveIndex);
                    if (aCheckWave != NULL) {
                        if (aCheckWave->mCreationType == WAVE_CREATION_TYPE_PREV_WAVE_START
                            && aCheckWave->mCreationDelay == 0) {
                            printf("Spawn Subsequent Wave... [%d]\n", mCandidateWaveIndex);
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
}

void LevelSection::AddWave(LevelWave *pLevelWave) {
    mWaveList.Add(pLevelWave);
}

void LevelSection::AddPerm(LevelSectionPermanent *pPerm) {
    mPermList.Add(pPerm);
}

void LevelSection::FlyInReset(int pType) {
    mFlyInType = pType;
    mFlyInTimer = 0;
}

void LevelSection::Load(const char *pFile) {
    LevelSectionBlueprint aBlueprint;
    FJSON aJSON;
    aJSON.Load(pFile);
    aBlueprint.Load(aJSON.mRoot);
    aBlueprint.Build(this);
}




