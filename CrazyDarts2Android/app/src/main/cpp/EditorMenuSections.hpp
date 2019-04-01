//
//  EditorMenuSections.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuSections_hpp
#define EditorMenuSections_hpp

#include "ToolMenu.hpp"

class GameEditor;
class EditorMenuSections : public ToolMenu {
public:
    EditorMenuSections(GameEditor *pEditor);
    virtual ~EditorMenuSections();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonBuildFormation;
    UIButton                                *mButtonSaveSection;
    UIButton                                *mButtonLoadSection;
    ToolMenuSectionRow                      *mRowMain2;
    UIButton                                *mButtonClear;
    UIButton                                *mButtonLoadCleared;
    
    
    ToolMenuPanel                           *mMenusPanel;
    ToolMenuSectionRow                      *mRowMenus1;
    ToolMenuSectionRow                      *mRowMenus2;
    UIButton                                *mButtonShowSpawn;
    UIButton                                *mButtonShowWavePicker;
    UIButton                                *mButtonShowSpawnPicker;
    UIButton                                *mButtonShowAttachments;
    
    
    ToolMenuPanel                           *mWavePanel;
    ToolMenuSectionRow                      *mRowWave1;
    UIButton                                *mButtonAddWave;
    UIButton                                *mButtonDeleteWave;
    UIButton                                *mButtonEditPaths;
    
    ToolMenuSectionRow                      *mRowWave2;
    UICheckBox                              *mCheckBoxPreview;
    UIButton                                *mButtonMoveWaveUp;
    UIButton                                *mButtonMoveWaveDown;
    
    
    
    
    
    ToolMenuPanel                           *mPlaybackPanel;
    ToolMenuSectionRow                      *mRowPlayback1;
    UICheckBox                              *mCheckBoxPlaybackEnabled;
    UIButton                                *mButtonPlaybackRestart;
    
    ToolMenuSectionRow                      *mRowPlayback2;
    UICheckBox                              *mCheckBoxCurrentWaveOnly;
    UICheckBox                              *mCheckBoxPlaybackStartAtSelectedWave;
    
    ToolMenuSectionRow                      *mRowPlayback3;
    
    
    
    
    
    
    
    

    GameEditor                              *mEditor;
    
};

#endif /* EditorMenuSections_hpp */
