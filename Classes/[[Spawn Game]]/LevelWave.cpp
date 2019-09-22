//
//  LevelWave.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWave.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"

LevelWave::LevelWave() {
    
    mIsComplete = false;
    
    mExitType = WAVE_EXIT_TYPE_DISPERSE;
    
    //mCreationType = WAVE_CREATION_TYPE_PREV_WAVE_START;
    
    mCreationRequiresPrevWaveStart = false;
    mCreationRequiresPrevWaveComplete = false;
    mCreationRequiresScreenWavesClear = false;
    mCreationRequiresScreenPermsClear = false;
    
    mCreationDelay = 0;
    
    mSpawnIndex = 0;
    
    mSpawnSpacing = 120.0f;
    
    mKillTimer = 8;
}

LevelWave::~LevelWave() {
    FreeList(LevelWaveSpawn, mSpawnList);
    FreeList(LevelWaveSpawn, mSpawnKillList);
    FreeList(LevelWaveSpawn, mSpawnDeleteList);
}


void LevelWave::Reset() {
    mIsComplete = false;
    mPath.Reset();
    EnumList(LevelWaveSpawn, aSpawn, mSpawnList) {
        aSpawn->Reset();
        mSpawnKillList.Add(aSpawn);
    }
    mSpawnList.RemoveAll();
    mSpawnIndex = 0;
}

/*
void LevelWave::Restart() {
    mIsComplete = false;
    EnumList(LevelWaveSpawn, aSpawn, mSpawnList) {
        aSpawn->Restart();
    }
    mSpawnIndex = 0;
}
*/

void LevelWave::Prepare() {
    mPath.Finalize();
}

void LevelWave::Update() {
    //////
    //
    EnumList(LevelWaveSpawn, aSpawn, mSpawnKillList) {
        aSpawn->mKillTimer--;
        if (aSpawn->mKillTimer <= 0) { mSpawnDeleteList.Add(aSpawn); }
    }
    EnumList(LevelWaveSpawn, aSpawn, mSpawnDeleteList) {
        mSpawnKillList.Remove(aSpawn);
        delete aSpawn;
    }
    mSpawnDeleteList.RemoveAll();
    //
    //////
    
    
    mPath.Update();
    
    if (mSpawnList.mCount <= 0) {
        mIsComplete = true;
        return;
    }
    
    
    for (int i=0;i<mSpawnIndex;i++) {
        LevelWaveSpawn *aSpawn = (LevelWaveSpawn *)mSpawnList.Fetch(i);
        if (aSpawn != NULL && aSpawn->mIsComplete == false) {
            
            
            if (aSpawn->mWaitTimer > 0) {
                aSpawn->mWaitTimer--;
                if ((aSpawn->mWaitTimer <= 0) || (aSpawn->mDidShortCircuit == true)) {
                    aSpawn->mWaitTimer = 0;
                    if (aSpawn->mPathIndex < mPath.mPath.mCount) {
                        aSpawn->mPathIndex += 1;
                    }
                }
            } else {
                if (aSpawn->mPathIndex < mPath.mPath.mCount) {
                    aSpawn->mPathIndex += 1;
                }
            }
            
            bool aComplete = false;
            
            
            if (aSpawn->mPathIndex >= mPath.mPath.mCount) {
                if ((aSpawn->mWaitTimer <= 0) || (aSpawn->mDidShortCircuit == true)) {
                    aSpawn->mWaitTimer = 0;
                    aComplete = true;
                }
            } else {
                if (mPath.mWait.mData[aSpawn->mPathIndex] > 0 && aSpawn->mWaitTimer == 0) {
                    
                    
                    if (aSpawn->mDidShortCircuit == false) {
                    
                        aSpawn->mWaitTimer = mPath.mWait.mData[aSpawn->mPathIndex];
                        aSpawn->mCurrentWaitTime = aSpawn->mWaitTimer;
                        aSpawn->mCurrentWaitTick = 0;
                        
                    }
                }
            }
            
            if (aSpawn->DidStart() && aSpawn->IsClear()) {
                aComplete = true;
            }
            
            if (aComplete) {
                aSpawn->mIsComplete = true;
                
                //HOOK: The wave is complete at this point...
                mRecentlyCompletedList.Add(aSpawn);
                
            }
            
        }
        if (aSpawn != NULL) {
            aSpawn->Update();
        }
    }
    
    if (mPath.mDidFinalize == true && mPath.mDidFailFinalize == false && mPath.mPath.mCount > 0) {
        if (mSpawnIndex >= 0 && mSpawnIndex < mSpawnList.mCount) {
            LevelWaveSpawn *aPrevSpawn = (LevelWaveSpawn *)mSpawnList.Fetch(mSpawnIndex - 1);
            LevelWaveSpawn *aSpawn = (LevelWaveSpawn *)mSpawnList.Fetch(mSpawnIndex);
            if (aSpawn !=  NULL) {
                bool aShouldSpawn = false;
                if (aPrevSpawn != NULL) {
                    
                    if (aPrevSpawn->mIsComplete) {
                        aShouldSpawn = true;
                    } else {
                        
                        if (aPrevSpawn->mDistanceTraveled > (mSpawnSpacing + aSpawn->mOffsetSpawnDistance)) {
                            aShouldSpawn = true;
                        }
                    }
                } else {
                    aShouldSpawn = true;
                }
                if (aShouldSpawn) {
                    if (aSpawn) {
                        aSpawn->Spawn();
                        mSpawnIndex += 1;
                    }
                }
            }
        }
    }
    
    EnumList(LevelWaveSpawn, aSpawn, mRecentlyCompletedList) {
        HandleSpawnComplete(aSpawn);
    }
    mRecentlyCompletedList.RemoveAll();
    
    
    
    
    if (mSpawnIndex >= mSpawnList.mCount) {
        
        bool aComplete = true;
        
        EnumList(LevelWaveSpawn, aSpawn, mSpawnList) {
            if (aSpawn->mIsComplete == false) {
                aComplete = false;
            }
        }
        
        if (aComplete == true) {
            mIsComplete = true;
        }
    }
}

