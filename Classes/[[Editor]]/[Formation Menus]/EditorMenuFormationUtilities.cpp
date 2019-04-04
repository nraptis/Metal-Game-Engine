//
//  EditorMenuFormationUtilities.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormationUtilities.hpp"
#include "GameFormationEditor.hpp"
#include "LevelWaveSpawnFormationTracerBlueprint.hpp"
#include "LevelWaveSpawnFormationTracer.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuFormationUtilities::EditorMenuFormationUtilities(GameFormationEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuFormationUtilities";
    
    mEditor = pEditor;
    
    
    SetTitle("Formation Utils");
    SetScrollMode(true);
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonCloseEditor = new UIButton();
    mButtonCloseEditor->SetText("Close Editor");
    mRowMain1->AddButton(mButtonCloseEditor);
    
    
    mButtonResetFormation = new UIButton();
    mButtonResetFormation->SetText("Reset");
    mRowMain1->AddButton(mButtonResetFormation);
    
    
    
    
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
    
    
    mSegmentTracersSpeed = new UISegment();
    mSegmentTracersSpeed->SetSegmentCount(7);
    mSegmentTracersSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    mSegmentTracersSpeed->SetTarget(&(mEditor->mTracerSpeedClassIndex));
    mPanelTracerTweaks->AddSection(mSegmentTracersSpeed);

    
    
    mStepperTestIndex = new UIStepper();
    mStepperTestIndex->SetText("Test Step: ");
    mPanelTracerTweaks->AddSection(mStepperTestIndex);
    
    
    
    
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
    
    
    if (pSender == mSegmentTracersSpeed) {
        mEditor->RefreshTracerSpeed();
        mEditor->Refresh();
    }
    
    if (pSender == mStepperTracerSpawnCount) { mEditor->Refresh(); }
    if (pSender == mButtonDeleteTracer) { mEditor->DeleteTracer(); }
    
}

void EditorMenuFormationUtilities::Update() {
    
    if (mEditor == NULL) { return; }
    if (gEditor == NULL) { return; }
    
    LevelWaveSpawnFormationTracerBlueprint *aTracer = NULL;
    aTracer = mEditor->mFormation.GetTracer();
    
    
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
    
    if (mStepperTestIndex) {
        bool aUnlink = true;
        
        LevelWaveSpawnFormationTracer *TT = NULL;
        
        int aIndex = 0;
        EnumList(LevelWaveSpawnFormationTracer, AAA, mEditor->mEditorFormation.mTracerList) {
            if (aIndex == mEditor->mFormation.mCurrentTracerIndex) {
                TT = AAA;
            }
        }
        
        
        if (TT != NULL) {
            aUnlink = false;
            mStepperTestIndex->SetTarget(&(TT->mPathIndex));
        }
        if (aUnlink) {
            mStepperTestIndex->SetTarget(NULL);
        }
    }
    

}
