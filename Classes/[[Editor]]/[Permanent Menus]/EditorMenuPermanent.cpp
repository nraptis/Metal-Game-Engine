//
//  EditorMenuPermanent.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPermanent.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuPermanent.hpp"
#include "GamePermanentEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuPermanent::EditorMenuPermanent(GamePermanentEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPermanent";
    
    mEditor = pEditor;
    
    SetTitle("Permanent Editor");
    
    //TODO: set TRUE
    SetScrollMode(false);
    
    
    mPanelEditor = new ToolMenuPanel();
    mPanelEditor->SetTitle("Edit Paths");
    AddSection(mPanelEditor);
    
    mSegmentMode = new UISegment();
    mSegmentMode->SetSegmentCount(3);
    mSegmentMode->SetTitles("Add Perm", "Move Perm", "Select Perm");
    mSegmentMode->SetTarget(&mEditor->mPermMode);
    mPanelEditor->AddSection(mSegmentMode);
    
    
    mSnapsPanel = new ToolMenuPanel();
    mSnapsPanel->SetTitle("Snapping Constraint");
    AddSection(mSnapsPanel);
    
    mRowSnaps1 = new ToolMenuSectionRow();
    mSnapsPanel->AddSection(mRowSnaps1);
    
    
    mCheckBoxPermSnapsEnabled = new UICheckBox();
    mCheckBoxPermSnapsEnabled->SetText("Snaps");
    if (mEditor) {
        mCheckBoxPermSnapsEnabled->SetTarget(&(mEditor->mSnapsEnabled));
    }
    mRowSnaps1->AddCheckBox(mCheckBoxPermSnapsEnabled);
    
    
    mButtonSnapsBreakX = new UIButton();
    mButtonSnapsBreakX->SetText("Break-X");
    mRowSnaps1->AddButton(mButtonSnapsBreakX);
    
    mButtonSnapsBreakY = new UIButton();
    mButtonSnapsBreakY->SetText("Break-X");
    mRowSnaps1->AddButton(mButtonSnapsBreakY);
    
    
    mPermPanel = new ToolMenuPanel();
    mPermPanel->SetTitle("Perm Picker");
    AddSection(mPermPanel);
    
    mRowPermanent1 = new ToolMenuSectionRow();
    mPermPanel->AddSection(mRowPermanent1);
    
    
    mButtonAddPermanent = new UIButton();
    mButtonAddPermanent->SetText("Add Perm");
    mRowPermanent1->AddButton(mButtonAddPermanent);
    
    mButtonDeletePermanent = new UIButton();
    mButtonDeletePermanent->SetText("Delete Perm");
    mRowPermanent1->AddButton(mButtonDeletePermanent);
    
    
    mButtonEditPermanentPaths = new UIButton();
    mButtonEditPermanentPaths->SetText("Edit Paths");
    mRowPermanent1->AddButton(mButtonEditPermanentPaths);
    
    
    
    
    
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
    
    mTimingPanelPanel = new ToolMenuPanel();
    mTimingPanelPanel->SetTitle("Timing");
    AddSection(mTimingPanelPanel);
    
    mStepperCreationType = new UISegment();
    mStepperCreationType->SetSegmentCount(5);
    mStepperCreationType->SetTitles("PW-Sta", "PW-End", "PW-Clr", "Scr-C-P" "Scr-C+P");
    mTimingPanelPanel->AddSection(mStepperCreationType);
    
    mStepperCreationDelay = new UIStepper();
    mStepperCreationDelay->SetText("Delay");
    mStepperCreationDelay->mMin = 0;
    mStepperCreationDelay->mMax = 2048;
    mTimingPanelPanel->AddSection(mStepperCreationDelay);
}

EditorMenuPermanent::~EditorMenuPermanent() {
    if (mEditor != NULL) {
    if (mEditor->mMenuPerm == this) {
        mEditor->mMenuPerm = NULL;
    }
    }
}

void EditorMenuPermanent::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuPermanent::Notify(void *pSender, const char *pNotification) {
    
    if (mEditor == NULL) { return; }
    if (gEditor == NULL) { return; }
    
    if (pSender == mButtonSnapsBreakX) { mEditor->BreakConstraintX(); }
    if (pSender == mButtonSnapsBreakY) { mEditor->BreakConstraintY(); }
    
    
    
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

void EditorMenuPermanent::Update() {
    
    
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
