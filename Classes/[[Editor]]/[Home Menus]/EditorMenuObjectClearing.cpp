//
//  EditorMenuObjectClearing.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuObjectClearing.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuObjectClearing.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuObjectClearing::EditorMenuObjectClearing(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuObjectClearing";
    
    mEditor = pEditor;
    
    SetTitle("Spawn (Meta)");
    
    SetScrollMode(true);
    
    
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mRowMain2 = new ToolMenuSectionRow();
    AddSection(mRowMain2);
    
    mRowMain3 = new ToolMenuSectionRow();
    AddSection(mRowMain3);
    
    mButtonKillAll = new UIButton();
    mButtonKillAll->SetText("K-All");
    mRowMain1->AddButton(mButtonKillAll);
    
    
    
    
    
    
    mButtonKillAllBalloons = new UIButton();
    mButtonKillAllBalloons->SetText("KA-B");
    mRowMain2->AddButton(mButtonKillAllBalloons);
    
    mButtonKillAllNonBalloons = new UIButton();
    mButtonKillAllNonBalloons->SetText("KA-NonB");
    mRowMain2->AddButton(mButtonKillAllNonBalloons);
    
    mButtonKillPerms = new UIButton();
    mButtonKillPerms->SetText("KA-Per");
    mRowMain3->AddButton(mButtonKillPerms);
    
    mButtonKillWaves = new UIButton();
    mButtonKillWaves->SetText("KA-Wav");
    mRowMain3->AddButton(mButtonKillWaves);

    
    
    
    
}

EditorMenuObjectClearing::~EditorMenuObjectClearing() {
    if (gEditor->mMenuObjectClearing == this) {
        gEditor->mMenuObjectClearing = NULL;
    }
}

void EditorMenuObjectClearing::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuObjectClearing::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }

    
    if (pSender == mButtonKillAll) { mEditor->KillAll(); }
    if (pSender == mButtonKillAllBalloons) { mEditor->KillAllBalloons(); }
    if (pSender == mButtonKillAllNonBalloons) { mEditor->KillAllNonBalloons(); }
    if (pSender == mButtonKillPerms) { mEditor->KillAllPerms(); }
    if (pSender == mButtonKillWaves) { mEditor->KillAllWave(); }
    
}

void EditorMenuObjectClearing::Update() {
    
    LevelWaveBlueprint *aWave = NULL;
    if (gEditor) {
        aWave = gEditor->mSection.mCurrentWave;
    }
    
    /*
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
    */
    
}
