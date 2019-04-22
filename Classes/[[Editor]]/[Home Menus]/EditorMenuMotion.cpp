//
//  EditorMenuMotion.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuMotion.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuMotion.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuMotion::EditorMenuMotion(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuMotion";
    
    mEditor = pEditor;
    
    SetTitle("Spawn (Meta)");
    
    SetScrollMode(false);
    
    
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
    mStepperSpawnCount->mMax = (WAVE_MAX_SPAWN_COUNT);
    mGenerationPanel->AddSection(mStepperSpawnCount);
    
    mStepperSpacing = new UIStepper();
    mStepperSpacing->SetText("Spacing");
    mStepperSpacing->mMin = -1000;
    mStepperSpacing->mMax = 1000;
    mGenerationPanel->AddSection(mStepperSpacing);
    
    
    
    mTimingPanel = new ToolMenuPanel();
    mTimingPanel->SetTitle("Timing");
    AddSection(mTimingPanel);
    
    
    
    
    
    
    //mStepperCreationType = new UISegment();
    //mStepperCreationType->SetSegmentCount(4);
    //mStepperCreationType->SetTitles("P-W-Sta", "P-W-End", "P-W-Clr", "S-Clr-NoP", "S-Cle-AndP");
    //mTimingPanel->AddSection(mStepperCreationType);
    
    
    
    mStepperCreationDelay = new UIStepper();
    mStepperCreationDelay->SetText("Delay");
    mStepperCreationDelay->mMin = 0;
    mStepperCreationDelay->mMax = 2048;
    mTimingPanel->AddSection(mStepperCreationDelay);
    
    
    mTimingRow1 = new ToolMenuSectionRow();
    mTimingPanel->AddSection(mTimingRow1);
    
    mCheckBoxCreationRequiresPrevWaveStart = new UICheckBox();
    mCheckBoxCreationRequiresPrevWaveStart->SetText("P-W-Start");
    mTimingRow1->AddCheckBox(mCheckBoxCreationRequiresPrevWaveStart);
    
    mCheckBoxCreationRequiresPrevWaveComplete = new UICheckBox();
    mCheckBoxCreationRequiresPrevWaveComplete->SetText("P-W-Compl");
    mTimingRow1->AddCheckBox(mCheckBoxCreationRequiresPrevWaveComplete);
    
    
    mTimingRow2 = new ToolMenuSectionRow();
    mTimingPanel->AddSection(mTimingRow2);
    
    mCheckBoxCreationRequiresScreenWavesClear = new UICheckBox();
    mCheckBoxCreationRequiresScreenWavesClear->SetText("Scr-Wav-Clr");
    mTimingRow2->AddCheckBox(mCheckBoxCreationRequiresScreenWavesClear);
    
    mCheckBoxCreationRequiresScreenPermsClear = new UICheckBox();
    mCheckBoxCreationRequiresScreenPermsClear->SetText("Scr-Prm-Clr");
    mTimingRow2->AddCheckBox(mCheckBoxCreationRequiresScreenPermsClear);
    
    
    
    
    
    
}

EditorMenuMotion::~EditorMenuMotion() {
    if (gEditor->mMenuMotion == this) {
        gEditor->mMenuMotion = NULL;
    }
}

void EditorMenuMotion::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuMotion::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }
    if (pSender == mSegmentSpeed) {
        gEditor->RefreshPlaybackSpeed();
        gEditor->RefreshPlayback();
    }
    if (pSender == mStepperSpawnCount) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperSpacing) { gEditor->RefreshPlayback(); }
    
    if (pSender == mStepperCreationDelay) { gEditor->RefreshPlayback(); }
    
    if (pSender == mCheckBoxCreationRequiresPrevWaveStart) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxCreationRequiresPrevWaveComplete) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxCreationRequiresScreenWavesClear) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxCreationRequiresScreenPermsClear) { gEditor->RefreshPlayback(); }
    
}

void EditorMenuMotion::Update() {
    
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
    
    
    
    if (mCheckBoxCreationRequiresPrevWaveStart != NULL) {
        bool aUnlink = true;
        if (aWave != NULL) {
            aUnlink = false;
            mCheckBoxCreationRequiresPrevWaveStart->SetTarget(&(aWave->mCreationRequiresPrevWaveStart));
        }
        if (aUnlink) {
            mCheckBoxCreationRequiresPrevWaveStart->SetTarget(NULL);
        }
    }
    
    
    if (mCheckBoxCreationRequiresPrevWaveComplete != NULL) {
        bool aUnlink = true;
        if (aWave != NULL) {
            aUnlink = false;
            mCheckBoxCreationRequiresPrevWaveComplete->SetTarget(&(aWave->mCreationRequiresPrevWaveComplete));
        }
        if (aUnlink) {
            mCheckBoxCreationRequiresPrevWaveComplete->SetTarget(NULL);
        }
    }
    
    if (mCheckBoxCreationRequiresScreenWavesClear != NULL) {
        bool aUnlink = true;
        if (aWave != NULL) {
            aUnlink = false;
            mCheckBoxCreationRequiresScreenWavesClear->SetTarget(&(aWave->mCreationRequiresScreenWavesClear));
        }
        if (aUnlink) {
            mCheckBoxCreationRequiresScreenWavesClear->SetTarget(NULL);
        }
    }
    
    if (mCheckBoxCreationRequiresScreenPermsClear != NULL) {
        bool aUnlink = true;
        if (aWave != NULL) {
            aUnlink = false;
            mCheckBoxCreationRequiresScreenPermsClear->SetTarget(&(aWave->mCreationRequiresScreenPermsClear));
        }
        if (aUnlink) {
            mCheckBoxCreationRequiresScreenPermsClear->SetTarget(NULL);
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
}
