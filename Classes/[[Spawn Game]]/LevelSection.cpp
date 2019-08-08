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
    
    mDidSpawn = false;
    
    mDelay = 100;
    mKillTimer = 8;
    
    mStartWaveIndex = 0;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mFlyInType = SECTION_FLY_NONE;
    mFlyInTimer = 0;
    mFlyInTime = 200;
    
    mFlyOutType = SECTION_FLY_NONE;
    mFlyOutTimer = 0;
    mFlyOutTime = 200;
    
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
    
    
    EnumList(LevelSectionPermanent, aPerm, mPermList) {
        aPerm->Reset();
        mKillPermList.Add(aPerm);
    }
    mPermList.RemoveAll();
    
    mCandidateWaveIndex = mStartWaveIndex;
    mCandidateWave = NULL;
    mIsComplete = false;
    mDidSpawn = false;
    mCandidateWaveDelay = 0;
}

void LevelSection::Restart() {
    mRemoveActiveWaveList.RemoveAll();
    mActiveWaveList.RemoveAll();
    mCandidateWaveIndex = mStartWaveIndex;
    mCandidateWave = NULL;
    mIsComplete = false;
    mCandidateWaveDelay = 0;
}

void LevelSection::Spawn() {
    Log("LevelSection::Spawn()\n");
    
    EnumList(LevelSectionPermanent, aPerm, mPermList) {
        aPerm->Prepare();
    }
    
    EnumList(LevelSectionPermanent, aPerm, mPermList) {
        aPerm->Spawn();
    }
    
    mDidSpawn = true;
}

void LevelSection::Update() {
    
    bool aAllWavesComplete = true;
    bool aAllPermsComplete = true;
    
    if (mDidSpawn == false) {
        aAllWavesComplete = false;
        aAllPermsComplete = false;
        mIsComplete = false;
    }
    
    
    bool aBlockWaves = false;
    
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
                aStartX = -(GAME_WIDTH + GAME_WIDTH / 2);
                aStartY = 0;
            }
            if (mFlyInType == SECTION_FLY_TOP) {
                aStartX = 0;
                aStartY = -(GAME_HEIGHT + GAME_HEIGHT / 2);
            }
            if (mFlyInType == SECTION_FLY_RIGHT) {
                aStartX = GAME_WIDTH + GAME_WIDTH / 2;
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
                aEndX = -(GAME_WIDTH + GAME_WIDTH / 2);
                aEndY = 0;
            }
            if (mFlyOutType == SECTION_FLY_TOP) {
                aEndX = 0;
                aEndY = -(GAME_HEIGHT + GAME_HEIGHT / 2);
            }
            if (mFlyOutType == SECTION_FLY_RIGHT) {
                aEndX = GAME_WIDTH + GAME_WIDTH / 2;
                aEndY = 0;
            }
            
            float aPercent = ((float)mFlyOutTimer) / ((float)mFlyOutTime);
            if (aPercent <= 0.0f) { aPercent = 0.0f; }
            if (aPercent >= 1.0f) { aPercent = 1.0f; }
            
            mX = aStartX + (aEndX - aStartX) * aPercent;
            mY = aStartY + (aEndY - aStartY) * aPercent;
        }
    }
    
    if (mCandidateWaveIndex >= mWaveList.mCount) {
        if (mActiveWaveList.mCount <= 0) {
            aAllWavesComplete = true;
        }
    }
    
    EnumList(LevelWave, aWave, mActiveWaveList) {
        if (aWave->mIsComplete == false) {
            aAllWavesComplete = false;
        }
    }
    
    EnumList(LevelSectionPermanent, aPerm, mPermList) {
        aPerm->Update();
        if (aPerm->IsClearForSectionCompletion() == false) {
            aAllPermsComplete = false;
        }
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
                
                printf("Spawn Candidate Wave... [%d]\n", mCandidateWaveIndex - 1);
                
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
    
    //bool aAllWavesComplete = true;
    //bool aAllPermsComplete = true;
    
    if (aAllWavesComplete == true && aAllPermsComplete == true) {
        mIsComplete = true;
    }
    
    
    if (gGame->mTestOverlay != NULL) {
        gGame->mTestOverlay->SetBubbleStatusWavesComplete(mName.c(), aAllWavesComplete);
        gGame->mTestOverlay->SetBubbleStatusPermsComplete(mName.c(), aAllPermsComplete);
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
    
    EnumList(LevelSectionPermanent, aPerm, mPermList) {
        if (aPerm->HasAnyObjects() == true) {
            return true;
        }
    }
    
    return false;
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




