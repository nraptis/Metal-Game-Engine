//
//  EditorMenuFormationGridGrid.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/7/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormationGrid.hpp"
#include "GameFormationEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuFormationGrid::EditorMenuFormationGrid(GameEditorGrid *pGrid) : ToolMenu() {
    mName = "EditorMenuFormationGrid";
    
    mGrid = pGrid;
    
    SetTitle("Grid");
    SetScrollMode(true);
    
    mPanelGrid = new ToolMenuPanel();
    mPanelGrid->SetTitle("My Grid");
    AddSection(mPanelGrid);
    
    mRowGrid1 = new ToolMenuSectionRow();
    mPanelGrid->AddSection(mRowGrid1);
    
    mCheckBoxGridEnabled = new UICheckBox();
    mCheckBoxGridEnabled->SetText("Grid");
    mCheckBoxGridEnabled->SetTarget(&mGrid->mGridEnabled);
    mRowGrid1->AddCheckBox(mCheckBoxGridEnabled);
    
    mCheckBoxGridDisplay = new UICheckBox();
    mCheckBoxGridDisplay->SetText("Markers");
    //mCheckBoxGridDisplay->SetTarget(&mGrid->mMarkersDisplay);
    mRowGrid1->AddCheckBox(mCheckBoxGridDisplay);
    
    mSegmentGridType = new UISegment();
    mSegmentGridType->SetSegmentCount(6);
    mSegmentGridType->SetTitles("RECT", "CIRC", "STAR", "TRI", "NGON1", "NGON2");
    mSegmentGridType->SetTarget(&mGrid->mGridType);
    mPanelGrid->AddSection(mSegmentGridType);
    
    mPanelRectGrid = new ToolMenuPanel();
    mPanelRectGrid->SetTitle("Rectangular");
    mPanelGrid->AddSection(mPanelRectGrid);
    
    mStepperRectGridWidth = new UIStepper();
    mStepperRectGridWidth->SetText("Grid Width:");
    mStepperRectGridWidth->SetTarget(&mGrid->mGridRectWidth);
    mPanelRectGrid->AddSection(mStepperRectGridWidth);
    
    mStepperRectGridHeight = new UIStepper();
    mStepperRectGridHeight->SetText("Grid Height:");
    mStepperRectGridHeight->SetTarget(&mGrid->mGridRectHeight);
    mPanelRectGrid->AddSection(mStepperRectGridHeight);
    
    mStepperRectGridSpacing = new UIStepper();
    mStepperRectGridSpacing->SetText("Grid Height:");
    mStepperRectGridSpacing->SetTarget(&mGrid->mGridRectSpacing);
    mPanelRectGrid->AddSection(mStepperRectGridSpacing);
    
    
    
    mPanelCircleGrid = new ToolMenuPanel();
    mPanelCircleGrid->SetTitle("Circular");
    mPanelGrid->AddSection(mPanelCircleGrid);
    
    
    mStepperCircleRingCount = new UIStepper();
    mStepperCircleRingCount->SetText("Ring Count:");
    mStepperCircleRingCount->SetTarget(&mGrid->mGridCircleRingCount);
    mPanelCircleGrid->AddSection(mStepperCircleRingCount);
    
    mStepperCircleRingSpacing = new UIStepper();
    mStepperCircleRingSpacing->SetText("Ring Spacing:");
    mStepperCircleRingSpacing->SetTarget(&mGrid->mGridCircleRingSpacing);
    mPanelCircleGrid->AddSection(mStepperCircleRingSpacing);
    
    mStepperCircleRadialCount = new UIStepper();
    mStepperCircleRadialCount->SetText("Radial Count:");
    mStepperCircleRadialCount->SetTarget(&mGrid->mGridCircleRadialCount);
    mPanelCircleGrid->AddSection(mStepperCircleRadialCount);
    
    
    
    
    
    
    
    mPanelStarGrid = new ToolMenuPanel();
    mPanelStarGrid->SetTitle("Star");
    mPanelGrid->AddSection(mPanelStarGrid);
    
    mStepperStarInnerRadius = new UIStepper();
    mStepperStarInnerRadius->SetText("Inner Rad:");
    mStepperStarInnerRadius->SetTarget(&mGrid->mGridStarInnerRadius);
    mPanelStarGrid->AddSection(mStepperStarInnerRadius);
    
    mStepperStarOuterRadius = new UIStepper();
    mStepperStarOuterRadius->SetText("Outer Rad:");
    mStepperStarOuterRadius->SetTarget(&mGrid->mGridStarOuterRadius);
    mPanelStarGrid->AddSection(mStepperStarOuterRadius);
    
    mStepperStarArmCount = new UIStepper();
    mStepperStarArmCount->SetText("Arm Count:");
    mStepperStarArmCount->SetTarget(&mGrid->mGridStarArmCount);
    mPanelStarGrid->AddSection(mStepperStarArmCount);
    
    mStepperStarLinePointCount = new UIStepper();
    mStepperStarLinePointCount->SetText("Point Count:");
    mStepperStarLinePointCount->SetTarget(&mGrid->mGridStarLinePointCount);
    mPanelStarGrid->AddSection(mStepperStarLinePointCount);
    
    mStepperStarStartRotation = new UIStepper();
    mStepperStarStartRotation->SetText("Rot Offset:");
    mStepperStarStartRotation->SetTarget(&mGrid->mGridStarStartRotation);
    mPanelStarGrid->AddSection(mStepperStarStartRotation);
    
    
    
    
    mPanelNGON1Grid = new ToolMenuPanel();
    mPanelNGON1Grid->SetTitle("NGON-1");
    mPanelGrid->AddSection(mPanelNGON1Grid);
    
    
    mStepperNGON1Sides = new UIStepper();
    mStepperNGON1Sides->SetText("Sides:");
    mStepperNGON1Sides->SetTarget(&mGrid->mGridNGON1Sides);
    mPanelNGON1Grid->AddSection(mStepperNGON1Sides);
    
    mStepperNGON1RingCount = new UIStepper();
    mStepperNGON1RingCount->SetText("Ring Count:");
    mStepperNGON1RingCount->SetTarget(&mGrid->mGridNGON1RingCount);
    mPanelNGON1Grid->AddSection(mStepperNGON1RingCount);
    
    mStepperNGON1RingSpacing = new UIStepper();
    mStepperNGON1RingSpacing->SetText("Ring Spacing:");
    mStepperNGON1RingSpacing->SetTarget(&mGrid->mGridNGON1RingSpacing);
    mPanelNGON1Grid->AddSection(mStepperNGON1RingSpacing);
    
    mStepperNGON1PointSpacing = new UIStepper();
    mStepperNGON1PointSpacing->SetText("Point Spacing:");
    mStepperNGON1PointSpacing->SetTarget(&mGrid->mGridNGON1PointSpacing);
    mPanelNGON1Grid->AddSection(mStepperNGON1PointSpacing);
    
    mStepperNGON1StartRotation = new UIStepper();
    mStepperNGON1StartRotation->SetText("S-Rot:");
    mStepperNGON1StartRotation->SetTarget(&mGrid->mGridNGON1StartRotation);
    mPanelNGON1Grid->AddSection(mStepperNGON1StartRotation);
    
    
    
    
    DeactivateCloseButton();
    RefreshGridPanels();
}

