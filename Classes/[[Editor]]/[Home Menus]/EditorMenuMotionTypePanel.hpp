//
//  EditorMenuMotionTypePanel.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/25/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuMotionTypePanel_hpp
#define EditorMenuMotionTypePanel_hpp

#include "LevelMotionControllerBlueprint.hpp"
#include "ToolMenu.hpp"

class EditorMenuMotionTypePanel : public ToolMenuPanel {
public:
    
    EditorMenuMotionTypePanel();
    virtual ~EditorMenuMotionTypePanel();
    
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    int                                     mType;
    
    LevelMotionControllerSliceBlueprint     *mMotionSlice;
    int                                     mSpeedIndex;
    
    
    ToolMenuPanel                           *mPanelGeneric;
    UISegment                               *mSegmentSpeed;
    
    ToolMenuSectionRow                      *mRowGeneric1;
    
    UICheckBox                              *mCheckBoxNegate;
    UICheckBox                              *mCheckBoxNegateRandomly;
    
    
};

class EditorMenuMotionTypePanelRotate : public EditorMenuMotionTypePanel {
public:
    
    EditorMenuMotionTypePanelRotate();
    virtual ~EditorMenuMotionTypePanelRotate();
    
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuSectionRow                      *mRowOffsets1;
    ToolMenuSectionRow                      *mRowOffsets2;
    
    UILabel                                 *mLabelPivotOffsetX;
    UILabel                                 *mLabelPivotOffsetY;
    
    UIButton                                *mButtonResetPivotOffsetX;
    UIButton                                *mButtonResetPivotOffsetY;
    
    UIStepper                               *mStepperPivotOffsetX;
    UIStepper                               *mStepperPivotOffsetY;
    
};


#endif /* EditorMenuMotionTypePanel_hpp */
