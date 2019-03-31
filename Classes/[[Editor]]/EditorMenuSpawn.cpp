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
    
    mGenerationPanel = new ToolMenuPanel();
    mGenerationPanel->SetTitle("Generation");
    AddSection(mGenerationPanel);
    
    mSegmentSpeed = new UISegment();
    mSegmentSpeed->SetSegmentCount(7);
    mSegmentSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    if (gGame) {
        mSegmentSpeed->SetTarget(&gEditor->mSpeedClassIndex);
    }
    mGenerationPanel->AddSection(mSegmentSpeed);
    
    
    mStepperSpawnCount = new UIStepper();
    mStepperSpawnCount->SetText("Count");
    mStepperSpawnCount->mMin = 1;
    mStepperSpawnCount->mMax = (MAX_SPAWN_COUNT);
    mGenerationPanel->AddSection(mStepperSpawnCount);
    
    mStepperSpacing = new UIStepper();
    mStepperSpacing->SetText("Spacing");
    mStepperSpacing->mMin = -1000;
    mStepperSpacing->mMax = 1000;
    mGenerationPanel->AddSection(mStepperSpacing);
    
    
    
    mTimingPanelPanel = new ToolMenuPanel();
    mTimingPanelPanel->SetTitle("Timing");
    AddSection(mTimingPanelPanel);
    
    
    mStepperCreationType = new UISegment();
    mStepperCreationType->SetSegmentCount(4);
    mStepperCreationType->SetTitles("P-W-Start", "P-W-End", "P-W-Clear", "Scr-Clear");
    mTimingPanelPanel->AddSection(mStepperCreationType);
    
    
    mStepperCreationDelay = new UIStepper();
    mStepperCreationDelay->SetText("Delay");
    mStepperCreationDelay->mMin = 0;
    mStepperCreationDelay->mMax = 2048;
    mTimingPanelPanel->AddSection(mStepperCreationDelay);
    
    
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
    
    if (gEditor == NULL) { return; }
    
    if (pSender == mSegmentSpeed) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperSpawnCount) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperSpacing) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperCreationType) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperCreationDelay) { gEditor->RefreshPlayback(); }
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
    
    
    if (mStepperCreationType != NULL) {
        bool aUnlink = true;
        if (aWave != NULL) {
            aUnlink = false;
            mStepperCreationType->SetTarget(&(aWave->mCreationType));
        }
        if (aUnlink) {
            mStepperCreationType->SetTarget(NULL);
        }
    }
    
    if (mStepperCreationDelay != NULL) {
        bool aUnlink = true;
        if (aWave != NULL) {
            aUnlink = false;
            mStepperCreationDelay->SetTarget(&(aWave->mCreationDelay));
        }
        if (aUnlink) {
            mStepperCreationDelay->SetTarget(NULL);
        }
    }
    \
    
}
