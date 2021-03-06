//
//  EditorMenuSections.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuSections.hpp"
#include "EditorMenuSections.hpp"
#include "GameEditor.hpp"
#include "EditorMenuFormationPicker.hpp"
#include "FApp.hpp"

EditorMenuSections::EditorMenuSections(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuSections";
    
    mEditor = pEditor;
    
    
    SetTitle("Section");
    SetScrollMode(true);
    
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonBuildFormation = new UIButton();
    mButtonBuildFormation->SetText("Formations");
    mRowMain1->AddButton(mButtonBuildFormation);
    
    mButtonSaveSection = new UIButton();
    mButtonSaveSection->SetText("Save..");
    mRowMain1->AddButton(mButtonSaveSection);
    
    mButtonLoadSection = new UIButton();
    mButtonLoadSection->SetText("Load..");
    mRowMain1->AddButton(mButtonLoadSection);
    
    mRowMain2 = new ToolMenuSectionRow();
    AddSection(mRowMain2);
    
    mButtonTest = new UIButton();
    mButtonTest->SetText("Test");
    mRowMain2->AddButton(mButtonTest);
    
    
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
    mButtonShowWavePicker->SetText("Picker-W");
    mRowMenus1->AddButton(mButtonShowWavePicker);
    
    mButtonShowSpawnPicker = new UIButton();
    mButtonShowSpawnPicker->SetText("Picker-S");
    mRowMenus1->AddButton(mButtonShowSpawnPicker);
    
    mButtonShowAttachments = new UIButton();
    mButtonShowAttachments->SetText("Atch");
    mRowMenus1->AddButton(mButtonShowAttachments);
    
    mRowMenus2 = new ToolMenuSectionRow();
    mMenusPanel->AddSection(mRowMenus2);
    
    
    mButtonShowStyleChooser = new UIButton();
    mButtonShowStyleChooser->SetText("Style");
    mRowMenus2->AddButton(mButtonShowStyleChooser);
    
    mButtonShowPermanentEditor = new UIButton();
    mButtonShowPermanentEditor->SetText("Perms");
    mRowMenus2->AddButton(mButtonShowPermanentEditor);
    
    mButtonShowFormationEditor = new UIButton();
    mButtonShowFormationEditor->SetText("F-Edit");
    mRowMenus2->AddButton(mButtonShowFormationEditor);
    
    mButtonShowFormationPicker = new UIButton();
    mButtonShowFormationPicker->SetText("F-Pick");
    mRowMenus2->AddButton(mButtonShowFormationPicker);
    
    
    mRowMenus3 = new ToolMenuSectionRow();
    mMenusPanel->AddSection(mRowMenus3);
    
    mButtonShowMotionEditor = new UIButton();
    mButtonShowMotionEditor->SetText("Motion");
    mRowMenus3->AddButton(mButtonShowMotionEditor);
    
    mButtonShowObjectClearer = new UIButton();
    mButtonShowObjectClearer->SetText("Clr-Obj");
    mRowMenus3->AddButton(mButtonShowObjectClearer);
    
    mTimingPanel = new ToolMenuPanel();
    mTimingPanel->SetTitle("Timing Panel");
    AddSection(mTimingPanel);
    
    mStepperAliveTimer = new UIStepper();
    mStepperAliveTimer->SetTarget(&(gEditor->mSection.mKeepAliveTimer));
    mStepperAliveTimer->SetText("Keep Alive");
    mTimingPanel->AddSection(mStepperAliveTimer);
    
    mStepperKillTimer = new UIStepper();
    mStepperKillTimer->SetTarget(&(gEditor->mSection.mForceKillTimer));
    mStepperKillTimer->SetText("Force Kill");
    mTimingPanel->AddSection(mStepperKillTimer);
    
    
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
    
    mButtonEditWavePaths = new UIButton();
    mButtonEditWavePaths->SetText("[E]dit Paths");
    mRowWave1->AddButton(mButtonEditWavePaths);
    
    
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
    
    
    mRowWave3 = new ToolMenuSectionRow();
    mWavePanel->AddSection(mRowWave3);
    
    
    mButtonCopyWave = new UIButton();
    mButtonCopyWave->SetText("Copy");
    mRowWave3->AddButton(mButtonCopyWave);
    
    mButtonPasteWaveEOL = new UIButton();
    mButtonPasteWaveEOL->SetText("Pst-EOL");
    mRowWave3->AddButton(mButtonPasteWaveEOL);
    
    mButtonPasteWaveINS = new UIButton();
    mButtonPasteWaveINS->SetText("Pst-INS");
    mRowWave3->AddButton(mButtonPasteWaveINS);
    
    
    mButtonFlipWaveH = new UIButton();
    mButtonFlipWaveH->SetText("Inv-H");
    mRowWave3->AddButton(mButtonFlipWaveH);
    
    
    
    
    
    mPlaybackPanel = new ToolMenuPanel();
    mPlaybackPanel->SetTitle("Playback");
    AddSection(mPlaybackPanel);
    
    mRowPlayback1 = new ToolMenuSectionRow();
    mPlaybackPanel->AddSection(mRowPlayback1);
    
    
    
    mCheckBoxPlaybackEnabled = new UICheckBox();
    mCheckBoxPlaybackEnabled->SetText("Play...");
    mCheckBoxPlaybackEnabled->SetTarget(&mEditor->mEditorPlaybackEnabled);
    mRowPlayback1->AddCheckBox(mCheckBoxPlaybackEnabled);
    
    
    mButtonPlaybackRestart = new UIButton();
    mButtonPlaybackRestart->SetText("Restart");
    mRowPlayback1->AddButton(mButtonPlaybackRestart);
    
    
    //mCheckBoxPlaybackEnabled
    //mButtonPlaybackRestart
    //mCheckBoxPlaybackStartAtSelectedWave
    //mCheckBoxCurrentWaveOnly
    
    
    mRowPlayback2 = new ToolMenuSectionRow();
    mPlaybackPanel->AddSection(mRowPlayback2);
    
    mCheckBoxPlaybackStartAtSelectedWave = new UICheckBox();
    mCheckBoxPlaybackStartAtSelectedWave->SetText("From Selected");
    mCheckBoxPlaybackStartAtSelectedWave->SetTarget(&mEditor->mEditorPlaybackFromCurrentWave);
    mRowPlayback2->AddCheckBox(mCheckBoxPlaybackStartAtSelectedWave);
    
    DeactivateCloseButton();
}

