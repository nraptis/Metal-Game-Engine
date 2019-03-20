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
    mCheckBoxPreview->SetText("Preview");
    mRowVisuals->AddCheckBox(mCheckBoxPreview);
    



    
    mPointsPanel = new ToolMenuPanel();
    mPointsPanel->SetTitle("Points");
    AddSection(mPointsPanel);
    
    
    mStepperWait = new UIStepper();
    mStepperWait->SetText("Wait:");
    mPointsPanel->AddSection(mStepperWait);
    gNotify.Register(this, mStepperWait, "stepper");
    
    
    
    
    mRowPointWait = new ToolMenuSectionRow();
    mPointsPanel->AddSection(mRowPointWait);
    
    mTextBoxWait = new UITextBox();
    mTextBoxWait->SetText("1 2 3 4 5 6");
    
    mRowPointWait->AddTextBox(mTextBoxWait);
    
    
    mButtonResetWait = new UIButton();
    mButtonResetWait->SetText("RWW Reset");
    mRowPointWait->AddButton(mButtonResetWait);
    
    
    
    mRowPointOptions = new ToolMenuSectionRow();
    mPointsPanel->AddSection(mRowPointOptions);
    
    mCheckBoxChamfer = new UICheckBox();
    mCheckBoxChamfer->SetText("Chamfer");
    mRowPointOptions->AddCheckBox(mCheckBoxChamfer);
    
    mButtonDeletePoint = new UIButton();
    mButtonDeletePoint->SetText("Delete Point");
    mRowPointOptions->AddButton(mButtonDeletePoint);
    
    
    mConstraintPanel = new ToolMenuPanel();
    mConstraintPanel->SetTitle("Constraints");
    mPointsPanel->AddSection(mConstraintPanel);
    
    
    mRowSnapPoints = new ToolMenuSectionRow();
    mConstraintPanel->AddSection(mRowSnapPoints);

    
    
    mCheckBoxSnapX = new UICheckBox();
    mCheckBoxSnapX->SetText("Snap X To...");
    mCheckBoxSnapX->SetTarget(&mEditor->mConstrainXToPoint);
    mRowSnapPoints->AddCheckBox(mCheckBoxSnapX);
    
    mCheckBoxSnapY = new UICheckBox();
    mCheckBoxSnapY->SetText("Snap Y To...");
    mCheckBoxSnapY->SetTarget(&mEditor->mConstrainYToPoint);
    mRowSnapPoints->AddCheckBox(mCheckBoxSnapY);
    
    
    mRowSnapX1 = new ToolMenuSectionRow();
    mConstraintPanel->AddSection(mRowSnapX1);
    
    mButtonBreakXConstraint = new UIButton();
    mButtonBreakXConstraint->SetText("[X]");
    mRowSnapX1->AddButton(mButtonBreakXConstraint);
    
    mButtonSnapXSpawnLeft = new UIButton();
    mButtonSnapXSpawnLeft->SetText("LLL");
    mRowSnapX1->AddButton(mButtonSnapXSpawnLeft);
    
    mButtonSnapXPeekLeft = new UIButton();
    mButtonSnapXPeekLeft->SetText("LL");
    mRowSnapX1->AddButton(mButtonSnapXPeekLeft);
    
    mButtonSnapXQuarterLeft = new UIButton();
    mButtonSnapXQuarterLeft->SetText("L");
    mRowSnapX1->AddButton(mButtonSnapXQuarterLeft);
    
    mRowSnapX2 = new ToolMenuSectionRow();
    mConstraintPanel->AddSection(mRowSnapX2);
    
    mButtonSnapXCenter = new UIButton();
    mButtonSnapXCenter->SetText("[C]");
    mRowSnapX2->AddButton(mButtonSnapXCenter);
    
    mButtonSnapXQuarterRight = new UIButton();
    mButtonSnapXQuarterRight->SetText("R");
    mRowSnapX2->AddButton(mButtonSnapXQuarterRight);
    
    mButtonSnapXPeekRight = new UIButton();
    mButtonSnapXPeekRight->SetText("RR");
    mRowSnapX2->AddButton(mButtonSnapXPeekRight);
    
    mButtonSnapXSpawnRight = new UIButton();
    mButtonSnapXSpawnRight->SetText("RRR");
    mRowSnapX2->AddButton(mButtonSnapXSpawnRight);
    
    
    
    
    
    
    
    
    
    
    
    
    mRowSnapY1 = new ToolMenuSectionRow();
    mConstraintPanel->AddSection(mRowSnapY1);
    
    mButtonBreakYConstraint = new UIButton();
    mButtonBreakYConstraint->SetText("[X]");
    mRowSnapY1->AddButton(mButtonBreakYConstraint);
    
    mButtonSnapYSpawnTop = new UIButton();
    mButtonSnapYSpawnTop->SetText("UUU");
    mRowSnapY1->AddButton(mButtonSnapYSpawnTop);
    
    mButtonSnapYPeekTop = new UIButton();
    mButtonSnapYPeekTop->SetText("UU");
    mRowSnapY1->AddButton(mButtonSnapYPeekTop);
    
    mButtonSnapYQuarterTop = new UIButton();
    mButtonSnapYQuarterTop->SetText("U");
    mRowSnapY1->AddButton(mButtonSnapYQuarterTop);
    
    mRowSnapY2 = new ToolMenuSectionRow();
    mConstraintPanel->AddSection(mRowSnapY2);
    
    mButtonSnapYCenter = new UIButton();
    mButtonSnapYCenter->SetText("[C]");
    mRowSnapY2->AddButton(mButtonSnapYCenter);
    
    mButtonSnapYQuarterBottom = new UIButton();
    mButtonSnapYQuarterBottom->SetText("D");
    mRowSnapY2->AddButton(mButtonSnapYQuarterBottom);
    
    
    mButtonSnapYBottom = new UIButton();
    mButtonSnapYBottom->SetText("DDD");
    mRowSnapY2->AddButton(mButtonSnapYBottom);

    
    
    DeactivateCloseButton();
}

