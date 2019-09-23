//
//  EditorMenuFormationGridGrid.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/7/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuFormationGridGrid_hpp
#define EditorMenuFormationGridGrid_hpp

#include "ToolMenu.hpp"
#include "GameEditorGrid.hpp"

class GameFormationEditor;
class EditorMenuFormationGrid : public ToolMenu {
public:
    EditorMenuFormationGrid(GameEditorGrid *pGrid);
    virtual ~EditorMenuFormationGrid();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameEditorGrid                          *mGrid;
    
    
    ToolMenuPanel                           *mPanelGrid;
    UISegment                               *mSegmentGridType;
    
    ToolMenuPanel                           *mPanelRectGrid;
    
    ToolMenuSectionRow                      *mRowGrid1;
    UICheckBox                              *mCheckBoxGridEnabled;
    UICheckBox                              *mCheckBoxGridDisplay;
    UIStepper                               *mStepperGridOffsetX;
    UIStepper                               *mStepperGridOffsetY;
    
    UIStepper                               *mStepperRectGridWidth;
    UIStepper                               *mStepperRectGridHeight;
    UIStepper                               *mStepperRectGridSpacingH;
    UIStepper                               *mStepperRectGridSpacingV;
    
    
    ToolMenuPanel                           *mPanelCircleGrid;
    UIStepper                               *mStepperCircleRingCount;
    UIStepper                               *mStepperCircleRingSpacing;
    UIStepper                               *mStepperCircleRadialCount;
    
    
    ToolMenuPanel                           *mPanelStarGrid;
    UIStepper                               *mStepperStarInnerRadius;
    UIStepper                               *mStepperStarOuterRadius;
    UIStepper                               *mStepperStarLinePointCount;
    UIStepper                               *mStepperStarArmCount;
    UIStepper                               *mStepperStarStartRotation;
    
    
    ToolMenuPanel                           *mPanelNGON1Grid;
    UIStepper                               *mStepperNGON1Sides;
    UIStepper                               *mStepperNGON1RingCount;
    UIStepper                               *mStepperNGON1RingSpacing;
    UIStepper                               *mStepperNGON1PointSpacing;
    UIStepper                               *mStepperNGON1StartRotation;
    
    
    
    
    ToolMenuPanel                           *mPanelNGON2Grid;
    UIStepper                               *mStepperNGON2Sides;
    UIStepper                               *mStepperNGON2Radius;
    ToolMenuSectionRow                      *mRowNGON21;
    UICheckBox                              *mCheckBoxNGON2Stagger;
    UICheckBox                              *mCheckBoxNGON2StaggerOdd;
    UIStepper                               *mStepperNGON2ScanLineOffsetY;
    UIStepper                               *mStepperNGON2ScanLineSpacingH;
    UIStepper                               *mStepperNGON2ScanLineSpacingV;
    UIStepper                               *mStepperNGON2StartRotation;
    
    
    
    ToolMenuPanel                           *mPanelTRAP1Grid;
    UIStepper                               *mStepperTRAP1TopSize;
    UIStepper                               *mStepperTRAP1BottomSize;
    UIStepper                               *mStepperTRAP1Height;
    UIStepper                               *mStepperTRAP1CountH;
    UIStepper                               *mStepperTRAP1CountV;
    UIStepper                               *mStepperTRAP1StartRotation;
    
    
    
    ToolMenuPanel                           *mPanelTRAP2Grid;
    UIStepper                               *mStepperTRAP2TopSize;
    UIStepper                               *mStepperTRAP2BottomSize;
    UIStepper                               *mStepperTRAP2Height;
    UIStepper                               *mStepperTRAP2ScanLineOffsetY;
    UIStepper                               *mStepperTRAP2ScanLineSpacingH;
    UIStepper                               *mStepperTRAP2ScanLineSpacingV;
    ToolMenuSectionRow                      *mRowTRAP21;
    UICheckBox                              *mCheckBoxTRAP2Stagger;
    UICheckBox                              *mCheckBoxTRAP2StaggerOdd;
    
    
    
    
    
    ToolMenuPanel                           *mPanelArcGrid;
    UIStepper                               *mStepperArcStartRot;
    UIStepper                               *mStepperArcEndRot;
    UIStepper                               *mStepperArcRadius;
    UIStepper                               *mStepperArcRadiusSpacing;
    UIStepper                               *mStepperArcRadiusCount;
    
    UIStepper                               *mStepperArcSweepCount;
    UIStepper                               *mStepperArcCumulativeDepression;
    
    ToolMenuSectionRow                      *mRowArc1;
    UICheckBox                              *mCheckBoxArcFillEvenly;
    UICheckBox                              *mCheckBoxArcInvertH;
    
    
    void                                    RefreshGridPanels();
    
};

#endif /* EditorMenuFormationGridGrid_hpp */
