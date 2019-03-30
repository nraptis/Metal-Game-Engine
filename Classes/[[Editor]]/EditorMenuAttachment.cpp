//
//  EditorMenuAttachment.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/29/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuAttachment.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuAttachment.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuAttachment::EditorMenuAttachment(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuAttachment";
    
    mEditor = pEditor;
    
    SetTitle("Spawn Attach");
    SetScrollMode(true);
    
    
    

    
    mPanelFormations = new ToolMenuPanel();
    mPanelFormations->SetTitle("Formations");
    AddSection(mPanelFormations);
    
    mRowFormations1 = new ToolMenuSectionRow();
    mPanelFormations->AddSection(mRowFormations1);
    
    
    mButtonPickFormation1 = new UIButton();
    mButtonPickFormation1->SetText("Form 1");
    mRowFormations1->AddButton(mButtonPickFormation1);
    
    mButtonPickFormation2 = new UIButton();
    mButtonPickFormation2->SetText("Form 2");
    mRowFormations1->AddButton(mButtonPickFormation2);
    
    mButtonClearFormation = new UIButton();
    mButtonClearFormation->SetText("1 Balloon");
    mRowFormations1->AddButton(mButtonClearFormation);
    
    
    mRowFormations2 = new ToolMenuSectionRow();
    mPanelFormations->AddSection(mRowFormations2);
    
    
    mCheckBoxInvertFormationH = new UICheckBox();
    mCheckBoxInvertFormationH->SetText("R-Flip H");
    mRowFormations2->AddCheckBox(mCheckBoxInvertFormationH);
    
    mCheckBoxInvertFormationV = new UICheckBox();
    mCheckBoxInvertFormationV->SetText("R-Flip H");
    mRowFormations2->AddCheckBox(mCheckBoxInvertFormationV);
    
   

    
    mPanelBehavior = new ToolMenuPanel();
    mPanelBehavior->SetTitle("Behaviors");
    AddSection(mPanelBehavior);
    
    
    mStepperSpacingOffset = new UIStepper();
    mStepperSpacingOffset->SetText("Spacing Offset");
    mStepperSpacingOffset->mMin = -1000;
    mStepperSpacingOffset->mMax = 1000;
    gNotify.Register(this, mStepperSpacingOffset, "stepper");
    mPanelBehavior->AddSection(mStepperSpacingOffset);
    

    
    mPanelRotation = new ToolMenuPanel();
    mPanelRotation->SetTitle("Rotation");
    AddSection(mPanelRotation);
    
    
    mSegmentRotationSpeed = new UISegment();
    mSegmentRotationSpeed->SetSegmentCount(7);
    mSegmentRotationSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    gNotify.Register(this, mSegmentRotationSpeed, "segment");
    if (gGame) {
        mSegmentRotationSpeed->SetTarget(&gEditor->mSpawnRotationSpeedClassIndex);
    }
    mPanelRotation->AddSection(mSegmentRotationSpeed);
    
    
    mRowRotation = new ToolMenuSectionRow();
    mPanelRotation->AddSection(mRowRotation);
    

    mCheckBoxRotationNegateAlways = new UICheckBox();
    mCheckBoxRotationNegateAlways->SetText("Neg Always");
    mRowRotation->AddCheckBox(mCheckBoxRotationNegateAlways);
    
    mCheckBoxRotationNegateRandom = new UICheckBox();
    mCheckBoxRotationNegateRandom->SetText("Neg Random");
    mRowRotation->AddCheckBox(mCheckBoxRotationNegateRandom);
    
    
}

EditorMenuAttachment::~EditorMenuAttachment() {
    if (gEditor->mMenuAttachment == this) {
        gEditor->mMenuAttachment = NULL;
    }
}

void EditorMenuAttachment::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuAttachment::Notify(void *pSender, const char *pNotification) {
    if (pSender == mSegmentRotationSpeed) {
        if (gEditor) { gEditor->RefreshSpawn(); }
    }
    if (pSender == mStepperSpacingOffset) {
        if (gEditor) { gEditor->RefreshSpawn(); }
    }
    
}

void EditorMenuAttachment::Update() {
    
    LevelWaveSpawnBlueprint *aSpawn = NULL;
    if (gEditor) { aSpawn = gEditor->SpawnGet(); }
    
    if (mStepperSpacingOffset != NULL) {
        bool aUnlink = true;
        if (aSpawn != NULL) {
            aUnlink = false;
            mStepperSpacingOffset->SetTarget(&(aSpawn->mSpawnSpacingOffset));
        }
        if (aUnlink) {
            mStepperSpacingOffset->SetTarget(NULL);
        }
    }
    
    
}
