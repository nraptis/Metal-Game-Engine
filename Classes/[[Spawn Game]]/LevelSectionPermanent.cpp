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
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mKillTimer = 8;
}

LevelSectionPermanent::~LevelSectionPermanent() {
    
}

void LevelSectionPermanent::Reset() {
    mPath.Reset();
    
    if (mObject != NULL) {
        mObject->Kill();
        mObject = NULL;
    }
}

void LevelSectionPermanent::Restart() {
    
}

void LevelSectionPermanent::Prepare() {
    mPath.Finalize();
}

void LevelSectionPermanent::Spawn() {
    
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
    
    if (mObjectType == GAME_OBJECT_TYPE_BALLOON) {
        mObject = new Balloon();
        ((Balloon *)mObject)->mSprite = &(gApp->mBalloonMap[3]);
        gGame->mBalloonList.Add(mObject);
    }
    
    if (mObjectType == GAME_OBJECT_TYPE_BRICKHEAD) {
        mObject = new BrickHead();
        gGame->mBrickHeadList.Add(mObject);
    }
    
    
    //mBaseX = 0.0f;
    //mBaseY = 0.0f;
    
    if (mObject != NULL) {
        mObject->mDidOriginateOnWave = false;
        mObject->mDidOriginateAsPermanent = true;
    }
    
    PositionObject();
}

void LevelSectionPermanent::Update() {
    
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
