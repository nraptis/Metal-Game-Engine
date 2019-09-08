//
//  EditorMenuPermanent.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPermanent.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuPermanent.hpp"
#include "GamePermanentEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuPermanent::EditorMenuPermanent(GamePermanentEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPermanent";
    
    mEditor = pEditor;
    
    SetTitle("Permanent Editor");
    
    //TODO: set TRUE
    SetScrollMode(false);
    
    
    mPanelEditor = new ToolMenuPanel();
    mPanelEditor->SetTitle("Edit Paths");
    AddSection(mPanelEditor);
    
    mSegmentMode = new UISegment();
    mSegmentMode->SetSegmentCount(3);
    mSegmentMode->SetTitles("Add Perm", "Move Perm", "Select Perm");
    mSegmentMode->SetTarget(&mEditor->mPermMode);
    mPanelEditor->AddSection(mSegmentMode);
    
    
    
    
    
    mPathExtPanel = new ToolMenuPanel();
    mPathExtPanel->SetTitle("Path Ext");
    AddSection(mPathExtPanel);
    
    mSegmentPathSpeed = new UISegment();
    mSegmentPathSpeed->SetSegmentCount(8);
    mSegmentPathSpeed->SetTitles("--", "XS", "S", "MS", "M", "MF", "F", "XF");
    if (mEditor != NULL) {
        mSegmentPathSpeed->SetTarget(&mEditor->mPathSpeedClassIndex);
    }
    mPathExtPanel->AddSection(mSegmentPathSpeed);
    
    mRowVisuals = new ToolMenuSectionRow();
    mPathExtPanel->AddSection(mRowVisuals);
    
    mCheckBoxSmooth = new UICheckBox();
    mCheckBoxSmooth->SetText("Smooth");
    mRowVisuals->AddCheckBox(mCheckBoxSmooth);
    
    mCheckBoxClosed = new UICheckBox();
    mCheckBoxClosed->SetText("Closed");
    mRowVisuals->AddCheckBox(mCheckBoxClosed);
    
    
    
    
    mSnapsPanel = new ToolMenuPanel();
    mSnapsPanel->SetTitle("Snapping Constraint");
    AddSection(mSnapsPanel);
    
    mRowSnaps1 = new ToolMenuSectionRow();
    mSnapsPanel->AddSection(mRowSnaps1);
    
    
    mCheckBoxPermSnapsEnabled = new UICheckBox();
    mCheckBoxPermSnapsEnabled->SetText("Snaps");
    if (mEditor) {
        mCheckBoxPermSnapsEnabled->SetTarget(&(mEditor->mSnapsEnabled));
    }
    mRowSnaps1->AddCheckBox(mCheckBoxPermSnapsEnabled);
    
    
    mButtonSnapsBreakX = new UIButton();
    mButtonSnapsBreakX->SetText("Brk-X");
    mRowSnaps1->AddButton(mButtonSnapsBreakX);
    
    mButtonSnapsBreakY = new UIButton();
    mButtonSnapsBreakY->SetText("Brk-Y");
    mRowSnaps1->AddButton(mButtonSnapsBreakY);
    
    mRowSnaps2 = new ToolMenuSectionRow();
    mSnapsPanel->AddSection(mRowSnaps2);
    
    mLabelOffsetX = new UILabel();
    mRowSnaps2->AddLabel(mLabelOffsetX);
    
    mLabelOffsetY = new UILabel();
    mRowSnaps2->AddLabel(mLabelOffsetY);
    
    mButtonResetOffsetX = new UIButton();
    mButtonResetOffsetX->SetText("Res X");
    mRowSnaps2->AddButton(mButtonResetOffsetX);
    
    mButtonResetOffsetY = new UIButton();
    mButtonResetOffsetY->SetText("Res Y");
    mRowSnaps2->AddButton(mButtonResetOffsetY);
    
    
    
    
    mPermPanel = new ToolMenuPanel();
    mPermPanel->SetTitle("Perm Picker");
    AddSection(mPermPanel);
    
    mRowPermanent1 = new ToolMenuSectionRow();
    mPermPanel->AddSection(mRowPermanent1);
    
    mButtonDeletePermanent = new UIButton();
    mButtonDeletePermanent->SetText("Delete Perm");
    mRowPermanent1->AddButton(mButtonDeletePermanent);
    
    mButtonEditPermanentPaths = new UIButton();
    mButtonEditPermanentPaths->SetText("Edit Paths");
    mRowPermanent1->AddButton(mButtonEditPermanentPaths);
    
    mRowPermanent2 = new ToolMenuSectionRow();
    mPermPanel->AddSection(mRowPermanent2);
    
    mButtonAddPath = new UIButton();
    mButtonAddPath->SetText("Add Path");
    mRowPermanent2->AddButton(mButtonAddPath);
    
    mButtonDeletePath = new UIButton();
    mButtonDeletePath->SetText("Delete Path");
    mRowPermanent2->AddButton(mButtonDeletePath);
    
    
    
    DeactivateCloseButton();
}

