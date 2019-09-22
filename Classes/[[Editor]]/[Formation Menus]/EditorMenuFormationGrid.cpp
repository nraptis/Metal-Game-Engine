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
    
    
    mStepperGridOffsetX = new UIStepper();
    mStepperGridOffsetX->SetText("Offset X:");
    mStepperGridOffsetX->SetTarget(&mGrid->mOffsetX);
    mPanelGrid->AddSection(mStepperGridOffsetX);
    
    mStepperGridOffsetY = new UIStepper();
    mStepperGridOffsetY->SetText("Offset Y:");
    mStepperGridOffsetY->SetTarget(&mGrid->mOffsetY);
    mPanelGrid->AddSection(mStepperGridOffsetY);
    
    
    
    
    mSegmentGridType = new UISegment();
    mSegmentGridType->SetSegmentCount(8);
    mSegmentGridType->SetTitles("RCT", "CRC", "STR", "ARC", "NGO1", "NGO2", "TRP1", "TRP2");
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
    
    mStepperRectGridSpacingH = new UIStepper();
    mStepperRectGridSpacingH->SetText("Spacing H:");
    mStepperRectGridSpacingH->SetTarget(&mGrid->mGridRectSpacingH);
    mPanelRectGrid->AddSection(mStepperRectGridSpacingH);
    
    mStepperRectGridSpacingV = new UIStepper();
    mStepperRectGridSpacingV->SetText("Spacing V:");
    mStepperRectGridSpacingV->SetTarget(&mGrid->mGridRectSpacingV);
    mPanelRectGrid->AddSection(mStepperRectGridSpacingV);
    
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
    
    
    
    
    
    
    
    
    
    mPanelNGON2Grid = new ToolMenuPanel();
    mPanelNGON2Grid->SetTitle("NGON-2");
    mPanelGrid->AddSection(mPanelNGON2Grid);
    
    
    mStepperNGON2Sides = new UIStepper();
    mStepperNGON2Sides->SetText("Sides:");
    mStepperNGON2Sides->SetTarget(&mGrid->mGridNGON2Sides);
    mPanelNGON2Grid->AddSection(mStepperNGON2Sides);
    
    mStepperNGON2Radius = new UIStepper();
    mStepperNGON2Radius->SetText("Radius:");
    mStepperNGON2Radius->SetTarget(&mGrid->mGridNGON2Radius);
    mPanelNGON2Grid->AddSection(mStepperNGON2Radius);
    
    mRowNGON21 = new ToolMenuSectionRow();
    mPanelNGON2Grid->AddSection(mRowNGON21);
    
    mCheckBoxNGON2Stagger = new UICheckBox();
    mCheckBoxNGON2Stagger->SetText("Stagger");
    mCheckBoxNGON2Stagger->SetTarget(&mGrid->mGridNGON2ScanLineStagger);
    mRowNGON21->AddCheckBox(mCheckBoxNGON2Stagger);
    
    
    mCheckBoxNGON2StaggerOdd = new UICheckBox();
    mCheckBoxNGON2StaggerOdd->SetText("Odd");
    mCheckBoxNGON2StaggerOdd->SetTarget(&mGrid->mGridNGON2ScanLineStaggerOdd);
    mRowNGON21->AddCheckBox(mCheckBoxNGON2StaggerOdd);
    
    
    
    mStepperNGON2ScanLineOffsetY = new UIStepper();
    mStepperNGON2ScanLineOffsetY->SetText("Scan-Off-Y:");
    mStepperNGON2ScanLineOffsetY->SetTarget(&mGrid->mGridNGON2ScanLineOffsetY);
    mPanelNGON2Grid->AddSection(mStepperNGON2ScanLineOffsetY);
    
    
    mStepperNGON2ScanLineSpacingH = new UIStepper();
    mStepperNGON2ScanLineSpacingH->SetText("SPC-V:");
    mStepperNGON2ScanLineSpacingH->SetTarget(&mGrid->mGridNGON2ScanLineSpacingV);
    mPanelNGON2Grid->AddSection(mStepperNGON2ScanLineSpacingH);
    
    mStepperNGON2ScanLineSpacingV = new UIStepper();
    mStepperNGON2ScanLineSpacingV->SetText("SPC-H:");
    mStepperNGON2ScanLineSpacingV->SetTarget(&mGrid->mGridNGON2ScanLineSpacingH);
    mPanelNGON2Grid->AddSection(mStepperNGON2ScanLineSpacingV);
    
    mStepperNGON2StartRotation = new UIStepper();
    mStepperNGON2StartRotation->SetText("Rot-Off:");
    mStepperNGON2StartRotation->SetTarget(&mGrid->mGridNGON2StartRotation);
    mPanelNGON2Grid->AddSection(mStepperNGON2StartRotation);
    
    
    
    
    mPanelTRAP1Grid = new ToolMenuPanel();
    mPanelTRAP1Grid->SetTitle("TRAP-1");
    mPanelGrid->AddSection(mPanelTRAP1Grid);
    
    
    mStepperTRAP1TopSize = new UIStepper();
    mStepperTRAP1TopSize->SetText("Top Size:");
    mStepperTRAP1TopSize->SetTarget(&mGrid->mGridTRAP1TopSize);
    mPanelTRAP1Grid->AddSection(mStepperTRAP1TopSize);
    
    mStepperTRAP1BottomSize = new UIStepper();
    mStepperTRAP1BottomSize->SetText("Btm Size:");
    mStepperTRAP1BottomSize->SetTarget(&mGrid->mGridTRAP1BottomSize);
    mPanelTRAP1Grid->AddSection(mStepperTRAP1BottomSize);
    
    mStepperTRAP1Height = new UIStepper();
    mStepperTRAP1Height->SetText("Height:");
    mStepperTRAP1Height->SetTarget(&mGrid->mGridTRAP1Height);
    mPanelTRAP1Grid->AddSection(mStepperTRAP1Height);
    
    mStepperTRAP1CountH = new UIStepper();
    mStepperTRAP1CountH->SetText("H-Count:");
    mStepperTRAP1CountH->SetTarget(&mGrid->mGridTRAP1CountH);
    mPanelTRAP1Grid->AddSection(mStepperTRAP1CountH);
    
    mStepperTRAP1CountV = new UIStepper();
    mStepperTRAP1CountV->SetText("V-Count:");
    mStepperTRAP1CountV->SetTarget(&mGrid->mGridTRAP1CountV);
    mPanelTRAP1Grid->AddSection(mStepperTRAP1CountV);
    
    mStepperTRAP1StartRotation = new UIStepper();
    mStepperTRAP1StartRotation->SetText("S-Rot:");
    mStepperTRAP1StartRotation->SetTarget(&mGrid->mGridTRAP1StartRotation);
    mPanelTRAP1Grid->AddSection(mStepperTRAP1StartRotation);
    
    
    
    
    
    
    
    
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
    if (pSender == mStepperGridOffsetX) { RefreshGridPanels();mGrid->BuildGrid(); }
    if (pSender == mStepperGridOffsetY) { RefreshGridPanels();mGrid->BuildGrid(); }
    
    
    
    
    if (pSender == mStepperRectGridWidth) { mGrid->BuildGrid(); }
    if (pSender == mStepperRectGridHeight) { mGrid->BuildGrid(); }
    if (pSender == mStepperRectGridSpacingH) { mGrid->BuildGrid(); }
    if (pSender == mStepperRectGridSpacingV) { mGrid->BuildGrid(); }
    
    
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
    
    
    
    
    if (pSender == mStepperNGON2Sides) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON2Radius) { mGrid->BuildGrid(); }
    if (pSender == mCheckBoxNGON2Stagger) { mGrid->BuildGrid(); }
    if (pSender == mCheckBoxNGON2StaggerOdd) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON2ScanLineOffsetY) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON2ScanLineSpacingH) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON2ScanLineSpacingV) { mGrid->BuildGrid(); }
    if (pSender == mStepperNGON2StartRotation) { mGrid->BuildGrid(); }
    
    
    
    if (pSender == mStepperTRAP1TopSize) { mGrid->BuildGrid(); }
    if (pSender == mStepperTRAP1BottomSize) { mGrid->BuildGrid(); }
    if (pSender == mStepperTRAP1Height) { mGrid->BuildGrid(); }
    if (pSender == mStepperTRAP1CountH) { mGrid->BuildGrid(); }
    if (pSender == mStepperTRAP1CountV) { mGrid->BuildGrid(); }
    if (pSender == mStepperTRAP1StartRotation) { mGrid->BuildGrid(); }
    
    
    
    
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
    
    if (aGridType == SNAP_GRID_TYPE_ARC) {
        
    } else {
        
    }
    
    if (mPanelNGON1Grid != NULL) {
        if (aGridType == SNAP_GRID_TYPE_NGON1) {
            mPanelNGON1Grid->Activate();
        } else {
            mPanelNGON1Grid->Deactivate();
        }
    }
    
    if (mPanelNGON2Grid != NULL) {
        if (aGridType == SNAP_GRID_TYPE_NGON2) {
            mPanelNGON2Grid->Activate();
        } else {
            mPanelNGON2Grid->Deactivate();
        }
    }
    
    
    
    
    if (mPanelTRAP1Grid != NULL) {
        if (aGridType == SNAP_GRID_TYPE_TRAP1) {
            mPanelTRAP1Grid->Activate();
        } else {
            mPanelTRAP1Grid->Deactivate();
        }
    }
}
