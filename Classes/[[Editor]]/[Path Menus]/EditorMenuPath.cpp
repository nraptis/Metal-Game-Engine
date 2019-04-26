//
//  EditorMenuPathMain.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPath.hpp"
#include "GamePathEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuPath::EditorMenuPath(GamePathEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPath";
    
    mEditor = pEditor;
    
    SetTitle("Path Tools");
    SetScrollMode(true);
    
    mPanelEditor = new ToolMenuPanel();
    mPanelEditor->SetTitle("Edit Paths");
    AddSection(mPanelEditor);
    
    mSegmentMode = new UISegment();
    mSegmentMode->SetSegmentCount(3);
    mSegmentMode->SetTitles("Add Point", "Move Point", "Select Point");
    mSegmentMode->SetTarget(&mEditor->mPathMode);
    mPanelEditor->AddSection(mSegmentMode);
    
    mRowVisuals = new ToolMenuSectionRow();
    mPanelEditor->AddSection(mRowVisuals);
    
    mCheckBoxSmooth = new UICheckBox();
    mCheckBoxSmooth->SetText("Smooth");
    mRowVisuals->AddCheckBox(mCheckBoxSmooth);
    
    
    mCheckBoxClosed = new UICheckBox();
    mCheckBoxClosed->SetText("Closed");
    mRowVisuals->AddCheckBox(mCheckBoxClosed);
    
    
    
    
    
    mPointsPanel = new ToolMenuPanel();
    mPointsPanel->SetTitle("Points");
    AddSection(mPointsPanel);
    
    mStepperWait = new UIStepper();
    mStepperWait->SetText("Wait:");
    mPointsPanel->AddSection(mStepperWait);
    
    
    mStepperChamfer = new UIStepper();
    mStepperChamfer->SetText("Chamfer:");
    mPointsPanel->AddSection(mStepperChamfer);
    
    
    mStepperDecel = new UIStepper();
    mStepperDecel->SetText("Decel:");
    mPointsPanel->AddSection(mStepperDecel);
    
    mStepperAccel = new UIStepper();
    mStepperAccel->SetText("Accel:");
    mPointsPanel->AddSection(mStepperAccel);
    
    
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
    
}

void EditorMenuPath::Layout() {
    ToolMenu::Layout();
}

void EditorMenuPath::Update() {
    ToolMenu::Update();
    
    
    
    if (mCheckBoxSmooth != NULL) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            aUnlink = false;
            mCheckBoxSmooth->SetTarget(&(mEditor->mPath->mSmooth));
        }
        if (aUnlink) {
            mCheckBoxSmooth->SetTarget(NULL);
        }
    }
    
    
    if (mCheckBoxClosed != NULL) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            aUnlink = false;
            mCheckBoxClosed->SetTarget(&(mEditor->mPath->mClosed));
        }
        if (aUnlink) {
            mCheckBoxClosed->SetTarget(NULL);
        }
    }
    
    
    if (mStepperWait != NULL) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mEditor->mPath->mNodeList.Fetch(mEditor->mPath->mSelectedIndex);
            if (aNode) {
                aUnlink = false;
                mStepperWait->SetTarget(&(aNode->mWaitTimer));
            }
        }
        if (aUnlink) {
            mStepperWait->SetTarget(NULL);
        }
    }
    
    if (mStepperChamfer != NULL) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mEditor->mPath->mNodeList.Fetch(mEditor->mPath->mSelectedIndex);
            if (aNode) {
                aUnlink = false;
                mStepperChamfer->SetTarget(&(aNode->mChamferSize));
            }
        }
        if (aUnlink) {
            mStepperChamfer->SetTarget(NULL);
        }
    }
    
    if (mStepperDecel != NULL) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mEditor->mPath->mNodeList.Fetch(mEditor->mPath->mSelectedIndex);
            if (aNode) {
                aUnlink = false;
                mStepperDecel->SetTarget(&(aNode->mDecelDistance));
            }
        }
        if (aUnlink) {
            mStepperDecel->SetTarget(NULL);
        }
    }
    
    if (mStepperAccel != NULL) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            LevelPathNodeBlueprint *aNode = (LevelPathNodeBlueprint *)mEditor->mPath->mNodeList.Fetch(mEditor->mPath->mSelectedIndex);
            if (aNode) {
                aUnlink = false;
                mStepperAccel->SetTarget(&(aNode->mAccelDistance));
            }
        }
        if (aUnlink) {
            mStepperAccel->SetTarget(NULL);
        }
    }
    
    
}

void EditorMenuPath::Notify(void *pSender, const char *pNotification) {
    
    if (pSender == mButtonDeletePoint) { mEditor->PathDeletePoint(); }
    if (pSender == mButtonBreakXConstraint) { mEditor->ConstraintXToType(X_CONSTRAINT_NONE); }
    if (pSender == mButtonBreakYConstraint) { mEditor->ConstraintYToType(Y_CONSTRAINT_NONE); }
    if (pSender == mButtonSnapPrevX) { mEditor->ConstraintXToPrev(); }
    if (pSender == mButtonSnapNextX) { mEditor->ConstraintXToNext(); }
    if (pSender == mButtonSnapPrevY) { mEditor->ConstraintYToPrev(); }
    if (pSender == mButtonSnapNextY) { mEditor->ConstraintYToNext(); }
    if (pSender == mStepperWait) { mEditor->PathRefresh(); }
    if (pSender == mStepperChamfer) { mEditor->PathRefresh(); }
    if (pSender == mCheckBoxSmooth) { mEditor->PathRefresh(); }
    if (pSender == mCheckBoxClosed) { mEditor->PathRefresh(); }
    
    if (pSender == mStepperAccel) { mEditor->PathRefresh(); }
    if (pSender == mStepperDecel) { mEditor->PathRefresh(); }
    
    
    
    
    
}
