//
//  EditorMenuPanelFormationConfiguration.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPanelFormationConfiguration.hpp"
#include "GameEditor.hpp"

EditorMenuPanelFormationConfiguration::EditorMenuPanelFormationConfiguration() {
    mName = "formation_config_panel";
    
    
    SetTitle("Formation Configuration");
    //mRowMain1 = new ToolMenuSectionRow();
    //AddSection(mRowMain1);
    
    mTracerSpeedIndexGlobal = 0;
    
    mTracerSpeedIndex1 = 0;
    mTracerSpeedIndex2 = 0;
    mTracerSpeedIndex3 = 0;
    
    mSegmentTracerSpeedGlobal = new UISegment();
    mSegmentTracerSpeedGlobal->SetSegmentCount(8);
    mSegmentTracerSpeedGlobal->SetTitles("--", "XS", "S", "MS", "M", "MF", "F", "XF");
    gNotify.Register(this, mSegmentTracerSpeedGlobal, "segment");
    AddSection(mSegmentTracerSpeedGlobal);
    
    mPanelTracerSpeed = new ToolMenuPanel();
    mPanelTracerSpeed->SetTitle("Per Tracer");
    AddSection(mPanelTracerSpeed);
    
    mSegmentTracerSpeed1 = new UISegment();
    mSegmentTracerSpeed1->SetSegmentCount(8);
    mSegmentTracerSpeed1->SetTitles("--", "XS", "S", "MS", "M", "MF", "F", "XF");
    gNotify.Register(this, mSegmentTracerSpeed1, "segment");
    mPanelTracerSpeed->AddSection(mSegmentTracerSpeed1);
    
    
    mSegmentTracerSpeed2 = new UISegment();
    mSegmentTracerSpeed2->SetSegmentCount(8);
    mSegmentTracerSpeed2->SetTitles("--", "XS", "S", "MS", "M", "MF", "F", "XF");
    gNotify.Register(this, mSegmentTracerSpeed2, "segment");
    mPanelTracerSpeed->AddSection(mSegmentTracerSpeed2);
    
    
    mSegmentTracerSpeed3 = new UISegment();
    mSegmentTracerSpeed3->SetSegmentCount(8);
    mSegmentTracerSpeed3->SetTitles("--", "XS", "S", "MS", "M", "MF", "F", "XF");
    gNotify.Register(this, mSegmentTracerSpeed3, "segment");
    mPanelTracerSpeed->AddSection(mSegmentTracerSpeed3);
    
}

EditorMenuPanelFormationConfiguration::~EditorMenuPanelFormationConfiguration() {
    
    
}

void EditorMenuPanelFormationConfiguration::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }
    LevelFormationConfigurationBlueprint *aConfig = gEditor->FormationConfigurationGet();
    
    if (aConfig == NULL) { return; }
    
    if (pSender == mSegmentTracerSpeedGlobal) {
        aConfig->mTracerSpeedGlobal = gEditor->SpeedConvertSegmentToType(mSegmentTracerSpeedGlobal->mSelectedIndex);
        gEditor->RefreshPlayback();
    }
    
    
    if (pSender == mSegmentTracerSpeed1) {
        aConfig->mTracerSpeed1 = gEditor->SpeedConvertSegmentToType(mSegmentTracerSpeed1->mSelectedIndex);
        gEditor->RefreshPlayback();
    }
    
    if (pSender == mSegmentTracerSpeed2) {
        aConfig->mTracerSpeed2 = gEditor->SpeedConvertSegmentToType(mSegmentTracerSpeed2->mSelectedIndex);
        gEditor->RefreshPlayback();
    }
    
    if (pSender == mSegmentTracerSpeed3) {
        aConfig->mTracerSpeed3 = gEditor->SpeedConvertSegmentToType(mSegmentTracerSpeed3->mSelectedIndex);
        gEditor->RefreshPlayback();
    }
    
    
    
    //if (pSender == mSegmentTracerSpeed1) { gEditor->RefreshPlayback(); }
    
    
    
    
    
    
    /*
    
    if (pSender == mButtonCloseEditor) { mEditor->Close(); }
    if (pSender == mButtonResetPerm) { mEditor->ResetSelected(); }
    
    
    if (pSender == mButtonMenuSpawnPicker) { mEditor->OpenMenuSpawnPicker(); }
    if (pSender == mButtonMenuPermPicker) { mEditor->OpenMenuPermPicker(); }
    if (pSender == mButtonMenuAttachment) { mEditor->OpenMenuAttachment(); }
    
    if (pSender == mButtonMenuMotionPerm) { mEditor->OpenMenuMotionForPerm(); }
    if (pSender == mButtonMenuMotionSpawn) { mEditor->OpenMenuMotionForSpawn(); }
    
    if (pSender == mStepperPathSpawnCount) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxPathSpawnEqualSpacing) { gEditor->RefreshPlayback(); }
    
    */
    
}

