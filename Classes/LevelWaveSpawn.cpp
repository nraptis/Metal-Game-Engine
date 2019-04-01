//
//  LevelWaveSpawnSpawn.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/23/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawn.hpp"
#include "LevelWavePath.hpp"
#include "LevelWave.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"

LevelWaveSpawn::LevelWaveSpawn(LevelWave *pWave, LevelWavePath *pPath) {
    mWave = pWave;
    mPath = pPath;
    mPathIndex = 0;
    mObject = NULL;
    mIsComplete = false;
    mOffsetSpawnDistance = 0.0f;
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    mDistanceTraveled = 0.0f;
    mKillTimer = 8;
}

LevelWaveSpawn::~LevelWaveSpawn() {
    
    //printf("Dealloc[LevelWaveSpawn:%X] Obj[%d]\n", this, mObject);
    
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
}

void LevelWaveSpawn::Spawn() {
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    mDistanceTraveled = 0.0f;
    mIsComplete = false;
    if (mPath->mPath.mCount > 0) {
        mBaseX = mPath->mPath.mX[0];
        mBaseY = mPath->mPath.mY[0];
    }
    
    mObject = new Balloon();
    mObject->mTransform.mX = mBaseX;
    mObject->mTransform.mY = mBaseY;
    gGame->mBalloonList.Add(mObject);
}

void LevelWaveSpawn::Reset() {
    
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
    
    mPathIndex = 0;
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    mDistanceTraveled = 0.0f;
}

void LevelWaveSpawn::Restart() {
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
    mPathIndex = 0;
    mIsComplete = false;
    mOffsetSpawnDistance = 0.0f;
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    mDistanceTraveled = 0.0f;
    mKillTimer = 8;
}

void LevelWaveSpawn::Update() {
    if (mPathIndex >= 0 && mPathIndex < mPath->mPath.mCount) {
        
        mBaseX = mPath->mPath.mX[mPathIndex];
        mBaseY = mPath->mPath.mY[mPathIndex];
        mDistanceTraveled = mPath->mDist.mData[mPathIndex];
        
    } else {
        if (mPath->mPath.mCount > 0 && mPathIndex > 0) {
            mBaseX = mPath->mPath.mX[mPath->mPath.mCount - 1];
            mBaseY = mPath->mPath.mY[mPath->mPath.mCount - 1];
            mDistanceTraveled = mPath->mDist.mData[mPath->mDist.mCount - 1];
        }
        
    }
    if (mObject != NULL) {
        mObject->mTransform.mX = mBaseX;
        mObject->mTransform.mY = mBaseY;
    }
}

void LevelWaveSpawn::Draw() {
    
    
    if (mPathIndex >= 0 && mPathIndex < mPath->mPath.mCount) {
        
        float aX = mPath->mPath.mX[mPathIndex];
        float aY = mPath->mPath.mY[mPathIndex];
        
        Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.65f);
        Graphics::DrawPoint(aX, aY, 5.0f);
    }
}


void LevelWaveSpawn::DisposeObject(GameObject *pObject) {
    
}











