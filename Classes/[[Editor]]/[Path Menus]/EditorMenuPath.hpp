//
//  EditorMenuPathMain.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuPathMain_hpp
#define EditorMenuPathMain_hpp

#include "ToolMenu.hpp"


class GamePathEditor;
class EditorMenuPath : public ToolMenu {
public:
    EditorMenuPath(GamePathEditor *pEditor);
    virtual ~EditorMenuPath();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuPanel                           *mPanelEditor;
    UISegment                               *mSegmentMode;
    
    ToolMenuSectionRow                      *mRowVisuals;
    UICheckBox                              *mCheckBoxSmooth;
    UICheckBox                              *mCheckBoxPreview;
    
    ToolMenuPanel                           *mPointsPanel;
    
    UIStepper                               *mStepperWait;
    UIStepper                               *mStepperChamfer;
    UIStepper                               *mStepperDecel;
    
    ToolMenuSectionRow                      *mRowPointOptions;
    UIButton                                *mButtonDeletePoint;
    UIButton                                *mButtonBreakXConstraint;
    UIButton                                *mButtonBreakYConstraint;
    
    ToolMenuPanel                           *mConstraintPanel;
    
    
    
    
    
    
    
    ToolMenuSectionRow                      *mRowSnapX;
    UICheckBox                              *mCheckBoxSnapX;
    UIButton                                *mButtonSnapPrevX;
    UIButton                                *mButtonSnapNextX;
    
    ToolMenuSectionRow                      *mRowSnapY;
    UICheckBox                              *mCheckBoxSnapY;
    UIButton                                *mButtonSnapPrevY;
    UIButton                                *mButtonSnapNextY;
    
    GamePathEditor                          *mEditor;
    
};


#endif /* EditorMenuPathMain_hpp */
