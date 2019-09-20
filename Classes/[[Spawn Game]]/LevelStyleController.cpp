//
//  LevelStyleController.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelStyleController.hpp"

LevelStyleController::LevelStyleController() {
    
    Reset();
    
}

LevelStyleController::~LevelStyleController() {
    
}

void LevelStyleController::Reset() {
    mDisableThreads = false;
    mEnableBobbleMode = false;
    mRandomizeSpin = false;
}

