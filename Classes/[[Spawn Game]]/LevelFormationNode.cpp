//
//  LevelFormationNodeFormationNode.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//



#include "LevelFormationNode.hpp"
#include "LevelFormationTracer.hpp"
#include "LevelFormation.hpp"
#include "LevelPath.hpp"
#include "LevelWave.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"
#include "BrickHead.hpp"
#include "Bomb.hpp"
#include "Turtle.hpp"

LevelFormationNode::LevelFormationNode() {
    
    mFormation = NULL;
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    
    mObject = NULL;
    mTracer = NULL;
    
    mDidOriginateOnWave = false;
    mDidOriginateAsPermanent = false;
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
    
    mPathIndexOffset = 0;
    
    mKillTimer = 8;
}

LevelFormationNode::~LevelFormationNode() {
    if (mObject) {
        gGame->DisposeObject(mObject);
        mObject = NULL;
    }
}

void LevelFormationNode::Spawn() {
    
    if (mObjectType == GAME_OBJECT_TYPE_BALLOON) {
        mObject = new Balloon();
        gGame->mBalloonList.Add(mObject);
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
        mObject->mDidOriginateOnWave = mDidOriginateOnWave;
        mObject->mDidOriginateAsPermanent = mDidOriginateAsPermanent;
        
        mObject->mTransform.mX = mBaseX;
        mObject->mTransform.mY = mBaseY;
        
        PositionObject();
    }
}

void LevelFormationNode::Reset() {
    
    if (mObject) {
        gGame->DisposeObject(mObject);
        mObject = NULL;
    }
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
}

void LevelFormationNode::Update() {
    PositionObject();
    
    if (mObject != NULL && mObject->mKill != 0) {
        mObject = NULL;
    }
}

void LevelFormationNode::Draw() {
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.25f, 0.65f, 0.85f, 0.85f);
    Graphics::DrawPoint(mX, mY, 4.0f);
    Graphics::SetColor();
}

void LevelFormationNode::DisposeObject(GameObject *pObject) {
    if (mObject != NULL && mObject == pObject) {
        Log("LevelFormationNode::SUCCESS - DisposeObject(%llx)\n", pObject);
        mObject = NULL;
    }
}

void LevelFormationNode::PositionObject() {
    
    
    //mTracer
    
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
                Log("Miss?\n");
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
    
    if (mObject != NULL) {
        mObject->mTransform.mX = mX;
        mObject->mTransform.mY = mY;
    }
}

LevelFormationNode *LevelFormationNode::Clone(LevelFormation *pFormation) {
    
    LevelFormationNode *aClone = new LevelFormationNode();
    
    aClone->mBaseX = mBaseX;
    aClone->mBaseY = mBaseY;
    aClone->mObjectType = mObjectType;
    
    return aClone;
}











