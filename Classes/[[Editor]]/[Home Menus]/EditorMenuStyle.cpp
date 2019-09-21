//
//  EditorMenuStyle.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuStyle.hpp"
#include "EditorMenuStyle.hpp"
#include "GameEditor.hpp"
#include "GamePermanentEditor.hpp"


EditorMenuStyle::EditorMenuStyle(GameEditor *pEditor) : ToolMenu() {
    mEditor = pEditor;
    mPermEditor = NULL;
    
    Init();
}

EditorMenuStyle::EditorMenuStyle(GamePermanentEditor *pEditor) {
    mEditor = NULL;
    mPermEditor = pEditor;
    
    Init();
}

void EditorMenuStyle::Init() {
    
    mName = "EditorMenuStyle";
    SetTitle("Style Editor");
    SetScrollMode(true);
    
    mIsForPermSpawn = false;
    mStyleController = NULL;
    
    mPanelMainControls = new ToolMenuPanel();
    mPanelMainControls->SetTitle("Main");
    AddSection(mPanelMainControls);
    
    
    mRowMain1 = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowMain1);
    
    mRowMain2 = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowMain2);
    
    
    mCheckBoxThreadsDisable = new UICheckBox();
    mCheckBoxThreadsDisable->SetText("No Threads");
    mRowMain1->AddCheckBox(mCheckBoxThreadsDisable);
    
    mCheckBoxBobbleEnable = new UICheckBox();
    mCheckBoxBobbleEnable->SetText("All Bobble");
    mRowMain1->AddCheckBox(mCheckBoxBobbleEnable);
    
    mCheckBoxRandomizeSpin = new UICheckBox();
    mCheckBoxRandomizeSpin->SetText("Rnd Spin");
    mRowMain2->AddCheckBox(mCheckBoxRandomizeSpin);

    
    
    
}

EditorMenuStyle::~EditorMenuStyle() {
    if (gEditor != NULL) {
        if (gEditor->mMenuStyle == this) {
            gEditor->mMenuStyle = NULL;
        }
    }
    if (gPermEditor != NULL) {
        if (gPermEditor->mMenuStyle == this) {
            gPermEditor->mMenuStyle = NULL;
        }
    }
}

void EditorMenuStyle::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuStyle::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }
    
    if (mStyleController != NULL) {
        
        
        if (pSender == mCheckBoxThreadsDisable) {
            //mMotionController->AddSliceNegate();
            gEditor->RefreshPlayback();
        }
        
    }
}

void EditorMenuStyle::Update() {
    
    mStyleController = NULL;
    if (gEditor == NULL) { return; }
    
    LevelPermSpawnBlueprint *aPermSpawn = gEditor->PermSpawnGet();
    LevelSectionPermBlueprint *aPerm = gEditor->PermGet();
    LevelWaveSpawnBlueprint *aSpawn = gEditor->SpawnGet();
    
    mStyleController = NULL;
    if (mEditor != NULL) {
        if (aSpawn != NULL) {
            mStyleController = &(aSpawn->mStyleController);
        }
    }
    
    if (mPermEditor != NULL) {
        if (aPerm != NULL) {
            if (aPerm->IsPathPerm()) {
                if (aPermSpawn != NULL) {
                    mStyleController = &(aPermSpawn->mStyleController);
                }
            } else {
                mStyleController = &(aPerm->mStyleController);
            }
        }
    }
    
    if (mCheckBoxThreadsDisable != NULL) {
        if (mStyleController != NULL) {
            mCheckBoxThreadsDisable->SetTarget(&(mStyleController->mDisableThreads));
        } else {
            mCheckBoxThreadsDisable->SetTarget(NULL);
        }
    }
    
    if (mCheckBoxBobbleEnable != NULL) {
        if (mStyleController != NULL) {
            mCheckBoxBobbleEnable->SetTarget(&(mStyleController->mEnableBobbleMode));
        } else {
            mCheckBoxBobbleEnable->SetTarget(NULL);
        }
    }
    
    if (mCheckBoxRandomizeSpin != NULL) {
        if (mStyleController != NULL) {
            mCheckBoxRandomizeSpin->SetTarget(&(mStyleController->mRandomizeSpin));
        } else {
            mCheckBoxRandomizeSpin->SetTarget(NULL);
        }
    }
    
}
