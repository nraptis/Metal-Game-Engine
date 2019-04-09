//
//  EditorMenuFormationUtilities.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuFormationUtilities_hpp
#define EditorMenuFormationUtilities_hpp

#include "ToolMenu.hpp"

class GameFormationEditor;
class EditorMenuFormationUtilities : public ToolMenu {
public:
    EditorMenuFormationUtilities(GameFormationEditor *pEditor);
    virtual ~EditorMenuFormationUtilities();
    
    virtual void                            Update() override;
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonCloseEditor;
    UIButton                                *mButtonResetFormation;
    
    
    ToolMenuPanel                           *mPanelTracers;
    
    ToolMenuSectionRow                      *mRowTracers1;
    UICheckBox                              *mCheckBoxTracersEnabled;
    
    UISegment                               *mSegmentCurrentTracer;
    
    UIButton                                *mButtonDeleteTracer;
    UISegment                               *mSegmentTracersMode;
    
    
    ToolMenuPanel                           *mPanelTracerTweaks;
    UIStepper                               *mStepperTracerSpawnCount;
    
    UISegment                               *mSegmentTracersSpeed;
    
    
    
    ToolMenuPanel                           *mPanelTracerSpecial;
    UISegment                               *mSegmentTracerSpecialType;
    UIStepper                               *mStepperTracerSpecialRadius;
    UIStepper                               *mStepperTracerSpecialCornerRadius;
    
    
    GameFormationEditor                     *mEditor;
    
    
};


#endif