EditorMenuSections::~EditorMenuSections() {
    
}

void EditorMenuSections::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuSections::Notify(void *pSender, const char *pNotification) {
    
    if (pSender == mButtonBuildFormation) { mEditor->OpenFormationEditor(NULL); }
    
    if (pSender == mButtonShowPermanentEditor) { mEditor->OpenPermanentEditor(); }
    
    if (pSender == mButtonEditWavePaths) { mEditor->OpenPathEditorForWave(); }
    if (pSender == mButtonAddWave) { mEditor->WaveAdd(); }
    if (pSender == mButtonDeleteWave) { mEditor->WaveRemove(); }
    
    if (pSender == mButtonMoveWaveUp) { mEditor->WaveMoveUp(); }
    if (pSender == mButtonMoveWaveDown) { mEditor->WaveMoveDown(); }
    
    
    if (pSender == mButtonCopyWave) { mEditor->CopyWave(); }
    if (pSender == mButtonPasteWaveEOL) { mEditor->PasteWaveAtEndOfList(); }
    if (pSender == mButtonPasteWaveINS) { mEditor->PasteWaveAfterCurrent(); }
    
    if (pSender == mButtonFlipWaveH) { mEditor->WaveFlipH(); }
    
    
    
    
    
    if (pSender == mButtonTest) { mEditor->Test(); }
    if (pSender == mButtonClear) { mEditor->Clear(); }
    if (pSender == mButtonLoadCleared) { mEditor->LoadCleared(); }
    
    if (pSender == mButtonShowSpawn) { mEditor->OpenSpawnMenu(); }
    if (pSender == mButtonShowWavePicker) { mEditor->OpenWavePickerMenu(); }
    if (pSender == mButtonShowSpawnPicker) { mEditor->OpenSpawnPickerMenu(); }
    
    if (pSender == mButtonShowAttachments) { mEditor->OpenAttachmentMenu(); }
    
    if (pSender == mButtonShowStyleChooser) { mEditor->OpenStyleMenu(); }
    
    
    
    if (pSender == mButtonShowFormationEditor) { mEditor->OpenFormationEditor(NULL); }
    if (pSender == mButtonShowFormationPicker) { mEditor->PickFormationForFormationEditor(); }
    
    
    if (pSender == mButtonShowMotionEditor) { mEditor->OpenMotionMenu(); }
    if (pSender == mButtonShowObjectClearer) { mEditor->OpenObjectClearingMenu(); }
    
    if (pSender == mButtonPlaybackRestart) { mEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxPlaybackStartAtSelectedWave) { mEditor->RefreshPlayback(); }
    
}

void EditorMenuSections::Update() {
    if (gEditor != NULL) {
        mCheckBoxPreview->SetTarget(&gEditor->mEditorShowReferenced);
    }
}
