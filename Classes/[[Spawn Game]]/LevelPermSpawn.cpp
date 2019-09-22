//
//  LevelPermSpawn.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelPermSpawn.hpp"
#include "LevelPath.hpp"
#include "LevelSectionPerm.hpp"
#include "Game.hpp"
#include "Balloon.hpp"
#include "FormationCollection.hpp"

LevelPermSpawn::LevelPermSpawn(LevelSectionPerm *pPerm, LevelPath *pPath) {
    mPerm = pPerm;
    mPath = pPath;
    mPathIndex = 0;
    mObject = NULL;
    mFormation = NULL;
    
    mIsPlayingEnter = false;
    mIsPlayingExit = false;
    
    
    mDidSpawn = false;
    mDidUpdateAfterSpawn = false;
    
    mWaitTimer = 0;
    
    mSpacingOffset = 0.0f;
    
    mPathX = 0.0f;
    mPathY = 0.0f;
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
    mKillTimer = 8;
}

LevelPermSpawn::~LevelPermSpawn() {
    if (mObject != NULL) {
        gGame->DisposeObject(mObject);
        mObject = NULL;
    }
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
}

void LevelPermSpawn::Spawn() {
    
    if (mObject != NULL) {
        gGame->DisposeObject(mObject);
        mObject = NULL;
    }
    
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
    
    if (mFormationID.mLength > 0) {
        
        mFormation = gFormationCollection.Get(mFormationID.c());
        if (mFormation != NULL) {
            mFormation->mDidOriginateAsPermanent = true;
            mFormation->mDidOriginateOnWave = false;
            
            SetObjectPosition();
            mFormation->Spawn(&mMotionController, &mFormationConfiguration);
            mFormation->ApplyStyleController(&mStyleController);
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
        
        if (mObjectType == GAME_OBJECT_TYPE_TURTLE) {
            mObject = new Turtle();
            gGame->mTurtleList.Add(mObject);
        }
        
        if (mObjectType == GAME_OBJECT_TYPE_BOMB) {
            mObject = new Bomb();
            gGame->mBombList.Add(mObject);
        }
        
        if (mObject != NULL) {
            mObject->mDidOriginateAsPermanent = true;
            mObject->mDidOriginateOnWave = false;
            SetObjectPosition();
        }
    }
    
    mDidSpawn = true;
    mDidUpdateAfterSpawn = false;
    
    
    if (mPath != NULL) {
        if (mPath->mWait.mCount > 0) {
            mWaitTimer = mPath->mWait.mData[0];
        }
    }
    
    if (mObject != NULL) {
        mObject->mPermSpawn = this;
        mStyleController.ApplyToObject(mObject);
    }
    
    if (mFormation != NULL) {
        mFormation->SetPermSpawn(this);
        mFormation->ApplyStyleController(&mStyleController);
    }
    
}

void LevelPermSpawn::DisposeObject(GameObject *pObject) {
    
    if (mObject != NULL && mObject == pObject) {
        mObject = NULL;
    }
    
    if (mFormation != NULL) {
        mFormation->DisposeObject(pObject);
    }
    
}

bool LevelPermSpawn::IsClear() {
    
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
        }
    }
    
    return true;
}

void LevelPermSpawn::Reset() {
    
    if (mObject != NULL) {
        gGame->DisposeObject(mObject);
        mObject = NULL;
    }

    mFormationConfiguration.Reset();
    mMotionController.Reset();
    
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
    
    mPathIndex = 0;
    mPathX = 0.0f;
    mPathY = 0.0f;
    
    mDidSpawn = false;
    mDidUpdateAfterSpawn = false;
}

