//
//  LevelWaveSpawnFormationNodeFormationNode.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//



#include "LevelWaveSpawnFormationNode.hpp"
#include "LevelWaveSpawnFormationTracer.hpp"
#include "LevelWaveSpawnFormation.hpp"
#include "LevelWavePath.hpp"
#include "LevelWave.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"

LevelWaveSpawnFormationNode::LevelWaveSpawnFormationNode(LevelWaveSpawnFormation *pFormation) {
    
    mFormation = pFormation;
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    
    mObject = NULL;
    mTracer = NULL;
    
    mPathIndexOffset = 0;
    
    mKillTimer = 8;
}

LevelWaveSpawnFormationNode::~LevelWaveSpawnFormationNode() {
    
    //printf("Dealloc[LevelWaveSpawnFormationNode:%X] Obj[%d]\n", this, mObject);
    
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
}

void LevelWaveSpawnFormationNode::Spawn() {
    
    mObject = new Balloon();
    
    //TODO: Remove
    ((Balloon *)mObject)->mSprite = &(gApp->mBalloonMap[1]);
    
    mObject->mTransform.mX = mBaseX;
    mObject->mTransform.mY = mBaseY;
    
    PositionObject();
    gGame->mBalloonList.Add(mObject);
}

void LevelWaveSpawnFormationNode::Reset() {
    
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
}

void LevelWaveSpawnFormationNode::Restart() {
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    mKillTimer = 8;
}

void LevelWaveSpawnFormationNode::Update() {
    PositionObject();
}

void LevelWaveSpawnFormationNode::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.25f, 0.65f, 0.85f, 0.85f);
    Graphics::DrawPoint(mX, mY, 4.0f);
    
    Graphics::SetColor();
}

void LevelWaveSpawnFormationNode::PositionObject() {
    
    
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
    
    if (mObject != NULL) {
        mObject->mTransform.mX = mX;
        mObject->mTransform.mY = mY;
    }
}

void LevelWaveSpawnFormationNode::DisposeObject(GameObject *pObject) {
    
}


LevelWaveSpawnFormationNode *LevelWaveSpawnFormationNode::Clone(LevelWaveSpawnFormation *pFormation) {
    
    LevelWaveSpawnFormationNode *aClone = new LevelWaveSpawnFormationNode(pFormation);
    
    aClone->mBaseX = mBaseX;
    aClone->mBaseY = mBaseY;
    
    return aClone;
}











