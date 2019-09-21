//
//  LevelWaveSpawnSpawn.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/23/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawn.hpp"
#include "LevelPath.hpp"
#include "LevelWave.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"
#include "FormationCollection.hpp"

LevelWaveSpawn::LevelWaveSpawn(LevelWave *pWave, LevelPath *pPath) {
    mWave = pWave;
    mPath = pPath;
    mPathIndex = 0;
    mObject = NULL;
    mFormation = NULL;
    mIsComplete = false;
    
    mDidSpawn = false;
    mDidUpdateAfterSpawn = false;
    
    mIsPlayingEnter = false;
    mIsPlayingExit = false;
    
    mOffsetSpawnDistance = 0.0f;
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    mDistanceTraveled = 0.0f;
    
    mWaitTimer = 0;
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
    mKillTimer = 8;
}

LevelWaveSpawn::~LevelWaveSpawn() {
    
    //Log("Dealloc[LevelWaveSpawn:%X] Obj[%d]\n", this, mObject);
    
    if (mObject != NULL) {
        gGame->DisposeObject(mObject);
        mObject = NULL;
    }
    
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
}

void LevelWaveSpawn::Spawn() {
    
    if (mObject != NULL) {
        gGame->DisposeObject(mObject);
        mObject = NULL;
    }
    
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    mDistanceTraveled = 0.0f;
    mIsComplete = false;
    if (mPath->mPath.mCount > 0) {
        mBaseX = mPath->mPath.mX[0];
        mBaseY = mPath->mPath.mY[0];
    }
    
    if (mFormationID.mLength > 0) {
        mFormation = gFormationCollection.Get(mFormationID.c());
        if (mFormation != NULL) {
            
            mFormation->mDidOriginateAsPermanent = false;
            mFormation->mDidOriginateOnWave = true;
            
            mFormation->mX = mBaseX;
            mFormation->mY = mBaseY;
            mFormation->Spawn(&mMotionController, &mFormationConfiguration);
        }
    }
    
    if (mFormation == NULL) {
        
        if (mObjectType == GAME_OBJECT_TYPE_BALLOON) {
            if (gGame->ShouldSpawnFreeLife()) {
                mObject = new FreeLife();
                gGame->mFreeLifeList.Add(mObject);
                gGame->NotifyDidSpawnFreeLife();
            } else {
                mObject = new Balloon();
                gGame->mBalloonList.Add(mObject);
            }
        }
        
        if (mObjectType == GAME_OBJECT_TYPE_BRICKHEAD) {
            mObject = new BrickHead();
            gGame->mBrickHeadList.Add(mObject);
        }
        
        if (mObjectType == GAME_OBJECT_TYPE_BOMB) {
            mObject = new Bomb();
            gGame->mBombList.Add(mObject);
        }
        
        if (mObjectType == GAME_OBJECT_TYPE_TURTLE) {
            mObject = new Turtle();
            gGame->mTurtleList.Add(mObject);
        }
        
        if (mObject != NULL) {
            
            mObject->mDidOriginateAsPermanent = false;
            mObject->mDidOriginateOnWave = true;
            
            mObject->mTransform.mX = mBaseX;
            mObject->mTransform.mY = mBaseY;
            
            
        }
    }
    
    mDidSpawn = true;
    mDidUpdateAfterSpawn = false;
    
    if (mObject != NULL) {
        mObject->mWaveSpawn = this;
        mStyleController.ApplyToObject(mObject);
    }
    if (mFormation != NULL) {
        mFormation->SetWaveSpawn(this);
        mFormation->ApplyStyleController(&mStyleController);
    }
}

void LevelWaveSpawn::DisposeObject(GameObject *pObject) {
    
    if (mObject != NULL && mObject == pObject) {
        mObject = NULL;
    }
    if (mFormation != NULL) {
        mFormation->DisposeObject(pObject);
    }
}

bool LevelWaveSpawn::DidStart() {
    if (mDidSpawn == true) {
        if (mDidUpdateAfterSpawn == true) {
            return true;
        }
    }
    return false;
}

bool LevelWaveSpawn::IsClear() {
    
    if (mDidSpawn == false) {
        return false;
    }
    
    if (mObject != NULL) {
        if (mObject->mKill == 0) {
            return false;
        }
    }
    
    if (mFormation != NULL) {
        if (mFormation->IsClear() == false) {
            return false;
        } else {
            Log("What?\n");
        }
    }
    
    return true;
}







void LevelWaveSpawn::Reset() {
    if (mObject != NULL) {
        gGame->DisposeObject(mObject);
        mObject = NULL;
    }
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
    
    mPathIndex = 0;
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    mDistanceTraveled = 0.0f;
    
    mDidSpawn = false;
    mDidUpdateAfterSpawn = false;
}

void LevelWaveSpawn::Update() {
    
    if (mDidSpawn == true) {
        mDidUpdateAfterSpawn = true;
    }
    
    if (mPathIndex >= 0 && mPathIndex < mPath->mPath.mCount) {
        mBaseX = mPath->mPath.mX[mPathIndex];
        mBaseY = mPath->mPath.mY[mPathIndex];
        mDistanceTraveled = mPath->mDist.mData[mPathIndex];
        mIsPlayingEnter = mPath->mPlayEnter.mData[mPathIndex];
        mIsPlayingExit = mPath->mPlayExit.mData[mPathIndex];
    } else {
        if (mPath->mPath.mCount > 0 && mPathIndex > 0) {
            mBaseX = mPath->mPath.mX[mPath->mPath.mCount - 1];
            mBaseY = mPath->mPath.mY[mPath->mPath.mCount - 1];
            mDistanceTraveled = mPath->mDist.mData[mPath->mDist.mCount - 1];
            mIsPlayingEnter = mPath->mPlayEnter.mData[mPath->mPlayEnter.mCount - 1];
            mIsPlayingExit = mPath->mPlayExit.mData[mPath->mPlayExit.mCount - 1];
        }
    }
    
    mMotionController.mSkipUpdate = false;
    if (mIsPlayingEnter && (mMotionController.mPlayOnEnter == false)) { mMotionController.mSkipUpdate = true; }
    if (mIsPlayingExit && (mMotionController.mPlayOnExit == false)) { mMotionController.mSkipUpdate = true; }
    mMotionController.Update();
    
    if (mObject != NULL) {
        mObject->mTransform.mX = mBaseX;
        mObject->mTransform.mY = mBaseY;
        
        if (mObject->mKill != 0) {
            mObject = NULL;
        } else {
            mMotionController.Apply(mBaseX, mBaseY, mObject);
        }
    }
    
    if (mFormation != NULL) {
        mFormation->mX = mBaseX;
        mFormation->mY = mBaseY;
        mFormation->Update(&mMotionController);
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

void LevelWaveSpawn::HandOffAllGameObjects(FList *pList) {
    
    if (mObject != NULL && pList != NULL) {
        pList->Add(mObject);
    }
    mObject = NULL;
    
    if (mFormation != NULL) {
        mFormation->HandOffAllGameObjects(pList);
    }
}