void EditorMenuPanelFormationConfiguration::Update() {
    
    
    //
    LevelFormationConfigurationBlueprint *aConfig = gEditor->FormationConfigurationGet();
    
    if (aConfig != NULL) {
        
        mTracerSpeedIndexGlobal = gEditor->SpeedConvertTypeToSegment(aConfig->mTracerSpeedGlobal);
        
        
        mTracerSpeedIndex1 = gEditor->SpeedConvertTypeToSegment(aConfig->mTracerSpeed1);
        mTracerSpeedIndex2 = gEditor->SpeedConvertTypeToSegment(aConfig->mTracerSpeed2);
        mTracerSpeedIndex3 = gEditor->SpeedConvertTypeToSegment(aConfig->mTracerSpeed3);
        
        
        
        
        
        
        
    }
    
    
    
    if (mSegmentTracerSpeedGlobal != NULL) {
        mSegmentTracerSpeedGlobal->SetTarget(&mTracerSpeedIndexGlobal);
    }
    
    if (mSegmentTracerSpeed1 != NULL) {
        mSegmentTracerSpeed1->SetTarget(&mTracerSpeedIndex1);
    }
    
    if (mSegmentTracerSpeed2 != NULL) {
        mSegmentTracerSpeed2->SetTarget(&mTracerSpeedIndex2);
    }
    
    if (mSegmentTracerSpeed3 != NULL) {
        mSegmentTracerSpeed3->SetTarget(&mTracerSpeedIndex3);
    }
    
    
    /*
    LevelSectionPermBlueprint *aPerm = NULL;
    if (gEditor != NULL) {
        aPerm = gEditor->PermGet();
    }
    
    if (mStepperPathSpawnCount != NULL) {
        bool aUnlink = true;
        if (aPerm != NULL) {
            aUnlink = false;
            mStepperPathSpawnCount->SetTarget(&(aPerm->mSpawnCount));
        }
        if (aUnlink) {
            mStepperPathSpawnCount->SetTarget(NULL);
        }
    }
    
    
    if (mStepperPathSpawnSpacing != NULL) {
        bool aUnlink = true;
        if (aPerm != NULL) {
            aUnlink = false;
            mStepperPathSpawnSpacing->SetTarget(&(aPerm->mSpawnSpacing));
        }
        if (aUnlink) {
            mStepperPathSpawnSpacing->SetTarget(NULL);
        }
    }
    
    if (mCheckBoxPathSpawnEqualSpacing != NULL) {
        bool aUnlink = true;
        if (aPerm != NULL) {
            aUnlink = false;
            mCheckBoxPathSpawnEqualSpacing->SetTarget(&(aPerm->mSpawnEqualSpacing));
        }
        if (aUnlink) {
            mCheckBoxPathSpawnEqualSpacing->SetTarget(NULL);
        }
    }
    
    */
    
    
}
