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
    
    mPanelMain = new ToolMenuPanel();
    mPanelMain->SetTitle("Control");
    AddSection(mPanelMain);
    
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonSaveFormation = new UIButton();
    mButtonSaveFormation->SetText("Save...");
    mRowMain1->AddButton(mButtonSaveFormation);
    
    mButtonLoadFormation = new UIButton();
    mButtonLoadFormation->SetText("Load...");
    mRowMain1->AddButton(mButtonLoadFormation);
    
    mButtonPrintFormation = new UIButton();
    mButtonPrintFormation->SetText("Print");
    mRowMain1->AddButton(mButtonPrintFormation);
    
    mSegmentMode = new UISegment();
    mSegmentMode->SetSegmentCount(3);
    mSegmentMode->SetTitles("Add Point", "Move Point", "Select Point");
    mSegmentMode->SetTarget(&mEditor->mFormationMode);
    mPanelMain->AddSection(mSegmentMode);
    
    
    mSliderRotation = new UISlider();
    mSliderRotation->SetText("Rotate:");
    if (mEditor) {
        mSliderRotation->SetTarget(&(mEditor->mFormation.mRotation));
    }
    mSliderRotation->SetRange(0.0f, 360.0f);
    mPanelMain->AddSection(mSliderRotation);
    
    
    
    
    mPanelNodes = new ToolMenuPanel();
    mPanelNodes->SetTitle("Nodes");
    AddSection(mPanelNodes);
    
    
    mRowNodes1 = new ToolMenuSectionRow();
    mPanelNodes->AddSection(mRowNodes1);
    
    mButtonDeleteNode = new UIButton();
    mButtonDeleteNode->SetText("Delete Node");
    mRowNodes1->AddButton(mButtonDeleteNode);
    
    
    //mRowNodes2 = new ToolMenuSectionRow();
    //mPanelNodes->AddSection(mRowNodes2);
    
    //mRowNodes3 = new ToolMenuSectionRow();
    //mPanelNodes->AddSection(mRowNodes3);
    
    
    

    mPanelGrid = new ToolMenuPanel();
    mPanelGrid->SetTitle("The Grid");
    AddSection(mPanelGrid);
    
    
    mSegmentGridType = new UISegment();
    mSegmentGridType->SetSegmentCount(6);
    mSegmentGridType->SetTitles("RECT", "CIRC", "STAR", "TRI", "ROUND", "NGON");
    mSegmentGridType->SetTarget(&mEditor->mGridType);
    mPanelGrid->AddSection(mSegmentGridType);
    
    

    
    
    mPanelRectGrid = new ToolMenuPanel();
    mPanelRectGrid->SetTitle("Rectangular");
    mPanelGrid->AddSection(mPanelRectGrid);
    
    
    mStepperRectGridWidth = new UIStepper();
    mStepperRectGridWidth->SetText("Grid Width:");
    mStepperRectGridWidth->SetTarget(&mEditor->mGridRectWidth);
    mPanelRectGrid->AddSection(mStepperRectGridWidth);
    
    mStepperRectGridHeight = new UIStepper();
    mStepperRectGridHeight->SetText("Grid Height:");
    mStepperRectGridHeight->SetTarget(&mEditor->mGridRectHeight);
    mPanelRectGrid->AddSection(mStepperRectGridHeight);
    
    mStepperRectGridSpacing = new UIStepper();
    mStepperRectGridSpacing->SetText("Grid Height:");
    mStepperRectGridSpacing->SetTarget(&mEditor->mGridRectSpacing);
    mPanelRectGrid->AddSection(mStepperRectGridSpacing);
    

    
    mPanelCircleGrid = new ToolMenuPanel();
    mPanelCircleGrid->SetTitle("Circular");
    mPanelGrid->AddSection(mPanelCircleGrid);
    
    
    mStepperCircleGridCount = new UIStepper();
    mStepperCircleGridCount->SetText("Grid Width:");
    mStepperCircleGridCount->SetTarget(&mEditor->mGridCircleCount);
    mPanelCircleGrid->AddSection(mStepperCircleGridCount);
    
    mStepperCircleRadius = new UIStepper();
    mStepperCircleRadius->SetText("Grid Width:");
    mStepperCircleRadius->SetTarget(&mEditor->mGridCircleRadius);
    mPanelCircleGrid->AddSection(mStepperCircleRadius);
    

    
    
    
    
    mPanelTestBottomBuffer = new ToolMenuPanel();
    mPanelTestBottomBuffer->SetTitle("Test Content");
    AddSection(mPanelTestBottomBuffer);
    
    mTestBufferRow1 = new ToolMenuSectionRow();
    mPanelTestBottomBuffer->AddSection(mTestBufferRow1);
    
    mButtonCreep2 = new UIButton();
    mButtonCreep2->SetText("T-1000");
    mTestBufferRow1->AddButton(mButtonCreep2);
    
    mButtonCreep1 = new UIButton();
    mButtonCreep1->SetText("T-2000");
    mTestBufferRow1->AddButton(mButtonCreep1);
    
    
    mTestBufferRow2 = new ToolMenuSectionRow();
    mPanelTestBottomBuffer->AddSection(mTestBufferRow2);
    

    mButtonCreep3 = new UIButton();
    mButtonCreep3->SetText("T-3000");
    mTestBufferRow2->AddButton(mButtonCreep3);
    
    
    
    /*
    mRowVisuals = new ToolMenuSectionRow();
    mPanelEditor->AddSection(mRowVisuals);
    
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
     
    */
    
    DeactivateCloseButton();
    RefreshGridPanels();
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
    
    if (pSender == mButtonDeleteNode) { mEditor->DeleteNode(); }
    
    if (pSender == mButtonPrintFormation) { mEditor->Print(); }
    if (pSender == mButtonSaveFormation) { mEditor->Save(); }
    if (pSender == mButtonLoadFormation) { mEditor->Load(); }
    
    
    if (pSender == mSliderRotation) { mEditor->Refresh(); }
    
    
    if (pSender == mSegmentGridType) { RefreshGridPanels(); }
    
    
    

}

void EditorMenuFormation::RefreshGridPanels() {
    
    if (mEditor == NULL) { return; }
    
    int aGridType = mEditor->mGridType;
    
    if (mPanelRectGrid != NULL) {
        if (aGridType == FORMATION_GRID_TYPE_RECT) {
            
            mPanelRectGrid->Activate();
        } else {
            mPanelRectGrid->Deactivate();
        }
    }
    
    if (mPanelCircleGrid != NULL) {
        if (aGridType == FORMATION_GRID_TYPE_CIRCLE) {
            
            mPanelCircleGrid->Activate();
        } else {
            mPanelCircleGrid->Deactivate();
        }
    }
    
    if (aGridType == FORMATION_GRID_TYPE_STAR) {
        
    } else {
        
    }
    
    
    if (aGridType == FORMATION_GRID_TYPE_TRIANGLE) {
        
    } else {
        
    }
    
    
    if (aGridType == FORMATION_GRID_TYPE_ROUNDED_RECT) {
        
    } else {
        
    }
    
    if (aGridType == FORMATION_GRID_TYPE_N_GON) {
        
    } else {
        
    }
    
}
