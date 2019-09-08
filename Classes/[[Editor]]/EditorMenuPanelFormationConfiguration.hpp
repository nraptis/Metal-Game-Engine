//
//  EditorMenuPanelFormationConfiguration.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuPanelFormationConfiguration_hpp
#define EditorMenuPanelFormationConfiguration_hpp

#include "ToolMenu.hpp"

class GamePermanentEditor;
class EditorMenuPanelFormationConfiguration : public ToolMenuPanel {
public:
    
    EditorMenuPanelFormationConfiguration();
    virtual ~EditorMenuPanelFormationConfiguration();
    
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonReset;
    
    UISegment                               *mSegmentTracerSpeedGlobal;
    
    ToolMenuPanel                           *mPanelTracerSpeed;
    UISegment                               *mSegmentTracerSpeed1;
    UISegment                               *mSegmentTracerSpeed2;
    UISegment                               *mSegmentTracerSpeed3;
    
    
    int                                     mTracerSpeedIndexGlobal;
    
    //ToolMenuPanel                           *mMenuPathSpawn;
    //UIStepper                               *mStepperPathSpawnCount;
    //UIStepper                               *mStepperPathSpawnSpacing;
    
    //ToolMenuSectionRow                      *mRowPathSpawn1;
    //UICheckBox                              *mCheckBoxPathSpawnEqualSpacing;
    
    
};

#endif /* EditorMenuPanelFormationConfiguration_hpp */
