//
//  EditorMenuPathMain.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPath.hpp"
#include "EditorMenuPath.hpp"
#include "GamePathEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuPath::EditorMenuPath(GamePathEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPath";
    
    mEditor = pEditor;
    
    SetTitle("Path Tools");
    SetScrollMode(true);
    
    mEditorPanel = new ToolMenuPanel();
    mEditorPanel->SetTitle("Edit Paths");
    AddSection(mEditorPanel);
    
    mSegmentMode = new UISegment();
    mSegmentMode->SetSegmentCount(3);
    mSegmentMode->SetTitles("Add Point", "Move Point", "Select Point");
    mSegmentMode->SetTarget(&mEditor->mPathMode);
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
    //gNotify.Register(this, mStepperWait, "stepper");
    
    mStepperChamfer = new UIStepper();
    mStepperChamfer->SetText("Chamfer:");
    mPointsPanel->AddSection(mStepperChamfer);
    //gNotify.Register(this, mStepperChamfer, "stepper");
    
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
    mCheckBoxSnapX->SetTarget(&mEditor->mConstrainXToPoint);
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
    mCheckBoxSnapY->SetTarget(&mEditor->mConstrainYToPoint);
    mRowSnapY->AddCheckBox(mCheckBoxSnapY);
    
    mButtonSnapPrevY = new UIButton();
    mButtonSnapPrevY->SetText("Prev Y");
    mRowSnapY->AddButton(mButtonSnapPrevY);
    
    mButtonSnapNextY = new UIButton();
    mButtonSnapNextY->SetText("Next Y");
    mRowSnapY->AddButton(mButtonSnapNextY);
    
    DeactivateCloseButton();
}

EditorMenuPath::~EditorMenuPath() {
    printf("Kill Editor");
}

void EditorMenuPath::Layout() {
    ToolMenu::Layout();
    
}

void EditorMenuPath::Update() {
    ToolMenu::Update();
    
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
    
    if (mStepperWait) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mEditor->mPath->mNodeList.Fetch(mEditor->mPath->mSelectedIndex);
            if (aNode) {
                aUnlink = false;
                mStepperWait->SetTarget(&(aNode->mWaitTimer));
            }
        }
        if (aUnlink) {
            mStepperWait->SetTarget(NULL);
        }
    }
    
    if (mStepperChamfer) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mEditor->mPath->mNodeList.Fetch(mEditor->mPath->mSelectedIndex);
            if (aNode) {
                aUnlink = false;
                mStepperChamfer->SetTarget(&(aNode->mChamferSize));
            }
        }
        if (aUnlink) {
            mStepperChamfer->SetTarget(NULL);
        }
    }
    
    
    
    
    
}
//

void EditorMenuPath::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
        if (pSender == mButtonDeletePoint) { mEditor->PathDeletePoint(); }
        
        if (pSender == mButtonBreakXConstraint) { mEditor->ConstraintXToType(X_CONSTRAINT_NONE); }
        if (pSender == mButtonBreakYConstraint) { mEditor->ConstraintYToType(Y_CONSTRAINT_NONE); }
        
        if (pSender == mButtonSnapPrevX) { mEditor->ConstraintXToPrev(); }
        if (pSender == mButtonSnapNextX) { mEditor->ConstraintXToNext(); }
        
        if (pSender == mButtonSnapPrevY) { mEditor->ConstraintYToPrev(); }
        if (pSender == mButtonSnapNextY) { mEditor->ConstraintYToNext(); }
    }
    
    if (FString(pNotification) == "stepper") {
        UIStepper *aStepper = (UIStepper *)pSender;
        if (aStepper == mStepperWait) {
            mEditor->PathRefresh();
        }
        if (aStepper == mStepperChamfer) {
            mEditor->PathRefresh();
        }
        
    }
    
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
    
    if (FString(pNotification) == "checkbox") {
        UICheckBox *aCheckbox = (UICheckBox *)pSender;
        if (aCheckbox == mCheckBoxSmooth) {
            mEditor->PathRefresh();
        }
    }
    
    
    
}
