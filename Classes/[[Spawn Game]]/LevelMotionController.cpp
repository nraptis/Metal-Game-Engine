//
//  LevelMotionController.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelMotionController.hpp"

//
//  LevelMotionController.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelMotionController.hpp"
#include "LevelSection.hpp"
#include "Game.hpp"
#include "Balloon.hpp"

LevelMotionController::LevelMotionController() {
    
    mPlayOnEnter = true;
    mPlayOnExit = true;
    
    mSkipUpdate = false;
    
    mKillTimer = 8;
}

LevelMotionController::~LevelMotionController() {
    FreeList(LevelMotionControllerSlice, mSliceList);
    FreeList(LevelMotionControllerSlice, mKillList);
}

void LevelMotionController::Reset() {
    EnumList(LevelMotionControllerSlice, aSlice, mSliceList) {
        mKillList.Add(aSlice);
    }
    mSliceList.RemoveAll();
}

void LevelMotionController::Update() {
    
    if (mSkipUpdate == false) {
        EnumList(LevelMotionControllerSlice, aSlice, mSliceList) {
            aSlice->Update();
        }
    }
    
    EnumList(LevelMotionControllerSlice, aSlice, mKillList) {
        aSlice->mKillTimer--;
        if (aSlice->mKillTimer <= 0) { mDeleteList.Add(aSlice); }
    }
    EnumList(LevelMotionControllerSlice, aSlice, mDeleteList) {
        mKillList.Remove(aSlice);
        delete aSlice;
    }
    mDeleteList.RemoveAll();
}

void LevelMotionController::Draw() {
    
}

void LevelMotionController::Apply(float pReferenceX, float pReferenceY, float *pX, float *pY) {
    
}

void LevelMotionController::Apply(float pReferenceX, float pReferenceY, GameObject *pObject) {
    if (pObject != NULL) {
        EnumList(LevelMotionControllerSlice, aSlice, mSliceList) {
            aSlice->Apply(pReferenceX, pReferenceY, &pObject->mTransform.mX, &pObject->mTransform.mY);
        }
    }
}



