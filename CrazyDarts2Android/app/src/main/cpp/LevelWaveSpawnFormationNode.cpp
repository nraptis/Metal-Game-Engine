//
//  LevelWaveSpawnFormationNodeFormationNode.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//



#include "LevelWaveSpawnFormationNode.hpp"
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
    
    mKillTimer = 8;
}

LevelWaveSpawnFormationNode::~LevelWaveSpawnFormationNode() {
    
    printf("Dealloc[LevelWaveSpawnFormationNode:%X] Obj[%d]\n", this, mObject);
    
    if (mObject) {
        mObject->Kill();
        mObject = NULL;
    }
}

void LevelWaveSpawnFormationNode::Spawn() {
    mBaseX = 0.0f;
    mBaseY = 0.0f;

    
    
    if (mFormation != NULL) {
        
        
    }
    
    
    mObject = new Balloon();
    mObject->mTransform.mX = mBaseX;
    mObject->mTransform.mY = mBaseY;
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
    
    if (mObject != NULL) {
        mObject->mTransform.mX = mBaseX;
        mObject->mTransform.mY = mBaseY;
    }
}

void LevelWaveSpawnFormationNode::Draw() {
    

    
}


void LevelWaveSpawnFormationNode::DisposeObject(GameObject *pObject) {
    
}











