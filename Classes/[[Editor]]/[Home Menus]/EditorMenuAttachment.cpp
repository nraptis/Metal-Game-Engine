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
    
    
    
    mPanelObjectTypes = new ToolMenuPanel();
    mPanelObjectTypes->SetTitle("Object");
    AddSection(mPanelObjectTypes);
    
    mRowObjectTypes1 = new ToolMenuSectionRow();
    mPanelObjectTypes->AddSection(mRowObjectTypes1);
    
    
    mButtonPickBalloon = new UIButton();
    mButtonPickBalloon->SetText("Bloon");
    mRowObjectTypes1->AddButton(mButtonPickBalloon);
    
    mButtonPickBrickHead = new UIButton();
    mButtonPickBrickHead->SetText("Brick");
    mRowObjectTypes1->AddButton(mButtonPickBrickHead);
    
    
    mRowObjectTypes2 = new ToolMenuSectionRow();
    mPanelObjectTypes->AddSection(mRowObjectTypes2);
    

    
    mPanelFormations = new ToolMenuPanel();
    mPanelFormations->SetTitle("Formations");
    AddSection(mPanelFormations);
    
    mRowFormations1 = new ToolMenuSectionRow();
    mPanelFormations->AddSection(mRowFormations1);
    
    
    mButtonPickFormation = new UIButton();
    mButtonPickFormation->SetText("Pick Form");
    mRowFormations1->AddButton(mButtonPickFormation);
    
    mButtonClearFormation = new UIButton();
    mButtonClearFormation->SetText("Clear Form");
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
    //gNotify.Register(this, mStepperSpacingOffset, "stepper");
    mPanelBehavior->AddSection(mStepperSpacingOffset);
    

    
    mPanelRotation = new ToolMenuPanel();
    mPanelRotation->SetTitle("Rotation");
    AddSection(mPanelRotation);
    
    
    mSegmentRotationSpeed = new UISegment();
    mSegmentRotationSpeed->SetSegmentCount(7);
    mSegmentRotationSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    //gNotify.Register(this, mSegmentRotationSpeed, "segment");
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
    
    if (gEditor == NULL) { return; }
    
    if (pSender == mSegmentRotationSpeed) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperSpacingOffset) { gEditor->RefreshPlayback(); }
    
    
    if (pSender == mButtonPickFormation)  { gEditor->PickFormationForSpawnNode(); }
    if (pSender == mButtonClearFormation) { gEditor->SpawnClearFormation(); }

    
    if (pSender == mButtonPickBalloon)   { gEditor->SpawnPickBalloon(); }
    if (pSender == mButtonPickBrickHead) { gEditor->SpawnPickBrickHead(); }
    
    
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
