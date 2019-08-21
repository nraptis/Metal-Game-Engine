//
//  LevelSectionPermanent.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelSectionPermanent.hpp"
#include "LevelSection.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"
#include "FormationCollection.hpp"


LevelSectionPermanent::LevelSectionPermanent(LevelSection *pSection) {
    mSection = pSection;
    
    mDidSpawn = false;
    
    mObject = NULL;
    mFormation = NULL;
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
    
    mSpawnEqualSpacing = true;
    mSpawnSpacing = 120;
    
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mKillTimer = 8;
}

LevelSectionPermanent::~LevelSectionPermanent() {
    
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
    
    FreeList(LevelPermSpawn, mSpawnList);
    FreeList(LevelPermSpawn, mSpawnKillList);
    FreeList(LevelPermSpawn, mSpawnDeleteList);
    
}

void LevelSectionPermanent::Reset() {
    
    
    //mFormationID.Clear();
    //mObjectType = GAME_OBJECT_TYPE_BALLOON;
    
    mDidSpawn = false;
    
    EnumList(LevelPermSpawn, aSpawn, mSpawnList) {
        aSpawn->Reset();
        mSpawnKillList.Add(aSpawn);
    }
    mSpawnList.RemoveAll();
    
    
    mPath.Reset();
    
    if (mObject != NULL) {
        mObject->Kill();
        mObject = NULL;
    }
}

void LevelSectionPermanent::Prepare() {
    
    for (int i=0;i<mPath.mNodeList.mCount;i++) {
        //LevelPathNode *aNode = ((LevelPathNode *)mPath.mNodeList.Fetch(i));
        //TODO: We do what here?
    }
    
    mPath.Finalize();
}

void LevelSectionPermanent::Spawn() {
    
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
    
    if (mFormation != NULL) {
        delete mFormation;
        mFormation = NULL;
    }
    
    //Either we are using the path or no...
    
    if (mPath.mNodeList.mCount > 0 &&
        mPath.mDidFailFinalize == false &&
        mPath.mDidFinalize == true &&
        mSpawnList.mCount > 0 &&
        mPath.mPath.mCount > 1) { //Are we super sure that we can do this?
        
        //One case, we are evenly spawned..
        
        if (mSpawnEqualSpacing) {
            for (int i=0;i<mSpawnList.mCount;i++) {
                LevelPermSpawn *aSpawn = ((LevelPermSpawn *)mSpawnList.mData[i]);
                float aPercent = ((float)i) / ((float)mSpawnList.mCount);
                float aPathPos = aPercent * ((float)mPath.mPath.mCount);
                aSpawn->mPathIndex = (int)(round(aPathPos));
            }
        } else {
            
            int aSpawnLoc = 0;
            float aSpawnDist = 0.0f;
            for (int i=0;i<mSpawnList.mCount;i++) {
                LevelPermSpawn *aSpawn = ((LevelPermSpawn *)mSpawnList.mData[i]);
                aSpawnDist += (mSpawnSpacing + aSpawn->mSpacingOffset);
                while (aSpawnLoc < mPath.mDist.mCount) {
                    if (mPath.mDist.mData[aSpawnLoc] >= aSpawnDist) {
                        aSpawnLoc -= 1;
                        break;
                    } else {
                        aSpawnLoc += 1;
                    }
                }
                
                if (aSpawnLoc >= mPath.mDist.mCount) { aSpawnLoc = mPath.mDist.mCount - 1; }
                if (aSpawnLoc < 0) { aSpawnLoc = 0; }
                
                aSpawn->mPathIndex = aSpawnLoc;
            }
        }
        
        EnumList(LevelPermSpawn, aSpawn, mSpawnList) {
            aSpawn->Spawn();
        }
        
    } else {
        
        //We are either an object or formation, free floating...
        
        
        if (mFormationID.mLength > 0) {
            
            mFormation = gFormationCollection.Get(mFormationID.c());
            if (mFormation != NULL) {
                
                mFormation->mDidOriginateAsPermanent = false;
                mFormation->mDidOriginateOnWave = true;
                
                mFormation->mX = mBaseX;
                mFormation->mY = mBaseY;
                mFormation->Spawn(&mMotionController);
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
                
                mObject->mDidOriginateOnWave = false;
                mObject->mDidOriginateAsPermanent = true;
            }
        }
    }
    
    mDidSpawn = true;
    
    PositionObject();
}

