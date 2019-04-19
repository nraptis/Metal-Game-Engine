//
//  EditorMenuPermanentUtils.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPermanentUtils.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuPermanentUtils.hpp"
#include "GamePermanentEditor.hpp"
#include "FApp.hpp"

EditorMenuPermanentUtils::EditorMenuPermanentUtils(GamePermanentEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPermanentUtils";
    
    mEditor = pEditor;
    
    SetTitle("Permanent Utils");
    
    //TODO: set TRUE
    SetScrollMode(false);
    
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonCloseEditor = new UIButton();
    mButtonCloseEditor->SetText("Close Editor");
    mRowMain1->AddButton(mButtonCloseEditor);
    
    
    mButtonResetPerm = new UIButton();
    mButtonResetPerm->SetText("Reset Path");
    mRowMain1->AddButton(mButtonResetPerm);
    
    mGenerationPanel = new ToolMenuPanel();
    mGenerationPanel->SetTitle("Generation");
    AddSection(mGenerationPanel);
    
    mSegmentSpeed = new UISegment();
    mSegmentSpeed->SetSegmentCount(7);
    mSegmentSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    mGenerationPanel->AddSection(mSegmentSpeed);
    
    
    mStepperSpawnCount = new UIStepper();
    mStepperSpawnCount->SetText("Count");
    mStepperSpawnCount->mMin = 1;
    mGenerationPanel->AddSection(mStepperSpawnCount);
    
    mStepperSpacing = new UIStepper();
    mStepperSpacing->SetText("Spacing");
    mStepperSpacing->mMin = -1000;
    mStepperSpacing->mMax = 1000;
    mGenerationPanel->AddSection(mStepperSpacing);
    
    
    
    mTimingPanel = new ToolMenuPanel();
    mTimingPanel->SetTitle("Timing");
    AddSection(mTimingPanel);
    
    
    mStepperCreationType = new UISegment();
    mStepperCreationType->SetSegmentCount(4);
    mStepperCreationType->SetTitles("P-W-Start", "P-W-End", "P-W-Clear", "Scr-Clear");
    mTimingPanel->AddSection(mStepperCreationType);
    
    
    mStepperCreationDelay = new UIStepper();
    mStepperCreationDelay->SetText("Delay");
    mStepperCreationDelay->mMin = 0;
    mStepperCreationDelay->mMax = 2048;
    mTimingPanel->AddSection(mStepperCreationDelay);
    
    
}

EditorMenuPermanentUtils::~EditorMenuPermanentUtils() {
    if (mEditor != NULL) {
    if (mEditor->mMenuUtils == this) {
        mEditor->mMenuUtils = NULL;
    }
    }
}

void EditorMenuPermanentUtils::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuPermanentUtils::Notify(void *pSender, const char *pNotification) {
    
    if (mEditor == NULL) { return; }
    
    if (pSender == mButtonCloseEditor) { mEditor->Close(); }
    if (pSender == mButtonResetPerm) { mEditor->ResetSelected(); }
    
    /*
    if (pSender == mSegmentSpeed) {
        gEditor->RefreshPlaybackSpeed();
        gEditor->RefreshPlayback();
    }
    if (pSender == mStepperSpawnCount) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperSpacing) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperCreationType) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperCreationDelay) { gEditor->RefreshPlayback(); }
    */
    
}

void EditorMenuPermanentUtils::Update() {
    
    /*
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
    
    */
    
}
