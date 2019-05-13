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

class EditorMenuMotionTypePanelNegate : public EditorMenuMotionTypePanel {
public:
    
    EditorMenuMotionTypePanelNegate();
    virtual ~EditorMenuMotionTypePanelNegate();
    
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuSectionRow                      *mRowNegs1;
    ToolMenuSectionRow                      *mRowNegs2;
    
    UICheckBox                              *mCheckBoxNegateH;
    UICheckBox                              *mCheckBoxNegateHRandomly;
    
    UICheckBox                              *mCheckBoxNegateV;
    UICheckBox                              *mCheckBoxNegateVRandomly;
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

class EditorMenuMotionTypePanelOscillateRotation : public EditorMenuMotionTypePanel {
public:
    
    EditorMenuMotionTypePanelOscillateRotation();
    virtual ~EditorMenuMotionTypePanelOscillateRotation();
    
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuSectionRow                      *mRowOptions;
    UICheckBox                              *mCheckBoxLinear;
    
    UIStepper                               *mStepperLinearTime;
    UIStepper                               *mStepperLinearTimer;
    
    UIStepper                               *mStepperPause1;
    UIStepper                               *mStepperPause2;
    
    UIStepper                               *mStepperAngleSpan;
    UIStepper                               *mStepperAngleSpanStartOffset;
    UIStepper                               *mStepperAngleSpanEndOffset;
};


class EditorMenuMotionTypePanelOscillateVertical : public EditorMenuMotionTypePanel {
public:
    
    EditorMenuMotionTypePanelOscillateVertical();
    virtual ~EditorMenuMotionTypePanelOscillateVertical();
    
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuSectionRow                      *mRowOptions;
    UICheckBox                              *mCheckBoxLinear;
    
    UIStepper                               *mStepperLinearTime;
    UIStepper                               *mStepperLinearTimer;
    
    UIStepper                               *mStepperPause1;
    UIStepper                               *mStepperPause2;
    
    UIStepper                               *mStepperRadius;
};

class EditorMenuMotionTypePanelOscillateHorizontal : public EditorMenuMotionTypePanel {
public:
    
    EditorMenuMotionTypePanelOscillateHorizontal();
    virtual ~EditorMenuMotionTypePanelOscillateHorizontal();
    
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuSectionRow                      *mRowOptions;
    UICheckBox                              *mCheckBoxLinear;
    
    UIStepper                               *mStepperLinearTime;
    UIStepper                               *mStepperLinearTimer;
    
    UIStepper                               *mStepperPause1;
    UIStepper                               *mStepperPause2;
    
    UIStepper                               *mStepperRadius;
};



#endif /* EditorMenuMotionTypePanel_hpp */
