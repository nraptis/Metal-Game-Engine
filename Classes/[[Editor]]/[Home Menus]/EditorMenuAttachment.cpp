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
#include "EditorMenuPanelFormationConfiguration.hpp"
#include "LevelSectionPermBlueprint.hpp"

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
    mCheckBoxShortCircuitKnockDown = NULL;
    mCheckBoxShortCircuit = NULL;
    
    
    
    SetTitle("Spawn Attach");
    SetScrollMode(true);
    
    mPanelObjectTypes = new ToolMenuPanel();
    mPanelObjectTypes->SetTitle("Object");
    AddSection(mPanelObjectTypes);
    
    mRowObjectTypes1 = new ToolMenuSectionRow();
    mPanelObjectTypes->AddSection(mRowObjectTypes1);
    
    
    mButtonPickBalloon = new UIButton();
    mButtonPickBalloon->SetText("Balloon");
    mRowObjectTypes1->AddButton(mButtonPickBalloon);
    
    mButtonPickBrickHead = new UIButton();
    mButtonPickBrickHead->SetText("Brick");
    mRowObjectTypes1->AddButton(mButtonPickBrickHead);
    
    
    mRowObjectTypes2 = new ToolMenuSectionRow();
    mPanelObjectTypes->AddSection(mRowObjectTypes2);
    
    mButtonPickBomb = new UIButton();
    mButtonPickBomb->SetText("Bomb");
    mRowObjectTypes2->AddButton(mButtonPickBomb);
    
    mButtonPickTurtle = new UIButton();
    mButtonPickTurtle->SetText("Turtle");
    mRowObjectTypes2->AddButton(mButtonPickTurtle);
    
    
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
    
    mPanelFormationConfiguration = new EditorMenuPanelFormationConfiguration();
    mPanelFormations->AddSection(mPanelFormationConfiguration);
    //AddSection(mPanelFormationConfiguration);
    
    mPanelFormations->Collapse();
    
    
    
    //if (mEditor != NULL) {
        
        mPanelBehavior = new ToolMenuPanel();
        mPanelBehavior->SetTitle("Behaviors");
        AddSection(mPanelBehavior);
    
    mRowBehavior1 = new ToolMenuSectionRow();
    mPanelBehavior->AddSection(mRowBehavior1);
    
    
    mCheckBoxShortCircuit = new UICheckBox();
    mCheckBoxShortCircuit->SetText("Short Circ");
    mRowBehavior1->AddCheckBox(mCheckBoxShortCircuit);
    
    mCheckBoxShortCircuitKnockDown = new UICheckBox();
    mCheckBoxShortCircuitKnockDown->SetText("Knock Down");
    mRowBehavior1->AddCheckBox(mCheckBoxShortCircuitKnockDown);
    
    
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
            
            LevelPermSpawnBlueprint *aSpawn = gEditor->PermSpawnGet();
            if (aSpawn != NULL) {
                gEditor->PickFormationForPermSpawnNode();
            } else {
                LevelSectionPermBlueprint *aPerm = gEditor->PermGet();
                if (aPerm != NULL) {
                    gEditor->PickFormationForPerm();
                }
            }
        }
    }
    
    if (pSender == mButtonClearFormation) { gEditor->SpawnClearFormation(); }
    
    if (pSender == mButtonPickBalloon) { gEditor->SpawnPickBalloon(); }
    if (pSender == mButtonPickBrickHead) { gEditor->SpawnPickBrickHead(); }
    if (pSender == mButtonPickBomb) { gEditor->SpawnPickBomb(); }
    if (pSender == mButtonPickTurtle) { gEditor->SpawnPickTurtle(); }
    
}

void EditorMenuAttachment::Update() {
    
    
    LevelWaveSpawnBlueprint *aWaveSpawn = NULL;
    LevelPermSpawnBlueprint *aPermSpawn = NULL;
    LevelSectionPermBlueprint *aPerm = NULL;
    
    if (mEditor != NULL) {
        aWaveSpawn = gEditor->SpawnGet();
    } else if (mPermEditor != NULL) {
        aPermSpawn = gEditor->PermSpawnGet();
        if (aPermSpawn == NULL) {
            aPerm = gEditor->PermGet();
        }
    }
    
    if (mStepperSpacingOffset != NULL) {
        if (aWaveSpawn != NULL) {
            mStepperSpacingOffset->SetTarget(&(aWaveSpawn->mSpawnSpacingOffset));
        } else {
            mStepperSpacingOffset->SetTarget(NULL);
        }
    }
    
    
    if (mCheckBoxShortCircuit != NULL) {
        if (aWaveSpawn != NULL) {
            mCheckBoxShortCircuit->SetTarget(&(aWaveSpawn->mShortCircuit));
        } else {
            mCheckBoxShortCircuit->SetTarget(NULL);
        }
    }
    
    
    if (mCheckBoxShortCircuitKnockDown != NULL) {
        if (aWaveSpawn != NULL) {
            mCheckBoxShortCircuitKnockDown->SetTarget(&(aWaveSpawn->mShortCircuitKnockDown));
        } else {
            mCheckBoxShortCircuitKnockDown->SetTarget(NULL);
        }
    }
    
    
    
    
    
    
}
