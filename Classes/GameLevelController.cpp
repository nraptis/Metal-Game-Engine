//
//  GameLevelController.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameLevelController.hpp"
#include "Game.hpp"


GameLevelController::GameLevelController(Game *pGame) {
    mGame = pGame;
    mData = NULL;
}

GameLevelController::~GameLevelController() {
    
}

void GameLevelController::Setup(LevelData *pData) {
    mData = pData;
    
}


void GameLevelController::Update() {
    
    if (mData != NULL) {
        mData->Update();
        
    }
    
}

void GameLevelController::DrawMarkers() {
    
}
