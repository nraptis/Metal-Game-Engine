//
//  EditorMenuAttachment.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/29/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuAttachment_hpp
#define EditorMenuAttachment_hpp


#include "ToolMenu.hpp"

class GameEditor;
class EditorMenuAttachment : public ToolMenu {
public:
    EditorMenuAttachment(GameEditor *pEditor);
    virtual ~EditorMenuAttachment();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameEditor                              *mEditor;
    
    
    ToolMenuPanel                           *mPanelFormations;
    
    ToolMenuSectionRow                      *mRowFormations1;
    UIButton                                *mButtonPickFormation1;
    UIButton                                *mButtonPickFormation2;
    UIButton                                *mButtonClearFormation;
    
    ToolMenuSectionRow                      *mRowFormations2;
    UICheckBox                              *mCheckBoxInvertFormationH;
    UICheckBox                              *mCheckBoxInvertFormationV;
    
    
    ToolMenuPanel                           *mPanelBehavior;
    
    UIStepper                               *mStepperSpacingOffset;
    
    ToolMenuPanel                           *mPanelRotation;
    UISegment                               *mSegmentRotationSpeed;
    ToolMenuSectionRow                      *mRowRotation;
    UICheckBox                              *mCheckBoxRotationNegateAlways;
    UICheckBox                              *mCheckBoxRotationNegateRandom;
    
    
};

#endif /* EditorMenuAttachment_hpp */
