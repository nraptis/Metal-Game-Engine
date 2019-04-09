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

EditorMenuFormationGrid::EditorMenuFormationGrid(GameFormationEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuFormationGrid";
    
    mEditor = pEditor;
    
    SetTitle("Formation Builder");
    SetScrollMode(true);
    
    mPanelGrid = new ToolMenuPanel();
    mPanelGrid->SetTitle("The Grid");
    AddSection(mPanelGrid);
    
    
    mRowGrid1 = new ToolMenuSectionRow();
    mPanelGrid->AddSection(mRowGrid1);
    
    
    mCheckBoxGridEnabled = new UICheckBox();
    mCheckBoxGridEnabled->SetText("Grid");
    mCheckBoxGridEnabled->SetTarget(&mEditor->mGridEnabled);
    mRowGrid1->AddCheckBox(mCheckBoxGridEnabled);
    
    mCheckBoxGridDisplay = new UICheckBox();
    mCheckBoxGridDisplay->SetText("Markers");
    mCheckBoxGridDisplay->SetTarget(&mEditor->mMarkersDisplay);
    mRowGrid1->AddCheckBox(mCheckBoxGridDisplay);
    
    
    
    mSegmentGridType = new UISegment();
    mSegmentGridType->SetSegmentCount(6);
    mSegmentGridType->SetTitles("RECT", "CIRC", "STAR", "TRI", "NGON1", "NGON2");
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
    
    
    mStepperCircleRingCount = new UIStepper();
    mStepperCircleRingCount->SetText("Ring Count:");
    mStepperCircleRingCount->SetTarget(&mEditor->mGridCircleRingCount);
    mPanelCircleGrid->AddSection(mStepperCircleRingCount);
    
    mStepperCircleRingSpacing = new UIStepper();
    mStepperCircleRingSpacing->SetText("Ring Spacing:");
    mStepperCircleRingSpacing->SetTarget(&mEditor->mGridCircleRingSpacing);
    mPanelCircleGrid->AddSection(mStepperCircleRingSpacing);
    
    mStepperCircleRadialCount = new UIStepper();
    mStepperCircleRadialCount->SetText("Radial Count:");
    mStepperCircleRadialCount->SetTarget(&mEditor->mGridCircleRadialCount);
    mPanelCircleGrid->AddSection(mStepperCircleRadialCount);
    
    
    
    
    
    
    mPanelNGON1Grid = new ToolMenuPanel();
    mPanelNGON1Grid->SetTitle("NGON-1");
    mPanelGrid->AddSection(mPanelNGON1Grid);
    
    
    mStepperNGON1Sides = new UIStepper();
    mStepperNGON1Sides->SetText("Sides:");
    mStepperNGON1Sides->SetTarget(&mEditor->mGridNGON1Sides);
    mPanelNGON1Grid->AddSection(mStepperNGON1Sides);
    
    mStepperNGON1RingCount = new UIStepper();
    mStepperNGON1RingCount->SetText("Ring Count:");
    mStepperNGON1RingCount->SetTarget(&mEditor->mGridNGON1RingCount);
    mPanelNGON1Grid->AddSection(mStepperNGON1RingCount);
    
    mStepperNGON1RingSpacing = new UIStepper();
    mStepperNGON1RingSpacing->SetText("Ring Spacing:");
    mStepperNGON1RingSpacing->SetTarget(&mEditor->mGridNGON1RingSpacing);
    mPanelNGON1Grid->AddSection(mStepperNGON1RingSpacing);
    
    mStepperNGON1PointSpacing = new UIStepper();
    mStepperNGON1PointSpacing->SetText("Point Spacing:");
    mStepperNGON1PointSpacing->SetTarget(&mEditor->mGridNGON1PointSpacing);
    mPanelNGON1Grid->AddSection(mStepperNGON1PointSpacing);
    
    mStepperNGON1StartRotation = new UIStepper();
    mStepperNGON1StartRotation->SetText("S-Rot:");
    mStepperNGON1StartRotation->SetTarget(&mEditor->mGridNGON1StartRotation);
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

void EditorMenuFormationGrid::Notify(void *pSender, const char *pNotification) {
    
    if (mEditor == NULL) { return; }
    
    if (pSender == mSegmentGridType) { RefreshGridPanels();mEditor->BuildGrid(); }
    
    if (pSender == mStepperRectGridWidth) { mEditor->BuildGrid(); }
    if (pSender == mStepperRectGridHeight) { mEditor->BuildGrid(); }
    if (pSender == mStepperRectGridSpacing) { mEditor->BuildGrid(); }
    
    if (pSender == mStepperCircleRingCount) { mEditor->BuildGrid(); }
    if (pSender == mStepperCircleRingSpacing) { mEditor->BuildGrid(); }
    if (pSender == mStepperCircleRadialCount) { mEditor->BuildGrid(); }
    
    if (pSender == mStepperNGON1Sides) { mEditor->BuildGrid(); }
    if (pSender == mStepperNGON1RingCount) { mEditor->BuildGrid(); }
    if (pSender == mStepperNGON1RingSpacing) { mEditor->BuildGrid(); }
    if (pSender == mStepperNGON1PointSpacing) { mEditor->BuildGrid(); }
    if (pSender == mStepperNGON1StartRotation) { mEditor->BuildGrid(); }
    
}

void EditorMenuFormationGrid::RefreshGridPanels() {
    
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
    
    if (mPanelNGON1Grid != NULL) {
        if (aGridType == FORMATION_GRID_TYPE_NGON1) {
            mPanelNGON1Grid->Activate();
        } else {
            mPanelNGON1Grid->Deactivate();
        }
    }
    
}
