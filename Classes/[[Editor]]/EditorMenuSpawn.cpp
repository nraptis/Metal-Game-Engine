//
//  EditorMenuSpawn.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuSpawn.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuSpawn.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuSpawn::EditorMenuSpawn(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuSpawn";
    
    mEditor = pEditor;
    
    SetTitle("Spawn Controller");
    SetScrollMode(true);
    
    mPanelGeneration = new ToolMenuPanel();
    mPanelGeneration->SetTitle("Generation");
    AddSection(mPanelGeneration);
    
    mRowGeneration = new ToolMenuSectionRow();
    mPanelGeneration->AddSection(mRowGeneration);
    
    mLabelSpeed = new UILabel();
    mLabelSpeed->SetText("Wave Speed");
    mRowGeneration->AddLabel(mLabelSpeed);
    
    mButtonClearFormation = new UIButton();
    mButtonClearFormation->SetText("No Form");
    mRowGeneration->AddButton(mButtonClearFormation);
    
    mCheckBoxSpeed = new UICheckBox();
    mCheckBoxSpeed->SetText("Speed Enable");
    mRowGeneration->AddCheckBox(mCheckBoxSpeed);
    
    
    mSegmentSpeed = new UISegment();
    mSegmentSpeed->SetSegmentCount(7);
    mSegmentSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    if (gGame) {
        mSegmentSpeed->SetTarget(&gEditor->mSpeedClassIndex);
    }
    mPanelGeneration->AddSection(mSegmentSpeed);
    gNotify.Register(this, mSegmentSpeed, "segment");
    
    
    mStepperSpawnCount = new UIStepper();
    mStepperSpawnCount->SetText("Count");
    mStepperSpawnCount->mMin = 1;
    mStepperSpawnCount->mMax = (MAX_SPAWN_COUNT);
    gNotify.Register(this, mStepperSpawnCount, "stepper");
    mPanelGeneration->AddSection(mStepperSpawnCount);
    
    mStepperSpacing = new UIStepper();
    mStepperSpacing->SetText("Spacing");
    mStepperSpacing->mMin = -1000;
    mStepperSpacing->mMax = 1000;
    gNotify.Register(this, mStepperSpacing, "stepper");
    mPanelGeneration->AddSection(mStepperSpacing);
    
    
    mPanelAttachments = new ToolMenuPanel();
    mPanelAttachments->SetTitle("Attachments");
    AddSection(mPanelAttachments);
    
    mRowFormations1 = new ToolMenuSectionRow();
    mPanelAttachments->AddSection(mRowFormations1);
    
    mButtonClearFormation = new UIButton();
    mButtonClearFormation->SetText("No Form");
    mRowFormations1->AddButton(mButtonClearFormation);
    
    mButtonDefaultFormation = new UIButton();
    mButtonDefaultFormation->SetText("Defualt");
    mRowFormations1->AddButton(mButtonDefaultFormation);
    
    mButtonPickFormation = new UIButton();
    mButtonPickFormation->SetText("Pick Form");
    mRowFormations1->AddButton(mButtonPickFormation);
    

    
    
    mPanelMovement = new ToolMenuPanel();
    mPanelMovement->SetTitle("Movement");
    AddSection(mPanelMovement);
    
    
    mSliderRotation = new UISlider();
    mSliderRotation->SetText("Rotate:");
    //mSliderViewDistance->SetValue(&mCamera->mDistance);
    mSliderRotation->SetRange(-20.0f, 20.0f);
    mPanelMovement->AddSection(mSliderRotation);
    
}

EditorMenuSpawn::~EditorMenuSpawn() {
    if (gEditor->mMenuSpawn == this) {
        gEditor->mMenuSpawn = NULL;
    }
}

void EditorMenuSpawn::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuSpawn::Notify(void *pSender, const char *pNotification) {
    
    if (FString("slider_update") == pNotification) {
        
    }
    
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        if (pSender == mSegmentSpeed) {
            if (gEditor) {
                gEditor->RefreshWaveSpeed();
            }
        }
    }
    
    if (FString(pNotification) == "stepper") {
        UIStepper *aStepper = (UIStepper *)pSender;
        if (aStepper == mStepperSpawnCount) {
            if (gEditor) { gEditor->RefreshWave(); }
        }
        
        if (aStepper == mStepperSpacing) {
            if (gEditor) { gEditor->RefreshWave(); }
        }
        
        
    }
}

void EditorMenuSpawn::Update() {
    
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
    
}
