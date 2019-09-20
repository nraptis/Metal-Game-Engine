//
//  EditorMenuStyle.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuStyle_hpp
#define EditorMenuStyle_hpp


#include "ToolMenu.hpp"
#include "LevelStyleControllerBlueprint.hpp"


class GameEditor;
class GamePermanentEditor;

class EditorMenuStyle : public ToolMenu {
public:
    EditorMenuStyle(GameEditor *pEditor);
    EditorMenuStyle(GamePermanentEditor *pEditor);
    
    void                                    Init();
    virtual ~EditorMenuStyle();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    bool                                    mIsForPermSpawn;
    
    GameEditor                              *mEditor;
    GamePermanentEditor                     *mPermEditor;
    LevelStyleControllerBlueprint           *mStyleController;
    
    
    ToolMenuPanel                           *mPanelMainControls;
    ToolMenuSectionRow                      *mRowMain1;
    ToolMenuSectionRow                      *mRowMain2;
    
    
    UICheckBox                              *mCheckBoxThreadsDisable;
    UICheckBox                              *mCheckBoxBobbleEnable;
    UICheckBox                              *mCheckBoxRandomizeSpin;
    
    
    
};

#endif /* EditorMenuStyle_hpp */
