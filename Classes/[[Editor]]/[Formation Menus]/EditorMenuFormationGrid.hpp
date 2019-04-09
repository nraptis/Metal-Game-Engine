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

class GameFormationEditor;
class EditorMenuFormationGrid : public ToolMenu {
public:
    EditorMenuFormationGrid(GameFormationEditor *pEditor);
    virtual ~EditorMenuFormationGrid();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    
    
    ToolMenuPanel                           *mPanelGrid;
    UISegment                               *mSegmentGridType;
    
    ToolMenuPanel                           *mPanelRectGrid;
    
    ToolMenuSectionRow                      *mRowGrid1;
    UICheckBox                              *mCheckBoxGridEnabled;
    UICheckBox                              *mCheckBoxGridDisplay;
    
    UIStepper                               *mStepperRectGridWidth;
    UIStepper                               *mStepperRectGridHeight;
    UIStepper                               *mStepperRectGridSpacing;
    
    ToolMenuPanel                           *mPanelCircleGrid;
    UIStepper                               *mStepperCircleRingCount;
    UIStepper                               *mStepperCircleRingSpacing;
    UIStepper                               *mStepperCircleRadialCount;
    
    
    ToolMenuPanel                           *mPanelNGON1Grid;
    UIStepper                               *mStepperNGON1Sides;
    UIStepper                               *mStepperNGON1RingCount;
    UIStepper                               *mStepperNGON1RingSpacing;
    UIStepper                               *mStepperNGON1PointSpacing;
    UIStepper                               *mStepperNGON1StartRotation;
    
    
    GameFormationEditor                     *mEditor;
    
    void                                    RefreshGridPanels();
    
};

#endif /* EditorMenuFormationGridGrid_hpp */
