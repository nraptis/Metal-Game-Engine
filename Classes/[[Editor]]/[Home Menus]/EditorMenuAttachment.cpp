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
#include "GamePermanentEditor.hpp"
//#include "FApp.hpp"

EditorMenuAttachment::EditorMenuAttachment(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuAttachment";
    
    mEditor = pEditor;
    mPermEditor = NULL;
    
    Init();
}

EditorMenuAttachment::EditorMenuAttachment(GamePermanentEditor *pEditor) {
    mEditor = NULL;
    mPermEditor = pEditor;
    
    Init();
}

void EditorMenuAttachment::Init() {
    
    mStepperSpacingOffset = NULL;
    
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
    
    
    
    
    //if (mEditor != NULL) {
        
        mPanelBehavior = new ToolMenuPanel();
        mPanelBehavior->SetTitle("Behaviors");
        AddSection(mPanelBehavior);
        
        mStepperSpacingOffset = new UIStepper();
        mStepperSpacingOffset->SetText("Spacing Offset");
        mStepperSpacingOffset->mMin = -1000;
        mStepperSpacingOffset->mMax = 1000;
        mPanelBehavior->AddSection(mStepperSpacingOffset);
    //}

}

EditorMenuAttachment::~EditorMenuAttachment() {
    
    if (gEditor != NULL) {
        if (gEditor->mMenuAttachment == this) {
            gEditor->mMenuAttachment = NULL;
        }
    }
    if (mPermEditor != NULL) {
        if (mPermEditor->mMenuAttachment == this) {
            mPermEditor->mMenuAttachment = NULL;
        }
    }
}

void EditorMenuAttachment::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuAttachment::Notify(void *pSender, const char *pNotification) {
    
    
    
    if (pSender == mStepperSpacingOffset) { gEditor->RefreshPlayback(); }
    
    if (pSender == mButtonPickFormation)  {
        if (mEditor != NULL) {
            gEditor->PickFormationForSpawnNode();
        }
        if (mPermEditor != NULL) {
            gEditor->PickFormationForPermSpawnNode();
        }
    }
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