void LevelWave::Draw() {
    for (int i=0;i<mSpawnIndex;i++) {
        LevelWaveSpawn *aSpawn = (LevelWaveSpawn *)mSpawnList.Fetch(i);
        if (aSpawn != NULL) {
            //aSpawn->Draw();
            
        }
    }
}

void LevelWave::DisposeObject(GameObject *pObject) {
    for (int i=0;i<mSpawnIndex;i++) {
        LevelWaveSpawn *aSpawn = (LevelWaveSpawn *)mSpawnList.Fetch(i);
        aSpawn->DisposeObject(pObject);
    }
}


void LevelWave::HandleSpawnComplete(LevelWaveSpawn *pSpawn) {
    
    FList aList;
    if (pSpawn) {
        pSpawn->HandOffAllGameObjects(&aList);
    }
    
    if (mExitType == WAVE_EXIT_TYPE_INSTANT) {
        for (int i=0;i<aList.mCount;i++) {
            GameObject *aObject = ((GameObject *)aList.mData[i]);
            if (gGame != NULL) {
                gGame->FlyOffEscape(aObject);
            }
        }
    } else { //Default is DISPERSE
        if (gGame != NULL) {
            gGame->mRecentFloatingAwayTick = 4;
        }
        
        if (aList.mCount > 1) {
            
            float aCenterX = 0.0f;
            float aCenterY = 0.0f;
            
            for (int i=0;i<aList.mCount;i++) {
                GameObject *aObject = ((GameObject *)aList.mData[i]);
                aCenterX += aObject->mTransform.mX;
                aCenterY += aObject->mTransform.mY;
            }
            
            aCenterX /= (float)aList.mCount;
            aCenterY /= (float)aList.mCount;
            
            
            float aMaxDist = 0.0f;
            
            for (int i=0;i<aList.mCount;i++) {
                GameObject *aObject = ((GameObject *)aList.mData[i]);
                float aDist = Distance(aCenterX, aCenterY, aObject->mTransform.mX, aObject->mTransform.mY);
                if (aDist > aMaxDist) {
                    aMaxDist = aDist;
                }
            }
            
            
            for (int i=0;i<aList.mCount;i++) {
                GameObject *aObject = ((GameObject *)aList.mData[i]);
                
                float aDiffX = aObject->mTransform.mX - aCenterX;
                float aDiffY = aObject->mTransform.mY - aCenterY;
                
                float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
                float aMagnitude = 0.0f;
                
                if (aDist > SQRT_EPSILON) {
                    aDist = sqrtf(aDist);
                    aDiffX /= aDist;
                    aDiffY /= aDist;
                } else {
                    aDiffX = 0.0f;
                    aDiffY = 0.0f;
                }
                
                if (aMaxDist > SQRT_EPSILON) { aMagnitude = aDist / aMaxDist; }
                
                aObject->Disperse(aDiffX, aDiffY, aMagnitude);
            }
        } else if (aList.mCount == 1) {
            GameObject *aObject = ((GameObject *)aList.First());
            aObject->Disperse(0.0f, 0.0f, 0.0f);
        }
    }
}












