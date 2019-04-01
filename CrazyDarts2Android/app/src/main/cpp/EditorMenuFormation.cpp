//
//  EditorMenuFormation.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

//
//  EditorMenuFormationMain.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormation.hpp"
#include "GameFormationEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuFormation::EditorMenuFormation(GameFormationEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuFormation";
    
    mEditor = pEditor;
    
    SetTitle("Formation Builder");
    SetScrollMode(true);
    
    mEditorPanel = new ToolMenuPanel();
    mEditorPanel->SetTitle("Edit Paths");
    AddSection(mEditorPanel);
    
    mSegmentMode = new UISegment();
    mSegmentMode->SetSegmentCount(3);
    mSegmentMode->SetTitles("Add Point", "Move Point", "Select Point");
    //mSegmentMode->SetTarget(&mEditor->mPathMode);
    mEditorPanel->AddSection(mSegmentMode);
    
    mRowVisuals = new ToolMenuSectionRow();
    mEditorPanel->AddSection(mRowVisuals);
    
    mCheckBoxSmooth = new UICheckBox();
    mCheckBoxSmooth->SetText("Smoothing");
    mRowVisuals->AddCheckBox(mCheckBoxSmooth);
    
    mCheckBoxPreview = new UICheckBox();
    mCheckBoxPreview->SetText("References");
    if (gEditor != NULL) {
        mCheckBoxPreview->SetTarget(&gEditor->mEditorShowReferenced);
    }
    mRowVisuals->AddCheckBox(mCheckBoxPreview);
    
    mPointsPanel = new ToolMenuPanel();
    mPointsPanel->SetTitle("Points");
    AddSection(mPointsPanel);
    
    mStepperWait = new UIStepper();
    mStepperWait->SetText("Wait:");
    mPointsPanel->AddSection(mStepperWait);
    
    mStepperChamfer = new UIStepper();
    mStepperChamfer->SetText("Chamfer:");
    mPointsPanel->AddSection(mStepperChamfer);
    
    mRowPointOptions = new ToolMenuSectionRow();
    mPointsPanel->AddSection(mRowPointOptions);
    
    mButtonDeletePoint = new UIButton();
    mButtonDeletePoint->SetText("Del Point");
    mRowPointOptions->AddButton(mButtonDeletePoint);
    
    mButtonBreakXConstraint = new UIButton();
    mButtonBreakXConstraint->SetText("Break X");
    mRowPointOptions->AddButton(mButtonBreakXConstraint);
    
    mButtonBreakYConstraint = new UIButton();
    mButtonBreakYConstraint->SetText("Break Y");
    mRowPointOptions->AddButton(mButtonBreakYConstraint);
    
    mConstraintPanel = new ToolMenuPanel();
    mConstraintPanel->SetTitle("Constraints");
    mPointsPanel->AddSection(mConstraintPanel);
    
    mRowSnapX = new ToolMenuSectionRow();
    mConstraintPanel->AddSection(mRowSnapX);
    
    mCheckBoxSnapX = new UICheckBox();
    mCheckBoxSnapX->SetText("Target X");
    //mCheckBoxSnapX->SetTarget(&mEditor->mConstrainXToPoint);
    mRowSnapX->AddCheckBox(mCheckBoxSnapX);
    
    mButtonSnapPrevX = new UIButton();
    mButtonSnapPrevX->SetText("Prev X");
    mRowSnapX->AddButton(mButtonSnapPrevX);
    
    mButtonSnapNextX = new UIButton();
    mButtonSnapNextX->SetText("Next X");
    mRowSnapX->AddButton(mButtonSnapNextX);
    
    mRowSnapY = new ToolMenuSectionRow();
    mConstraintPanel->AddSection(mRowSnapY);
    
    mCheckBoxSnapY = new UICheckBox();
    mCheckBoxSnapY->SetText("Target Y");
    //mCheckBoxSnapY->SetTarget(&mEditor->mConstrainYToPoint);
    mRowSnapY->AddCheckBox(mCheckBoxSnapY);
    
    mButtonSnapPrevY = new UIButton();
    mButtonSnapPrevY->SetText("Prev Y");
    mRowSnapY->AddButton(mButtonSnapPrevY);
    
    mButtonSnapNextY = new UIButton();
    mButtonSnapNextY->SetText("Next Y");
    mRowSnapY->AddButton(mButtonSnapNextY);
    
    DeactivateCloseButton();
}

EditorMenuFormation::~EditorMenuFormation() {
    printf("Kill Editor");
}

void EditorMenuFormation::Layout() {
    ToolMenu::Layout();
    
}

void EditorMenuFormation::Update() {
    ToolMenu::Update();
    
    /*
    if (mCheckBoxSmooth) {
        bool aUnlink = true;
        if (mEditor->mWave != NULL) {
            aUnlink = false;
            mCheckBoxSmooth->SetTarget(&(mEditor->mWave->mPath.mSmooth));
        }
        if (aUnlink) {
            mCheckBoxSmooth->SetTarget(NULL);
        }
    }
    */
    
}
//

void EditorMenuFormation::Notify(void *pSender, const char *pNotification) {
    
    if (pSender == mButtonDeletePoint) { }

}
