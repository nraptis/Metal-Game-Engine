//
//  EditorMenuSpawn.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuSpawn.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuSpawn.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuSpawn::EditorMenuSpawn(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuSpawn";
    
    mEditor = pEditor;
    
    SetTitle("Spawn (Meta)");
    SetScrollMode(true);
    
    mSegmentSpeed = new UISegment();
    mSegmentSpeed->SetSegmentCount(7);
    mSegmentSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    if (gGame) {
        mSegmentSpeed->SetTarget(&gEditor->mSpeedClassIndex);
    }
    AddSection(mSegmentSpeed);
    gNotify.Register(this, mSegmentSpeed, "segment");
    
    
    mStepperSpawnCount = new UIStepper();
    mStepperSpawnCount->SetText("Count");
    mStepperSpawnCount->mMin = 1;
    mStepperSpawnCount->mMax = (MAX_SPAWN_COUNT);
    gNotify.Register(this, mStepperSpawnCount, "stepper");
    AddSection(mStepperSpawnCount);
    
    mStepperSpacing = new UIStepper();
    mStepperSpacing->SetText("Spacing");
    mStepperSpacing->mMin = -1000;
    mStepperSpacing->mMax = 1000;
    gNotify.Register(this, mStepperSpacing, "stepper");
    AddSection(mStepperSpacing);
}

EditorMenuSpawn::~EditorMenuSpawn() {
    if (gEditor->mMenuSpawn == this) {
        gEditor->mMenuSpawn = NULL;
    }
}

void EditorMenuSpawn::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuSpawn::Notify(void *pSender, const char *pNotification) {
    if (pSender == mSegmentSpeed) {
        if (gEditor) { gEditor->RefreshWave(); }
    }
    if (pSender == mStepperSpawnCount) {
        if (gEditor) { gEditor->RefreshWave(); }
    }
    if (pSender == mStepperSpacing) {
        if (gEditor) { gEditor->RefreshWave(); }
    }
}

void EditorMenuSpawn::Update() {
    
    LevelWaveBlueprint *aWave = NULL;
    if (gEditor) {
        aWave = gEditor->mSection.mCurrentWave;
    }
    
    
    if (mStepperSpawnCount != NULL) {
        bool aUnlink = true;
        if (aWave != NULL) {
            aUnlink = false;
            mStepperSpawnCount->SetTarget(&(aWave->mSpawnCount));
        }
        if (aUnlink) {
            mStepperSpawnCount->SetTarget(NULL);
        }
    }
    
    if (mStepperSpacing != NULL) {
        bool aUnlink = true;
        if (aWave != NULL) {
            aUnlink = false;
            mStepperSpacing->SetTarget(&(aWave->mSpawnSpacing));
        }
        if (aUnlink) {
            mStepperSpacing->SetTarget(NULL);
        }
    }
    
}