EditorMenuPath::~EditorMenuPath() {
    
}

void EditorMenuPath::Layout() {
    ToolMenu::Layout();
    
}

void EditorMenuPath::Update() {
    ToolMenu::Update();
  
    if (mCheckBoxChamfer) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mEditor->mPath->mNodeList.Fetch(mEditor->mPath->mSelectedIndex);
            if (aNode) {
                aUnlink = false;
                mCheckBoxChamfer->SetTarget(&(aNode->mChamfer));
            }
        }
        if (aUnlink) {
            mCheckBoxChamfer->SetTarget(NULL);
        }
    }
    
    if (mCheckBoxSmooth) {
        bool aUnlink = true;
        if (mEditor->mPath != NULL) {
            aUnlink = false;
            mCheckBoxSmooth->SetTarget(&(mEditor->mPath->mSmooth));
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
    
    
}
//

void EditorMenuPath::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
        if (pSender == mButtonDeletePoint) { mEditor->PathDeletePoint(); }
        
        if (pSender == mButtonBreakXConstraint) { mEditor->ConstraintXToType(X_CONSTRAINT_NONE); }
        if (pSender == mButtonSnapXSpawnLeft) { mEditor->ConstraintXToType(X_CONSTRAINT_LEFT_SPAWN); }
        if (pSender == mButtonSnapXPeekLeft) { mEditor->ConstraintXToType(X_CONSTRAINT_LEFT_PEEK); }
        if (pSender == mButtonSnapXQuarterLeft) { mEditor->ConstraintXToType(X_CONSTRAINT_LEFT_QUARTER); }
        if (pSender == mButtonSnapXCenter) { mEditor->ConstraintXToType(X_CONSTRAINT_CENTER); }
        if (pSender == mButtonSnapXQuarterRight) { mEditor->ConstraintXToType(X_CONSTRAINT_RIGHT_QUARTER); }
        if (pSender == mButtonSnapXPeekRight) { mEditor->ConstraintXToType(X_CONSTRAINT_RIGHT_PEEK); }
        if (pSender == mButtonSnapXSpawnRight) { mEditor->ConstraintXToType(X_CONSTRAINT_RIGHT_SPAWN); }
        
        if (pSender == mButtonBreakYConstraint) { mEditor->ConstraintYToType(Y_CONSTRAINT_NONE); }
        if (pSender == mButtonSnapYSpawnTop) { mEditor->ConstraintYToType(Y_CONSTRAINT_TOP_SPAWN); }
        if (pSender == mButtonSnapYQuarterTop) { mEditor->ConstraintYToType(Y_CONSTRAINT_TOP_QUARTER); }
        if (pSender == mButtonSnapYPeekTop) { mEditor->ConstraintYToType(Y_CONSTRAINT_TOP_PEEK); }
        if (pSender == mButtonSnapYCenter) { mEditor->ConstraintYToType(Y_CONSTRAINT_CENTER); }
        if (pSender == mButtonSnapYQuarterBottom) { mEditor->ConstraintYToType(Y_CONSTRAINT_BOTTOM_QUARTER); }
        if (pSender == mButtonSnapYBottom) { mEditor->ConstraintYToType(Y_CONSTRAINT_BOTTOM); }
    }
    
    if (FString(pNotification) == "stepper") {
        UIStepper *aStepper = (UIStepper *)pSender;
        if (aStepper == mStepperWait) {
            mEditor->PathRefresh();
        }
        
    }
    
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
    
    if (FString(pNotification) == "checkbox") {
        UICheckBox *aCheckbox = (UICheckBox *)pSender;
        if (aCheckbox == mCheckBoxSmooth) {
            mEditor->mPath->Build();
        }
        if (aCheckbox == mCheckBoxChamfer) {
            mEditor->mPath->Build();
        }
        
        
    }
    
    
    
}
