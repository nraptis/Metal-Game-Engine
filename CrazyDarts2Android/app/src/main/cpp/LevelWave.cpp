//
//  LevelWave.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWave.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"

LevelWave::LevelWave() {
    mAliveTimer = 0;
    mIsComplete = false;
    mRight = true;
}

LevelWave::~LevelWave() {
    
}

void LevelWave::Spawn() {
    Log("LevelWave::Spawn()");
    
    Balloon *aBalloon = new Balloon();
    if (mRight) {
        aBalloon->mTransform.mX = gGame->mWidth;
        aBalloon->mTransform.mY = gGame->mHeight * 0.33f;
        
        aBalloon->mVelX = -2.0f;
        aBalloon->mVelY = 0.01f;
    } else {
        aBalloon->mTransform.mX = 0.0f;
        aBalloon->mTransform.mY = gGame->mHeight * 0.33f;
        
        aBalloon->mVelX = 2.0f;
        aBalloon->mVelY = 0.01f;
    }
    
    gGame->mBalloonList.Add(aBalloon);
    
}

void LevelWave::Update() {
    mAliveTimer += 1;
    if (mAliveTimer >= 500) {
        mIsComplete = true;
    }
}

void LevelWave::Draw() {
    
}

void LevelWave::Dispose() {
    
}

void LevelWave::DisposeObject(GameObject *pObject) {
    
}
