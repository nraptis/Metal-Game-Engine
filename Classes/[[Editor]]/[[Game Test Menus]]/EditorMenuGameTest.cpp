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
    
    
    
    mName = "EditorMenuGameTest";
    SetTitle("Game Test");
    
    SetScrollMode(true);
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonClose = new UIButton();
    mButtonClose->SetText("Close");
    mRowMain1->AddButton(mButtonClose);
    
    
    mButtonRestart = new UIButton();
    mButtonRestart->SetText("Restart");
    mRowMain1->AddButton(mButtonRestart);

    
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
    
    
    if (pSender == mButtonClose) {
#ifdef EDITOR_MODE
        gApp->EditorTestSwitchToEditor();
#endif
    }
    
    if (pSender == mButtonRestart) {
#ifdef EDITOR_MODE
        gGame->LoadEditorTest();
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
