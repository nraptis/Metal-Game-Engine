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
}

LevelSection::~LevelSection() {
    FreeList(LevelWave, mWaveList);
    FreeList(LevelWave, mKillList);
    mActiveWaveList.RemoveAll();
}

void LevelSection::Reset() {
    mActiveWaveList.RemoveAll();
    EnumList(LevelWave, aWave, mWaveList) {
        aWave->Reset();
        mKillList.Add(aWave);
    }
    mWaveList.RemoveAll();
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
    
    if (mCandidateWave == NULL) {
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
        } else if (mCandidateWave->mCreationType == WAVE_CREATION_TYPE_SCREEN_CLEAR) {
            if (gGame->IsScreenClearForSpawn()) {
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
                
                
                //TODO: Probe forward and spawn every
                //wave with
                // ->mCreationType == WAVE_CREATION_TYPE_PREV_WAVE_START
                // &&  ->mCreationDelay == 0
                //
                
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
    
    
    EnumList(LevelWave, aWave, mKillList) {
        if (mCandidateWave == aWave) { mCandidateWave = NULL; }
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

void LevelSection::DisposeObject(GameObject *pObject) {
    EnumList(LevelWave, aWave, mWaveList) {
        aWave->DisposeObject(pObject);
    }
}

void LevelSection::AddWave(LevelWave *pLevelWave) {
    mWaveList.Add(pLevelWave);
}

void LevelSection::Load(const char *pFile) {
    LevelSectionBlueprint aBlueprint;
    FJSON aJSON;
    aJSON.Load(pFile);
    aBlueprint.Load(aJSON.mRoot);
    aBlueprint.Build(this);
}
