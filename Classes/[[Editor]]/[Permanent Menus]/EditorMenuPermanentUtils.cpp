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
#include "GameEditor.hpp"
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
    if (gEditor == NULL) { return; }
    
    if (pSender == mButtonCloseEditor) { mEditor->Close(); }
    if (pSender == mButtonResetPerm) { mEditor->ResetSelected(); }
    
    
    if (pSender == mButtonMenuSpawnPicker) { mEditor->OpenMenuSpawnPicker(); }
    if (pSender == mButtonMenuPermPicker) { mEditor->OpenMenuPermPicker(); }
    if (pSender == mButtonMenuAttachment) { mEditor->OpenMenuAttachment(); }
    
    if (pSender == mButtonMenuMotionPerm) { mEditor->OpenMenuMotionForPerm(); }
    if (pSender == mButtonMenuMotionSpawn) { mEditor->OpenMenuMotionForSpawn(); }
    
    if (pSender == mStepperPathSpawnCount) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxPathSpawnEqualSpacing) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPathSpawnSpacing) { gEditor->RefreshPlayback(); }
    
}

void EditorMenuPermanentUtils::Update() {
    
    LevelSectionPermanentBlueprint *aPerm = NULL;
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
    
    /*
    
    */
    
    /*
    LevelWaveBlueprint *aWave = NULL;
    if (gEditor) {
        aWave = gEditor->mSection.mCurrentWave;
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