EditorMenuFormationGrid::~EditorMenuFormationGrid() {
    
}

void EditorMenuFormationGrid::Layout() {
    ToolMenu::Layout();
    
}

void EditorMenuFormationGrid::Update() {
    ToolMenu::Update();
    
    /*
     if (mCheckBoxSmooth) {
     bool aUnlink = true;
     if (mGrid->mWave != NULL) {
     aUnlink = false;
     mCheckBoxSmooth->SetTarget(&(mGrid->mWave->mPath.mSmooth));
     }
     if (aUnlink) {
     mCheckBoxSmooth->SetTarget(NULL);
     }
     }
     */
    
}
//

void EditorMenuFormationGrid::Notify(void *pSender, const char *pNotification) {
    
    if (mGrid == NULL) { return; }
    
    if (pSender == mSegmentGridType) { RefreshGridPanels();mGrid->BuildGrid(); }
    
    if (pSender == mStepperRectGridWidth) { mGrid->BuildGrid(); }
    if (pSender == mStepperRectGridHeight) { mGrid->BuildGrid(); }
    if (pSender == mStepperRectGridSpacing) { mGrid->BuildGrid(); }
    
    if (pSender == mStepperCircleRingCount) { mGrid->BuildGrid(); }
    if (pSender == mStepperCircleRingSpacing) { mGrid->BuildGrid(); }
    if (pSender == mStepperCircleRadialCount) { mGrid->BuildGrid(); }
    
    if (pSender == mStepperStarInnerRadius) { mGrid->BuildGrid(); }
    if (pSender == mStepperStarOuterRadius) { mGrid->BuildGrid(); }
    if (pSender == mStepperStarLinePointCount) { mGrid->BuildGrid(); }
    if (pSender == mStepperStarArmCount) { mGrid->BuildGrid(); }
    if (pSender == mStepperStarStartRotation) { mGrid->BuildGrid(); }
    
    if (pSender == mStepperNGON1Sides) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON1RingCount) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON1RingSpacing) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON1PointSpacing) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON1StartRotation) { mGrid->BuildGrid(); }
    
}

void EditorMenuFormationGrid::RefreshGridPanels() {
    
    if (mGrid == NULL) { return; }
    
    int aGridType = mGrid->mGridType;
    
    if (mPanelRectGrid != NULL) {
        if (aGridType == SNAP_GRID_TYPE_RECT) {
            
            mPanelRectGrid->Activate();
        } else {
            mPanelRectGrid->Deactivate();
        }
    }
    
    if (mPanelCircleGrid != NULL) {
        if (aGridType == SNAP_GRID_TYPE_CIRCLE) {
            mPanelCircleGrid->Activate();
        } else {
            mPanelCircleGrid->Deactivate();
        }
    }
    
    if (mPanelStarGrid != NULL) {
        if (aGridType == SNAP_GRID_TYPE_STAR) {
            mPanelStarGrid->Activate();
        } else {
            mPanelStarGrid->Deactivate();
        }
    }
    
    if (aGridType == SNAP_GRID_TYPE_TRIANGLE) {
        
    } else {
        
    }
    
    if (mPanelNGON1Grid != NULL) {
        if (aGridType == SNAP_GRID_TYPE_NGON1) {
            mPanelNGON1Grid->Activate();
        } else {
            mPanelNGON1Grid->Deactivate();
        }
    }
    
}
