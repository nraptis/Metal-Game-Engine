//
//  EditorMenuFormation.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuFormation_hpp
#define EditorMenuFormation_hpp

#include "ToolMenu.hpp"


class GameFormationEditor;
class EditorMenuFormation : public ToolMenu {
public:
    EditorMenuFormation(GameFormationEditor *pEditor);
    virtual ~EditorMenuFormation();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuPanel                           *mEditorPanel;
    UISegment                               *mSegmentMode;
    
    ToolMenuSectionRow                      *mRowVisuals;
    UICheckBox                              *mCheckBoxSmooth;
    UICheckBox                              *mCheckBoxPreview;
    
    ToolMenuPanel                           *mPointsPanel;
    
    UIStepper                               *mStepperWait;
    UIStepper                               *mStepperChamfer;
    
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
    
    GameFormationEditor                     *mEditor;
    
};


#endif /* EditorMenuFormation_hpp */
