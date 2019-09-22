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
class GamePermanentEditor;
class EditorMenuPanelFormationConfiguration;

class EditorMenuAttachment : public ToolMenu {
public:
    EditorMenuAttachment(GameEditor *pEditor);
    EditorMenuAttachment(GamePermanentEditor *pEditor);
    
    void                                    Init();
    
    
    
    virtual ~EditorMenuAttachment();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameEditor                              *mEditor;
    GamePermanentEditor                     *mPermEditor;
    
    
    
    ToolMenuPanel                           *mPanelObjectTypes;
    
    ToolMenuSectionRow                      *mRowObjectTypes1;
    ToolMenuSectionRow                      *mRowObjectTypes2;
    
    UIButton                                *mButtonPickBalloon;
    UIButton                                *mButtonPickBrickHead;
    
    UIButton                                *mButtonPickBomb;
    UIButton                                *mButtonPickTurtle;
    
    
    
    
    
    
    ToolMenuPanel                           *mPanelFormations;
    
    ToolMenuSectionRow                      *mRowFormations1;
    UIButton                                *mButtonPickFormation;
    UIButton                                *mButtonClearFormation;
    
    ToolMenuSectionRow                      *mRowFormations2;
    UICheckBox                              *mCheckBoxInvertFormationH;
    UICheckBox                              *mCheckBoxInvertFormationV;
    
    EditorMenuPanelFormationConfiguration   *mPanelFormationConfiguration;
    
    
    ToolMenuPanel                           *mPanelBehavior;
    
    ToolMenuSectionRow                      *mRowBehavior1;
    UICheckBox                              *mCheckBoxShortCircuit;
    UICheckBox                              *mCheckBoxShortCircuitKnockDown;
    
    
    UIStepper                               *mStepperSpacingOffset;
};

#endif /* EditorMenuAttachment_hpp */
