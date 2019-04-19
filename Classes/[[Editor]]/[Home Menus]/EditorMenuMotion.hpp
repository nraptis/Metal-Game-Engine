//
//  EditorMenuMotion.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuMotion_hpp
#define EditorMenuMotion_hpp

#include "ToolMenu.hpp"

class GameEditor;
class EditorMenuMotion : public ToolMenu {
public:
    EditorMenuMotion(GameEditor *pEditor);
    virtual ~EditorMenuMotion();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameEditor                              *mEditor;
    
    ToolMenuPanel                           *mGenerationPanel;
    UISegment                               *mSegmentSpeed;
    UIStepper                               *mStepperSpawnCount;
    UIStepper                               *mStepperSpacing;
    
    ToolMenuPanel                           *mTimingPanel;
    //UISegment                               *mStepperCreationType;
    UIStepper                               *mStepperCreationDelay;
    
    ToolMenuSectionRow                      *mTimingRow1;
    UICheckBox                              *mCheckBoxCreationRequiresPrevWaveStart;
    UICheckBox                              *mCheckBoxCreationRequiresPrevWaveComplete;
    
    
    ToolMenuSectionRow                      *mTimingRow2;
    UICheckBox                              *mCheckBoxCreationRequiresScreenWavesClear;
    UICheckBox                              *mCheckBoxCreationRequiresScreenPermsClear;
};

#endif /* EditorMenuMotion_hpp */
