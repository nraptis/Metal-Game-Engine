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
    AddSection(mSegmentTracerSpeed1);
    
    //mSegmentTracerSpeed2;
    //mSegmentTracerSpeed3;
    
    
    
    /*
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonReset;
    
    UISegment                               *mSegmentTracerSpeedGlobal;
    
    ToolMenuPanel                           *mPanelTracerSpeed;
    
    
    */
    
    
    /*
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
    
    
    
    
    mMenuPathSpawn = new ToolMenuPanel();
    mMenuPathSpawn->SetTitle("Path Spawn");
    AddSection(mMenuPathSpawn);
    
    mStepperPathSpawnCount = new UIStepper();
    mStepperPathSpawnCount->SetText("Spawn Count");
    mMenuPathSpawn->AddSection(mStepperPathSpawnCount);
    
    
    mStepperPathSpawnSpacing = new UIStepper();
    mStepperPathSpawnSpacing->SetText("Spawn Spacing");
    mMenuPathSpawn->AddSection(mStepperPathSpawnSpacing);
    
    
    
    
    mRowPathSpawn1 = new ToolMenuSectionRow();
    mMenuPathSpawn->AddSection(mRowPathSpawn1);
    
    mCheckBoxPathSpawnEqualSpacing = new UICheckBox();
    mCheckBoxPathSpawnEqualSpacing->SetText("Space Evenly");
    mRowPathSpawn1->AddCheckBox(mCheckBoxPathSpawnEqualSpacing);
    
    
    
    
    
    mMenusPanel = new ToolMenuPanel();
    mMenusPanel->SetTitle("Menus");
    AddSection(mMenusPanel);
    
    mRowMenus1 = new ToolMenuSectionRow();
    mMenusPanel->AddSection(mRowMenus1);
    
    mButtonMenuSpawnPicker = new UIButton();
    mButtonMenuSpawnPicker->SetText("Spawn Picker");
    mRowMenus1->AddButton(mButtonMenuSpawnPicker);
    
    mButtonMenuPermPicker = new UIButton();
    mButtonMenuPermPicker->SetText("Perm Picker");
    mRowMenus1->AddButton(mButtonMenuPermPicker);
    
    
    
    mRowMenus2 = new ToolMenuSectionRow();
    mMenusPanel->AddSection(mRowMenus2);
    
    mButtonMenuAttachment = new UIButton();
    mButtonMenuAttachment->SetText("Attachments");
    mRowMenus2->AddButton(mButtonMenuAttachment);
    
    
    mButtonMenuMotionPerm = new UIButton();
    mButtonMenuMotionPerm->SetText("Mot-Perm");
    mRowMenus2->AddButton(mButtonMenuMotionPerm);
    
    
    mButtonMenuMotionSpawn = new UIButton();
    mButtonMenuMotionSpawn->SetText("Mot-Spawn");
    mRowMenus2->AddButton(mButtonMenuMotionSpawn);
    
    DeactivateCloseButton();
    */
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
    
    
    if (pSender == mSegmentTracerSpeed1) { gEditor->RefreshPlayback(); }
    
    
    
    
    
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
        
        
    }
    
    
    
    if (mSegmentTracerSpeedGlobal != NULL) {
        mSegmentTracerSpeedGlobal->SetTarget(&mTracerSpeedIndexGlobal);
    }
    
    if (mSegmentTracerSpeed1 != NULL) {
        
        if (aConfig != NULL) {
            mSegmentTracerSpeed1->SetTarget(&aConfig->mTracerSpeed1);
        } else {
            mSegmentTracerSpeed1->SetTarget(NULL);
        }
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
