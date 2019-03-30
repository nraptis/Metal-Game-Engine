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
    mAliveTimer = 0;
    mIsComplete = false;
    mRight = true;
    
    //for (int i=0;i<5;i++) {
    //    LevelWaveSpawn *aSpawn = new LevelWaveSpawn(this, &mPath);
    //    mSpawnList.Add(aSpawn);
    //}
    mSpawnIndex = 0;
    
    
    mSpawnSeparationDistance = 90.0f;
    
    mKillTimer = 8;
}

LevelWave::~LevelWave() {
    FreeList(LevelWaveSpawn, mSpawnList);
    FreeList(LevelWaveSpawn, mSpawnKillList);
    FreeList(LevelWaveSpawn, mSpawnDeleteList);
}

void LevelWave::Reset() {
    mPath.Reset();
    EnumList(LevelWaveSpawn, aSpawn, mSpawnList) {
        aSpawn->Reset();
        mSpawnKillList.Add(aSpawn);
    }
    mSpawnList.RemoveAll();
    mSpawnIndex = 0;
}

void LevelWave::Restart() {
    
}

void LevelWave::Spawn() {
    Log("LevelWave::Spawn()");
    
    Balloon *aBalloon = new Balloon();
    if (mRight) {
        aBalloon->mTransform.mX = gGame->mWidth;
        aBalloon->mTransform.mY = gGame->mHeight * 0.33f;
        
        aBalloon->mVelX = -2.0f;
        aBalloon->mVelY = 0.01f;
    } else {
        aBalloon->mTransform.mX = 0.0f;
        aBalloon->mTransform.mY = gGame->mHeight * 0.33f;
        
        aBalloon->mVelX = 2.0f;
        aBalloon->mVelY = 0.01f;
    }
    
    gGame->mBalloonList.Add(aBalloon);
    
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
            aSpawn->mPathIndex += 1;
            if (aSpawn->mPathIndex >= mPath.mPath.mCount) {
                aSpawn->mIsComplete = true;
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
                        
                        if (aPrevSpawn->mDistanceTraveled > (mSpawnSeparationDistance + aSpawn->mOffsetSpawnDistance)) {
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
    

    
    
    
}

void LevelWave::Draw() {
    for (int i=0;i<mSpawnIndex;i++) {
        LevelWaveSpawn *aSpawn = (LevelWaveSpawn *)mSpawnList.Fetch(i);
        if (aSpawn != NULL) {
            aSpawn->Draw();
        }
    }
}

void LevelWave::Dispose() {
    
}

void LevelWave::DisposeObject(GameObject *pObject) {
    
}











