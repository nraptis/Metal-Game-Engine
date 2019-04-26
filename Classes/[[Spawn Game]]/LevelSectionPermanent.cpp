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

LevelSectionPermanent::LevelSectionPermanent(LevelSection *pSection) {
    mSection = pSection;
    
    mObject = NULL;
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
    
    mSpawnEqualSpacing = true;
    mSpawnSpacing = 90;
    
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mKillTimer = 8;
}

LevelSectionPermanent::~LevelSectionPermanent() {
    
    FreeList(LevelPermSpawn, mSpawnList);
    FreeList(LevelPermSpawn, mSpawnKillList);
    FreeList(LevelPermSpawn, mSpawnDeleteList);
    
}

void LevelSectionPermanent::Reset() {
    
    
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

void LevelSectionPermanent::Restart() {
    
}

void LevelSectionPermanent::Prepare() {
    
    
    
    for (int i=0;i<mPath.mNodeList.mCount;i++) {
        LevelPathNode *aNode = ((LevelPathNode *)mPath.mNodeList.Fetch(i));
        
        
        printf("Node[%d] (%f x %f) \n", i, aNode->mX, aNode->mY);
        
    }
    
    mPath.Finalize();
    
    
    
}

void LevelSectionPermanent::Spawn() {
    
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
    
    
    //Either we are using the path or no...
    
    if (mPath.mNodeList.mCount > 0 &&
        mPath.mDidFailFinalize == false &&
        mPath.mDidFinalize == true &&
        mSpawnList.mCount > 0 &&
        mPath.mPath.mCount > 1) { //Are we super sure that we can do this?
        
        //One case, we are evenly spawned..
        
        // = true;
        //mSpawnSpacing = 90;
        
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
        
        if (mObjectType == GAME_OBJECT_TYPE_BALLOON) {
            mObject = new Balloon();
            
            //TODO: For auto-tech
            //((Balloon *)mObject)->mSprite = &(gApp->mBalloonMap[3]);
            
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
}

void LevelSectionPermanent::Draw() {
    
    mPath.Draw();
    
}

void LevelSectionPermanent::DisposeObject(GameObject *pObject) {
    
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
    
    /*
    if (gGame != NULL) {
        
        if (mTracer != NULL && mTracer->mPath.mCount > 2) {
            
            
            int aPathIndex = mTracer->mPathIndex + mPathIndexOffset;
            
            int aCeil = (mTracer->mPath.mCount - 1);
            aPathIndex = aPathIndex % aCeil;
            
            if (aPathIndex >= 0 && aPathIndex < mTracer->mPath.mCount) {
                
                mX = mTracer->mPath.mX[aPathIndex];
                mY = mTracer->mPath.mY[aPathIndex];
                
                
                if (mFormation->mRotation != 0.0f) {
                    FVec2 aPoint;
                    aPoint.mX = mX; aPoint.mY = mY;
                    aPoint = PivotPoint(aPoint, mFormation->mRotation);
                    mX = aPoint.mX; mY = aPoint.mY;
                }
                
                mX += mFormation->mX;
                mY += mFormation->mY;
                
            } else {
                printf("Miss?\n");
            }
            
            
            
            
        } else if (mFormation != NULL) {
            
            float aLeft = gGame->mGameAreaLeft;
            float aRight = gGame->mGameAreaRight;
            float aTop = gGame->mGameAreaTop;
            float aBottom = gGame->mGameAreaBottom;
            
            float aWidth = aRight - aLeft;
            float aHeight = aBottom - aTop;
            
            mX = (mBaseX / 100.0f) * aWidth;
            mY = (mBaseY / 100.0f) * aHeight;
            
            if (mFormation->mRotation != 0.0f) {
                FVec2 aPoint;
                aPoint.mX = mX; aPoint.mY = mY;
                aPoint = PivotPoint(aPoint, mFormation->mRotation);
                mX = aPoint.mX; mY = aPoint.mY;
            }
            
            mX += mFormation->mX;
            mY += mFormation->mY;
        }
    }
    */
    
    if (mObject != NULL) {
        mObject->mTransform.mX = mX;
        mObject->mTransform.mY = mY;
    }
    
}
