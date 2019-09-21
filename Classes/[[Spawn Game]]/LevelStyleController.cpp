//
//  LevelStyleController.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelStyleController.hpp"
#include "Balloon.hpp"
#include "FreeLife.hpp"

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

void LevelStyleController::ApplyToObject(GameObject *pObject) {
    
    if (pObject == NULL) { return; }
    
    if (mDisableThreads) {
        if (pObject->mGameObjectType == GAME_OBJECT_TYPE_BALLOON) {
            Balloon *aBalloon = ((Balloon *)pObject);
            aBalloon->RemoveThread();
        }
        
        if (pObject->mGameObjectType == GAME_OBJECT_TYPE_FREE_LIFE) {
            FreeLife *aFreeLife = ((FreeLife *)pObject);
            aFreeLife->RemoveThread();
        }
        
    }
}

void LevelStyleController::ApplyToObjectList(FList *pList) {
    
    if (pList == NULL) { return; }
    
    EnumList(GameObject, aObject, *pList) {
        ApplyToObject(aObject);
    }
    
}
