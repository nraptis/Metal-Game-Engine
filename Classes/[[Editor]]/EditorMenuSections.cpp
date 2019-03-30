//
//  EditorMenuSections.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuSections.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuSections.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuSections::EditorMenuSections(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuSections";
    
    mEditor = pEditor;
    
    
    SetTitle("Section");
    SetScrollMode(true);
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonNewSection = new UIButton();
    mButtonNewSection->SetText("New Section");
    mRowMain1->AddButton(mButtonNewSection);
    
    mButtonSaveSection = new UIButton();
    mButtonSaveSection->SetText("Save..");
    mRowMain1->AddButton(mButtonSaveSection);
    
    mButtonLoadSection = new UIButton();
    mButtonLoadSection->SetText("Load..");
    mRowMain1->AddButton(mButtonLoadSection);
    
    mRowMain2 = new ToolMenuSectionRow();
    AddSection(mRowMain2);
    
    
    mButtonClear = new UIButton();
    mButtonClear->SetText("Clear");
    mRowMain2->AddButton(mButtonClear);
    
    mButtonLoadCleared = new UIButton();
    mButtonLoadCleared->SetText("Undo Clear");
    mRowMain2->AddButton(mButtonLoadCleared);
    
    
    mMenusPanel = new ToolMenuPanel();
    mMenusPanel->SetTitle("Menus...");
    AddSection(mMenusPanel);
    
    mRowMenus1 = new ToolMenuSectionRow();
    mMenusPanel->AddSection(mRowMenus1);
    
    
    mButtonShowSpawn = new UIButton();
    mButtonShowSpawn->SetText("Spawn");
    mRowMenus1->AddButton(mButtonShowSpawn);
    
    mButtonShowWavePicker = new UIButton();
    mButtonShowWavePicker->SetText("Wave Picker");
    mRowMenus1->AddButton(mButtonShowWavePicker);
    
    mButtonShowSpawnPicker = new UIButton();
    mButtonShowSpawnPicker->SetText("Spawn Picker");
    mRowMenus1->AddButton(mButtonShowSpawnPicker);
    
    
    mRowMenus2 = new ToolMenuSectionRow();
    mMenusPanel->AddSection(mRowMenus2);
    
    mButtonShowAttachments = new UIButton();
    mButtonShowAttachments->SetText("Attachments");
    mRowMenus2->AddButton(mButtonShowAttachments);
    
    
    
    
    
    
    
    
    mWavePanel = new ToolMenuPanel();
    mWavePanel->SetTitle("Wave Panel");
    AddSection(mWavePanel);
    
    mRowWave1 = new ToolMenuSectionRow();
    mWavePanel->AddSection(mRowWave1);
    
    
    mButtonAddWave = new UIButton();
    mButtonAddWave->SetText("Add Wave");
    mRowWave1->AddButton(mButtonAddWave);
    
    mButtonDeleteWave = new UIButton();
    mButtonDeleteWave->SetText("Delete Wave");
    mRowWave1->AddButton(mButtonDeleteWave);
    
    
    mButtonEditPaths = new UIButton();
    mButtonEditPaths->SetText("[E]dit Paths");
    mRowWave1->AddButton(mButtonEditPaths);
    
    
    mRowWave2 = new ToolMenuSectionRow();
    mWavePanel->AddSection(mRowWave2);
    
    
    mCheckBoxPreview = new UICheckBox();
    mCheckBoxPreview->SetText("References");
    mRowWave2->AddCheckBox(mCheckBoxPreview);
    
    mButtonMoveWaveUp = new UIButton();
    mButtonMoveWaveUp->SetText("Send Fwd");
    mRowWave2->AddButton(mButtonMoveWaveUp);
    
    mButtonMoveWaveDown = new UIButton();
    mButtonMoveWaveDown->SetText("Send Bck");
    mRowWave2->AddButton(mButtonMoveWaveDown);
    
    
    
    
    DeactivateCloseButton();
}

EditorMenuSections::~EditorMenuSections() {
    
}

void EditorMenuSections::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuSections::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        if (pSender == mButtonEditPaths) { mEditor->OpenPathEditor(); }
        if (pSender == mButtonAddWave) { mEditor->WaveAdd(); }
        if (pSender == mButtonDeleteWave) { mEditor->WaveRemove(); }
        
        if (pSender == mButtonMoveWaveUp) { mEditor->WaveMoveUp(); }
        if (pSender == mButtonMoveWaveDown) { mEditor->WaveMoveDown(); }
        
        if (pSender == mButtonClear) { mEditor->Clear(); }
        if (pSender == mButtonLoadCleared) { mEditor->LoadCleared(); }
        
        if (pSender == mButtonShowSpawn) { mEditor->OpenSpawnMenu(); }
        if (pSender == mButtonShowWavePicker) { mEditor->OpenWavePickerMenu(); }
        if (pSender == mButtonShowSpawnPicker) { mEditor->OpenSpawnPickerMenu(); }
        
        if (pSender == mButtonShowAttachments) { mEditor->OpenAttachmentMenu(); }
        
        
        
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

void EditorMenuSections::Update() {
    
    if (gGame != NULL) {
#ifdef EDITOR_MODE
        mCheckBoxPreview->SetTarget(&gGame->mEditorShowReferenced);
#else
        mCheckBoxPreview->SetTarget(NULL);
#endif
    }
    
    
}
