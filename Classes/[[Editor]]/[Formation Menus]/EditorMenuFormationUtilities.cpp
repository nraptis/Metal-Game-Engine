//
//  EditorMenuFormationUtilities.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormationUtilities.hpp"
#include "GameFormationEditor.hpp"
#include "LevelFormationTracerBlueprint.hpp"
#include "LevelFormationTracer.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuFormationUtilities::EditorMenuFormationUtilities(GameFormationEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuFormationUtilities";
    
    mEditor = pEditor;
    
    
    SetTitle("Formation Utils");
    SetScrollMode(true);
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    
    mButtonResetFormation = new UIButton();
    mButtonResetFormation->SetText("Reset");
    mRowMain1->AddButton(mButtonResetFormation);
    
    mButtonCloseEditor = new UIButton();
    mButtonCloseEditor->SetText("Close Editor");
    mRowMain1->AddButton(mButtonCloseEditor);
    mPanelTracers = new ToolMenuPanel();
    mPanelTracers->SetTitle("Tracer Mode");
    AddSection(mPanelTracers);
    
    
    
    mRowTracers1 = new ToolMenuSectionRow();
    mPanelTracers->AddSection(mRowTracers1);
    
    
    mCheckBoxTracersEnabled = new UICheckBox();
    mCheckBoxTracersEnabled->SetText("Tracers Enabled");
    mCheckBoxTracersEnabled->SetTarget(&mEditor->mTracerEnabled);
    mRowTracers1->AddCheckBox(mCheckBoxTracersEnabled);
    
    mButtonDeleteTracer = new UIButton();
    mButtonDeleteTracer->SetText("Delete Tracer");
    mRowTracers1->AddButton(mButtonDeleteTracer);
    
    mSegmentTracersMode = new UISegment();
    mSegmentTracersMode->SetSegmentCount(3);
    mSegmentTracersMode->SetTitles("Add Point", "Move Point", "Select Point");
    mSegmentTracersMode->SetTarget(&mEditor->mTracerMode);
    mPanelTracers->AddSection(mSegmentTracersMode);
    
    mSegmentCurrentTracer = new UISegment();
    mSegmentCurrentTracer->SetSegmentCount(6);
    mSegmentCurrentTracer->SetTitles("Trace 1", "Trace 2", "Trace 3", "Trace 4", "Trace 5", "Trace 6");
    mSegmentCurrentTracer->SetTarget(&mEditor->mFormation.mCurrentTracerIndex);
    mPanelTracers->AddSection(mSegmentCurrentTracer);
    
    
    
    mPanelTracerTweaks = new ToolMenuPanel();
    mPanelTracerTweaks->SetTitle("Tracer Tweaks");
    AddSection(mPanelTracerTweaks);
    
    
    mStepperTracerSpawnCount = new UIStepper();
    mStepperTracerSpawnCount->SetText("Spawn Count: ");
    mPanelTracerTweaks->AddSection(mStepperTracerSpawnCount);
    
    mPanelTracerSpecial = new ToolMenuPanel();
    mPanelTracerSpecial->SetTitle("Tracer Special");
    AddSection(mPanelTracerSpecial);
    
    
    //mStepperTracerSpawnCount = new UIStepper();
    //mStepperTracerSpawnCount->SetText("Spawn Count: ");
    //mPanelTracerSpecial->AddSection(mStepperTracerSpawnCount);
    
    
    
    mSegmentTracerSpecialType = new UISegment();
    mSegmentTracerSpecialType->SetSegmentCount(3);
    mSegmentTracerSpecialType->SetTitles("None", "Circle", "Round");
    mPanelTracerSpecial->AddSection(mSegmentTracerSpecialType);
    
    mStepperTracerSpecialRadius = new UIStepper();
    mStepperTracerSpecialRadius->SetText("Size: ");
    mPanelTracerSpecial->AddSection(mStepperTracerSpecialRadius);
    
    mStepperTracerSpecialCornerRadius = new UIStepper();
    mStepperTracerSpecialCornerRadius->SetText("Corner: ");
    mPanelTracerSpecial->AddSection(mStepperTracerSpecialCornerRadius);
    
    
    /*
    mSegmentGridType = new UISegment();
    mSegmentGridType->SetSegmentCount(6);
    mSegmentGridType->SetTitles("RECT", "CIRC", "STAR", "TRI", "ROUND", "NGON1");
    mSegmentGridType->SetTarget(&mEditor->mGridType);
    mPanelGrid->AddSection(mSegmentGridType);
    */
    
    
    
    DeactivateCloseButton();
}

EditorMenuFormationUtilities::~EditorMenuFormationUtilities() {
    
}

void EditorMenuFormationUtilities::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuFormationUtilities::Notify(void *pSender, const char *pNotification) {
    
    if (mEditor == NULL) { return; }
    
    if (pSender == mButtonCloseEditor) { mEditor->Close(); }
    
    if (pSender == mButtonResetFormation) { mEditor->Clear(); }
    
    if (pSender == mStepperTracerSpawnCount) { mEditor->Refresh(); }
    if (pSender == mButtonDeleteTracer) { mEditor->DeleteTracer(); }
    
    
    if (pSender == mSegmentTracerSpecialType) {
        //mEditor->Update();
        mEditor->Refresh();
    }
    if (pSender == mStepperTracerSpecialRadius) { mEditor->Refresh(); }
    if (pSender == mStepperTracerSpecialCornerRadius) { mEditor->Refresh(); }
    
}

void EditorMenuFormationUtilities::Update() {
    
    if (mEditor == NULL) { return; }
    if (gEditor == NULL) { return; }
    
    LevelFormationTracerBlueprint *aTracer = NULL;
    aTracer = mEditor->mFormation.GetTracer();
    
    //NOTE: DO NOT SET SPEED CLASS HERE...
    //mTracerSpeedClassIndex = NO NO NO NO NO
    
    if (mStepperTracerSpawnCount) {
        bool aUnlink = true;
        if (aTracer != NULL) {
            aUnlink = false;
            mStepperTracerSpawnCount->SetTarget(&(aTracer->mCount));
        }
        if (aUnlink) {
            mStepperTracerSpawnCount->SetTarget(NULL);
        }
    }
    
    /*
    if (mSegmentTracersSpeed) {
        bool aUnlink = true;
        if (aTracer != NULL) {
            aUnlink = false;
            mSegmentTracersSpeed->SetTarget(&(aTracer->mSpeedClass));
        }
        if (aUnlink) {
            mSegmentTracersSpeed->SetTarget(NULL);
        }
    }
    */

    
    if (mSegmentTracerSpecialType) {
        bool aUnlink = true;
        if (aTracer != NULL) {
            aUnlink = false;
            mSegmentTracerSpecialType->SetTarget(&(aTracer->mSpecialType));
        }
        if (aUnlink) {
            mSegmentTracerSpecialType->SetTarget(NULL);
        }
    }
    

    if (mStepperTracerSpecialRadius) {
        bool aUnlink = true;
        if (aTracer != NULL) {
            aUnlink = false;
            mStepperTracerSpecialRadius->SetTarget(&(aTracer->mSpecialRadius));
        }
        if (aUnlink) {
            mStepperTracerSpecialRadius->SetTarget(NULL);
        }
    }
    
    
    if (mStepperTracerSpecialCornerRadius) {
        bool aUnlink = true;
        if (aTracer != NULL) {
            aUnlink = false;
            mStepperTracerSpecialCornerRadius->SetTarget(&(aTracer->mSpecialCornerRadius));
        }
        if (aUnlink) {
            mStepperTracerSpecialCornerRadius->SetTarget(NULL);
        }
    }
}
