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
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonNewSection;
    UIButton                                *mButtonSaveSection;
    UIButton                                *mButtonLoadSection;
    ToolMenuSectionRow                      *mRowMain2;
    
    
    ToolMenuPanel                           *mWavePanel;
    ToolMenuSectionRow                      *mRowWave1;
    UIButton                                *mButtonAddWave;
    UIButton                                *mButtonDeleteWave;
    UIButton                                *mButtonSelectNextWave;
    UIButton                                *mButtonSelectPreviousWave;
    
    
    
    
    
    ToolMenuPanel                           *mPathPanel;
    ToolMenuSectionRow                      *mRowPath1;
    UIButton                                *mButtonEditPaths;
    UIButton                                *mButtonSelectNextPath;
    UIButton                                *mButtonSelectPreviousPath;
    ToolMenuSectionRow                      *mRowPath2;
    
    GameEditor                              *mEditor;
    
};

#endif /* EditorMenuSections_hpp */