void LevelPermSpawn::Update() {
    
    if (mDidSpawn == true) {
        mDidUpdateAfterSpawn = true;
    }
    
    if (mDidSpawn == true && mPath != NULL) {
        if (mPath->mPath.mCount > 0) {
            
            
            //mPathIndex += 1;
            //if (mPathIndex >= mPath->mPath.mCount) {
            //    mPathIndex = 0;
            //}
            
            
            if (mWaitTimer > 0) {
                mWaitTimer--;
                if (mWaitTimer <= 0) {
                    if (mPathIndex < mPath->mPath.mCount) {
                        mPathIndex += 1;
                    } else {
                        mPathIndex = 0;
                        mWaitTimer = mPath->mWait.mData[0];
                    }
                }
            } else {
                if (mPathIndex < mPath->mPath.mCount) {
                    mPathIndex += 1;
                }
            }
            
            if (mPathIndex >= mPath->mPath.mCount) {
                if (mWaitTimer <= 0) {
                    mPathIndex = 0;
                    mWaitTimer = mPath->mWait.mData[0];
                }
            } else {
                if (mPath->mWait.mData[mPathIndex] > 0 && mWaitTimer == 0) {
                    mWaitTimer = mPath->mWait.mData[mPathIndex];
                }
            }
        }
    }
    
    
    mMotionController.mSkipUpdate = false;
    if (mIsPlayingEnter && (mMotionController.mPlayOnEnter == false)) { mMotionController.mSkipUpdate = true; }
    if (mIsPlayingExit && (mMotionController.mPlayOnExit == false)) { mMotionController.mSkipUpdate = true; }
    mMotionController.Update();
    
    SetObjectPosition();
    
    if (mObject != NULL) {
        if (mObject->mKill != 0) {
            mObject = NULL;
        } else {
            mMotionController.Apply(mObject->mTransform.mX, mObject->mTransform.mY, mObject);
        }
    }
    
    if (mFormation != NULL) {
        mFormation->Update(&mMotionController);
    }
}

void LevelPermSpawn::Draw() {
    
    if (mPathIndex >= 0 && mPathIndex < mPath->mPath.mCount) {
        
        float aX = mPath->mPath.mX[mPathIndex];
        float aY = mPath->mPath.mY[mPathIndex];
        
        Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.65f);
        Graphics::DrawPoint(aX, aY, 5.0f);
    }
}

void LevelPermSpawn::SetObjectPosition() {
    
    RefreshPathPosition();
    
    float aX = mPathX;
    float aY = mPathY;
    
    if (mPerm != NULL) {
        FVec2 aPos = FVec2(aX, aY);
        aPos = mPerm->ConvertLocalPointToGame(aPos);
        aX = aPos.mX;
        aY = aPos.mY;
    }
    
    
    if (mObject != NULL) {
        mObject->mTransform.mX = aX;
        mObject->mTransform.mY = aY;
        
        if (mObject->mKill != 0) {
            mObject = NULL;
        }
    }
    
    if (mFormation != NULL) {
        mFormation->mX = aX;
        mFormation->mY = aY;
    }
}

void LevelPermSpawn::RefreshPathPosition() {
    mPathX = 0.0f; mPathY = 0.0f;
    int aIndex = mPathIndex;
    if (mPath->mPath.mCount > 0) {
        while (aIndex > mPath->mPath.mCount) {
            aIndex -= mPath->mPath.mCount;
        }
        while (aIndex < 0) {
            aIndex += mPath->mPath.mCount;
        }
        mPathX = mPath->mPath.mX[aIndex];
        mPathY = mPath->mPath.mY[aIndex];
    }
}

bool LevelPermSpawn::IsClearForSectionCompletion() {
    
    if (mDidSpawn == false) { return false; }
    
    if (mObject != NULL) {
        if (mObject->IsRequiredToClearForSectionCompletion() == true) {
            return false;
        }
    }
    
    if (mFormation != NULL) {
        if (mFormation->IsClearForSectionCompletion() == false) {
            return false;
        }
    }
    
    return true;
}

bool LevelPermSpawn::HasAnyObjects() {
    if (mObject != NULL) { return true; }
    if (mFormation != NULL) {
        if (mFormation->HasAnyObjects() == true) {
            return true;
        }
    }
    return false;
}

void LevelPermSpawn::HandOffAllGameObjects(FList *pList) {
    if (mObject != NULL && pList != NULL) {
        pList->Add(mObject);
    }
    mObject = NULL;
    
    if (mFormation != NULL) {
        mFormation->HandOffAllGameObjects(pList);
    }
}









