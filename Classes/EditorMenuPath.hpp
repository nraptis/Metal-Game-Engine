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
    virtual void                            Update() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    
    ToolMenuPanel                           *mEditorPanel;
    UISegment                               *mSegmentMode;
    
    ToolMenuSectionRow                      *mRowVisuals;
    UICheckBox                              *mCheckBoxSmooth;
    UICheckBox                              *mCheckBoxPreview;
    
    ToolMenuPanel                           *mPointsPanel;
    
    UIStepper                               *mStepperWait;
    UIStepper                               *mStepperChamfer;
    
    ToolMenuSectionRow                      *mRowPointWait;
    UITextBox                               *mTextBoxWait;
    UIButton                                *mButtonResetWait;
    
    ToolMenuSectionRow                      *mRowPointOptions;
    UIButton                                *mButtonDeletePoint;
    
    ToolMenuPanel                           *mConstraintPanel;
    
    
    
    
    
    
    
    ToolMenuSectionRow                      *mRowSnapPoints;
    UICheckBox                              *mCheckBoxSnapX;
    UICheckBox                              *mCheckBoxSnapY;
    
    ToolMenuSectionRow                      *mRowSnapX1;
    ToolMenuSectionRow                      *mRowSnapX2;
    UIButton                                *mButtonBreakXConstraint;
    UIButton                                *mButtonSnapXSpawnLeft;
    UIButton                                *mButtonSnapXPeekLeft;
    UIButton                                *mButtonSnapXQuarterLeft;
    UIButton                                *mButtonSnapXCenter;
    UIButton                                *mButtonSnapXQuarterRight;
    UIButton                                *mButtonSnapXPeekRight;
    UIButton                                *mButtonSnapXSpawnRight;
    
    
    
    
    ToolMenuSectionRow                      *mRowSnapY1;
    ToolMenuSectionRow                      *mRowSnapY2;
    UIButton                                *mButtonBreakYConstraint;
    UIButton                                *mButtonSnapYSpawnTop;
    UIButton                                *mButtonSnapYPeekTop;
    UIButton                                *mButtonSnapYQuarterTop;
    UIButton                                *mButtonSnapYCenter;
    UIButton                                *mButtonSnapYQuarterBottom;
    UIButton                                *mButtonSnapYBottom;
    
    
    
    //UICheckBox                              *mCheckBoxSmooth;
    //UICheckBox                              *mCheckBoxPreview;
    
    
    GamePathEditor                          *mEditor;
    
};


#endif /* EditorMenuPathMain_hpp */