EditorMenuPermanent::~EditorMenuPermanent() {
    if (mEditor != NULL) {
        if (mEditor->mMenuPerm == this) {
            mEditor->mMenuPerm = NULL;
        }
    }
}

void EditorMenuPermanent::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuPermanent::Notify(void *pSender, const char *pNotification) {
    
    if (mEditor == NULL) { return; }
    if (gEditor == NULL) { return; }
    
    if (pSender == mButtonSnapsBreakX) { mEditor->BreakConstraintX(); }
    if (pSender == mButtonSnapsBreakY) { mEditor->BreakConstraintY(); }
    
    if (pSender == mButtonDeletePermanent) { mEditor->DeletePermanent(); }
    if (pSender == mButtonEditPermanentPaths) { mEditor->OpenPathEditor(); }
    if (pSender == mButtonAddPath) { mEditor->AddPath(); gEditor->RefreshPlayback(); }
    if (pSender == mButtonDeletePath) { mEditor->DeletePath(); gEditor->RefreshPlayback(); }
    
    
    
    if (pSender == mButtonResetOffsetX) { mEditor->ResetOffsetX(); gEditor->RefreshPlayback(); }
    if (pSender == mButtonResetOffsetY) { mEditor->ResetOffsetY(); gEditor->RefreshPlayback(); }
    
    
    if (pSender == mCheckBoxSmooth) {  gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxClosed) {  gEditor->RefreshPlayback(); }
    
    if (pSender == mSegmentPathSpeed) { mEditor->RefreshSpeed(); gEditor->RefreshPlayback(); }
    
    
    
    
}

void EditorMenuPermanent::Update() {
    
    
    if (mEditor == NULL) {
        return;
    }
    
    LevelSectionPermanentBlueprint *aPerm = gEditor->PermGet();
    
    
    
    if (mCheckBoxSmooth != NULL) {
        bool aUnlink = true;
        if (aPerm != NULL) {
            aUnlink = false;
            
            mCheckBoxSmooth->SetTarget(&(aPerm->mPath.mSmooth));
        }
        if (aUnlink) {
            mCheckBoxSmooth->SetTarget(NULL);
        }
    }
    
    if (mCheckBoxClosed != NULL) {
        bool aUnlink = true;
        if (aPerm != NULL) {
            aUnlink = false;
            mCheckBoxClosed->SetTarget(&(aPerm->mPath.mClosed));
        }
        if (aUnlink) {
            mCheckBoxClosed->SetTarget(NULL);
        }
    }
    
    if (mLabelOffsetX != NULL) {
        if (aPerm != NULL) {
            int aNum = round(aPerm->mConstraint.mOffsetX);
            mLabelOffsetX->SetText(FString("X: ") + FString(aNum));
        } else {
            mLabelOffsetX->SetText(FString("X: ???"));
        }
    }
    
    if (mLabelOffsetY != NULL) {
        if (aPerm != NULL) {
            int aNum = round(aPerm->mConstraint.mOffsetY);
            mLabelOffsetY->SetText(FString("Y: ") + FString(aNum));
        } else {
            mLabelOffsetY->SetText(FString("Y: ???"));
        }
    }
    
    /*
     LevelWaveBlueprint *aWave = NULL;
     if (gEditor) {
     aWave = gEditor->mSection.mCurrentWave;
     }
     
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
