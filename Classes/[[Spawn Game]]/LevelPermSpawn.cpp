//
//  LevelPermSpawn.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelPermSpawn.hpp"
#include "LevelPath.hpp"
#include "LevelSectionPermanent.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"
#include "FormationCollection.hpp"

LevelPermSpawn::LevelPermSpawn(LevelSectionPermanent *pPerm, LevelPath *pPath) {
    mPerm = pPerm;
    mPath = pPath;
    mPathIndex = 0;
    mObject = NULL;
    mFormation = NULL;
    
    mDidSpawn = false;
    mDidUpdateAfterSpawn = false;
    
    mSpacingOffset = 0.0f;
    
    mPathX = 0.0f;
    mPathY = 0.0f;
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
    mKillTimer = 8;
}

LevelPermSpawn::~LevelPermSpawn() {
    if (mObject != NULL) {
        mObject->Kill();
        mObject = NULL;
    }
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
}

void LevelPermSpawn::Spawn() {
    
    if (mObject != NULL) {
        mObject->Kill();
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
            mFormation->Spawn();
        }
    }
    
    if (mFormation == NULL) {
        
        if (mObjectType == GAME_OBJECT_TYPE_BALLOON) {
            mObject = new Balloon();
            gGame->mBalloonList.Add(mObject);
        }
        
        if (mObjectType == GAME_OBJECT_TYPE_BRICKHEAD) {
            mObject = new BrickHead();
            gGame->mBrickHeadList.Add(mObject);
        }
        
        if (mObject != NULL) {
            mObject->mDidOriginateAsPermanent = true;
            mObject->mDidOriginateOnWave = false;
            SetObjectPosition();
        }
    }
    
    mDidSpawn = true;
    mDidUpdateAfterSpawn = false;
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
        mObject->Kill();
        mObject = NULL;
    }
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
            mPathIndex += 1;
            if (mPathIndex >= mPath->mPath.mCount) {
                mPathIndex = 0;
            }
        }
    }
    
    SetObjectPosition();
    
    if (mObject != NULL) {
        if (mObject->mKill != 0) {
            mObject = NULL;
        }
    }
    
    if (mFormation != NULL) {
        mFormation->Update();
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
        mFormation->Update();
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











