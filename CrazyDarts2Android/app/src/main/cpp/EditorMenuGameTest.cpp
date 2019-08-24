//
//  EditorMenuGameTest.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuGameTest.hpp"
#include "Game.hpp"
#include "GameContainer.hpp"

EditorMenuGameTest::EditorMenuGameTest() : ToolMenu() {
    
    mName = "Game_Test_Menu";
    SetTitle("Game Test");
    
    SetScrollMode(true);
    
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

EditorMenuGameTest::~EditorMenuGameTest() {
    if (gGameContainer != NULL) {
        if (gGameContainer->mEditorMenu == this) {
            gGameContainer->mEditorMenu = NULL;
        }
    }
}

void EditorMenuGameTest::Layout() {
    ToolMenu::Layout();
    
}

void EditorMenuGameTest::Notify(void *pSender, const char *pNotification) {
    
    if (gGame == NULL) { return; }
    if (gGameContainer == NULL) { return; }
    
    
    if (pSender == mButtonCloseEditor) {
#ifdef EDITOR_MODE
        gApp->EditorTestSwitchToEditor();
#endif
    }
    
    
    
    
    /*
     if (pSender == mButtonCloseEditor) { mEditor->Close(); }
     */
    
}

void EditorMenuGameTest::Update() {
    
    if (gGame == NULL) { return; }
    if (gGameContainer == NULL) { return; }
    
    /*
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
     */
    
}