void LevelSectionPermanent::Update() {
    
    //////
    //
    EnumList(LevelPermSpawn, aSpawn, mSpawnKillList) {
        aSpawn->mKillTimer--;
        if (aSpawn->mKillTimer <= 0) { mSpawnDeleteList.Add(aSpawn); }
    }
    EnumList(LevelPermSpawn, aSpawn, mSpawnDeleteList) {
        mSpawnKillList.Remove(aSpawn);
        delete aSpawn;
    }
    mSpawnDeleteList.RemoveAll();
    //
    //////
    
    mMotionController.Update();
    
    EnumList(LevelPermSpawn, aSpawn, mSpawnList) {
        aSpawn->Update();
    }
    
    
    if (mObject != NULL && mObject->mKill != 0) {
        mObject = NULL;
    }
    
    
    mPath.Update();
    
    if (mPath.mDidFinalize == true && mPath.mDidFailFinalize == false && mPath.mPath.mCount > 0) {
        
    }
    
    
    PositionObject();
    
    
    if (mFormation != NULL) {
        mFormation->Update(&mMotionController);
    }
    
    if (mObject != NULL) {
        mMotionController.Apply(mX, mY, mObject);
    }
    
}

void LevelSectionPermanent::Draw() {
    
    mPath.Draw();
    
}

void LevelSectionPermanent::DisposeObject(GameObject *pObject) {
    
    
    
    if (mObject == pObject) {
        mObject = NULL;
    }
    
    if (mFormation != NULL) {
        mFormation->DisposeObject(pObject);
    }
    
    EnumList(LevelPermSpawn, aSpawn, mSpawnList) {
        aSpawn->DisposeObject(pObject);
    }
    
}

FVec2 LevelSectionPermanent::ConvertLocalPointToGame(FVec2 pPos) {
    
    FVec2 aResult;
    
    float aX = mX;
    float aY = mY;
    
    if (mSection != NULL) {
        //aX += mSection->mX;
        //aY += mSection->mY;
    }
    
    aResult.mX = pPos.mX + aX;
    aResult.mY = pPos.mY + aY;
    
    return aResult;
}


void LevelSectionPermanent::PositionObject() {
    
    mX = mBaseX;
    mY = mBaseY;
    
    if (mSection != NULL) {
        mX += mSection->mX;
        mY += mSection->mY;
    }
    
    if (mObject != NULL) {
        mObject->mTransform.mX = mX;
        mObject->mTransform.mY = mY;
    }
    
    if (mFormation != NULL) {
        mFormation->mX = mX;
        mFormation->mY = mY;
    }
    
}

bool LevelSectionPermanent::IsClearForSectionCompletion() {
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
    
    EnumList(LevelPermSpawn, aSpawn, mSpawnList) {
        if (aSpawn->IsClearForSectionCompletion() == false) {
            return false;
        }
    }
    
    return true;
}

bool LevelSectionPermanent::HasAnyObjects() {
    
    if (mObject != NULL) {
        return true;
    }
    
    if (mFormation != NULL) {
        if (mFormation->HasAnyObjects() == true) {
            return true;
        }
    }
    
    EnumList(LevelPermSpawn, aSpawn, mSpawnList) {
        if (aSpawn->HasAnyObjects() == true) {
            return true;
        }
    }
    
    return false;
}

void LevelSectionPermanent::HandOffAllGameObjects(FList *pList) {
    
    if (mObject != NULL && pList != NULL) {
        pList->Add(mObject);
    }
    mObject = NULL;
    
    if (mFormation != NULL) {
        mFormation->HandOffAllGameObjects(pList);
    }
    
    EnumList(LevelPermSpawn, aSpawn, mSpawnList) {
        aSpawn->HandOffAllGameObjects(pList);
    }
}
