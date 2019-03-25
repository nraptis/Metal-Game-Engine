//
//  EditorMenuSpawn.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuSpawn_hpp
#define EditorMenuSpawn_hpp

#include "ToolMenu.hpp"

class GameEditor;
class EditorMenuSpawn : public ToolMenu {
public:
    EditorMenuSpawn(GameEditor *pEditor);
    virtual ~EditorMenuSpawn();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameEditor                              *mEditor;
    
    
    ToolMenuPanel                           *mPanelGeneration;
    
    ToolMenuSectionRow                      *mRowGeneration;
    UILabel                                 *mLabelSpeed;
    UICheckBox                              *mCheckBoxSpeed;
    
    UISegment                               *mSegmentSpeed;
    UIStepper                               *mStepperSpawnCount;
    UISlider                                *mSliderSpacing;
    
    ToolMenuPanel                           *mPanelAttachments;
    ToolMenuSectionRow                      *mRowFormations1;
    UIButton                                *mButtonClearFormation;
    UIButton                                *mButtonDefaultFormation;
    UIButton                                *mButtonPickFormation;
    
    
    ToolMenuPanel                           *mPanelMovement;
    UISlider                                *mSliderRotation;
    
};

#endif
